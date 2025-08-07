#include <windows.h>
#include <iostream>
#include <string>

// Dynamically load the messageboxa and use a hash of it showcasing two techniques
// used by malware to make it much harder to analyze the code statically

// Simple djb2 hash function
unsigned long djb2Hash(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

// Define the hash of "MessageBoxA"
#define HASH_MessageBoxA 0x384F14B4  // Precomputed hash of "MessageBoxA"

typedef int (WINAPI* MESSAGEBOXA)(HWND, LPCSTR, LPCSTR, UINT);

int main() {
    HMODULE hUser32 = LoadLibraryA("user32.dll");
    if (!hUser32) {
        std::cerr << "Failed to load user32.dll" << std::endl;
        return 1;
    }

    // Loop through exported functions and match by hash
    BYTE* base = (BYTE*)hUser32;
    IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)base;
    IMAGE_NT_HEADERS* ntHeaders = (IMAGE_NT_HEADERS*)(base + dosHeader->e_lfanew);
    IMAGE_EXPORT_DIRECTORY* exportDir = (IMAGE_EXPORT_DIRECTORY*)
        (base + ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

    DWORD* nameRvas = (DWORD*)(base + exportDir->AddressOfNames);
    WORD* ordinals = (WORD*)(base + exportDir->AddressOfNameOrdinals);
    DWORD* functions = (DWORD*)(base + exportDir->AddressOfFunctions);

    MESSAGEBOXA pMessageBoxA = nullptr;
    std::cout << "Hash of MessageBoxA" << std::hex << std::uppercase << djb2Hash("MessageBoxA") << std::endl;

    for (DWORD i = 0; i < exportDir->NumberOfNames; ++i) {
        const char* funcName = (const char*)(base + nameRvas[i]);
        if (djb2Hash(funcName) == HASH_MessageBoxA) {
            WORD ordinal = ordinals[i];
            DWORD funcRva = functions[ordinal];
            pMessageBoxA = (MESSAGEBOXA)(base + funcRva);
            break;
        }
    }

    if (!pMessageBoxA) {
        std::cerr << "Failed to find MessageBoxA by hash" << std::endl;
        return 1;
    }

    // Call MessageBoxA
    pMessageBoxA(NULL, "This is dynamically resolved!", "Success", MB_OK);

    return 0;
}
