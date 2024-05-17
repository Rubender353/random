#include <windows.h>
#include <stdio.h>
#include <winternl.h>


#define SystemProcessInformation 5

//example of NtQuerySystemInformation being used to find a process. technique used by malware

typedef NTSTATUS(WINAPI* NtQuerySystemInformation_t)(
	ULONG SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength
	);

int FindTarget(const wchar_t* procname) {
	int pid = 0;
	PVOID buffer = NULL;
	DWORD bufSize = 0;

	// resolve function address
	NtQuerySystemInformation_t pNtQuerySystemInformation = (NtQuerySystemInformation_t)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtQuerySystemInformation");

	// get initial buffer size to allocate
	pNtQuerySystemInformation((SYSTEM_INFORMATION_CLASS)SystemProcessInformation, 0, 0, &bufSize);
	if (bufSize == 0)
		return -1;

	// allocate appropriate buffer for process information
	if (buffer = VirtualAlloc(0, bufSize, MEM_COMMIT, PAGE_READWRITE)) {
		SYSTEM_PROCESS_INFORMATION* sysproc_info = (SYSTEM_PROCESS_INFORMATION*)buffer;
		if (!pNtQuerySystemInformation((SYSTEM_INFORMATION_CLASS)SystemProcessInformation, buffer, bufSize, &bufSize)) {
			while (TRUE) {
				//printf("procname = %S\n", sysproc_info->ImageName.Buffer);
				if (lstrcmpiW(procname, sysproc_info->ImageName.Buffer) == 0) {
					pid = (int)sysproc_info->UniqueProcessId;
					break;
				}
				if (!sysproc_info->NextEntryOffset)
					break;
				sysproc_info = (SYSTEM_PROCESS_INFORMATION*)((ULONG_PTR)sysproc_info + sysproc_info->NextEntryOffset);
			}
		}
	}
	VirtualFree(buffer, bufSize, MEM_RELEASE);
	return pid;
}

int main(void) {
	int pid = FindTarget(L"msedge.exe");
	printf("Notepad %s%d)\n", pid > 0 ? "found at PID: (" : "NOT FOUND(", pid);

	return 0;
}