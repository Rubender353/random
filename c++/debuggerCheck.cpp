#include <windows.h>
#include <winternl.h>
#include <iostream>

#pragma comment(lib, "ntdll.lib")

// example uses 3 debugger check methods. 1 is NtQueryInformationProcess using ProcessDebugPort, 2 is PEB check, and 3 is using IsDebuggerPresent
extern "C" NTSTATUS NTAPI NtQueryInformationProcess(
    HANDLE ProcessHandle,
    PROCESSINFOCLASS ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength,
    PULONG ReturnLength
);

bool CheckProcessDebugPort() {
    DWORD debugPort = 0;
    NTSTATUS status = NtQueryInformationProcess(
        GetCurrentProcess(),
        ProcessDebugPort,
        &debugPort,
        sizeof(debugPort),
        nullptr
    );
    return NT_SUCCESS(status) && debugPort != 0;
}

bool CheckPEBBeingDebugged() {
#ifdef _M_X64
    // Read PEB address from GS:[0x60]
    ULONG_PTR pebAddress = __readgsqword(0x60);
    // BeingDebugged is a BYTE at offset 0x2 inside the PEB
    BYTE beingDebugged = *(BYTE*)(pebAddress + 0x2);
    return beingDebugged != 0;
#else
    // x86 version: PEB is at FS:[0x30]
    ULONG_PTR pebAddress = __readfsdword(0x30);
    BYTE beingDebugged = *(BYTE*)(pebAddress + 0x2);
    return beingDebugged != 0;
#endif
}

bool IsDebuggerPresentPEB() {
    return CheckPEBBeingDebugged() || CheckProcessDebugPort() || IsDebuggerPresent();
}

int main() {
    if (IsDebuggerPresentPEB()) {
        std::cout << "[!] Debugger detected! Exiting...\n";
        return 1;
    }
    std::cout << "No debugger detected. Running normally.\n";
    return 0;
}

