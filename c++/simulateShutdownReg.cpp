#include <windows.h>
#include <winreg.h>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <thread>
#include <chrono>
// Simulates a shutdown, cancels in 30 seconds, and monitors the current user run registry for any changes. Can be used to pickup malware that writes to this run registry before shutdown
std::set<std::wstring> ListRunKeys(HKEY root, LPCWSTR subkey) {
    std::set<std::wstring> keys;
    HKEY hKey;
    if (RegOpenKeyEx(root, subkey, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        DWORD index = 0;
        WCHAR valueName[256];
        DWORD valueSize = sizeof(valueName) / sizeof(WCHAR);
        while (RegEnumValue(hKey, index++, valueName, &valueSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
            keys.insert(valueName);
            valueSize = sizeof(valueName) / sizeof(WCHAR);
        }
        RegCloseKey(hKey);
    }
    return keys;
}

void Log(const std::wstring& msg) {
    std::wofstream log(L"registry_monitor.log", std::ios::app);
    SYSTEMTIME st;
    GetLocalTime(&st);
    log << L"[" << st.wYear << L"-" << st.wMonth << L"-" << st.wDay << L" "
        << st.wHour << L":" << st.wMinute << L":" << st.wSecond << L"] "
        << msg << std::endl;
    log.close();
}

void MonitorRunKeyChanges() {
    const wchar_t* subkey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    HKEY hKey;

    if (RegOpenKeyEx(HKEY_CURRENT_USER, subkey, 0, KEY_NOTIFY, &hKey) != ERROR_SUCCESS) {
        std::wcerr << L"Failed to open Run key\n";
        return;
    }

    std::set<std::wstring> before = ListRunKeys(HKEY_CURRENT_USER, subkey);

    Log(L"Monitoring Run key for changes...");

    while (true) {
        // Wait for change notification
        if (RegNotifyChangeKeyValue(hKey, FALSE, REG_NOTIFY_CHANGE_LAST_SET, NULL, FALSE) == ERROR_SUCCESS) {
            std::set<std::wstring> after = ListRunKeys(HKEY_CURRENT_USER, subkey);
            for (const auto& entry : after) {
                if (before.find(entry) == before.end()) {
                    Log(L"New Run entry detected: " + entry);
                }
            }
            before = after;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1)); // prevent tight loop
    }

    RegCloseKey(hKey);
}

void SimulateShutdown() {
    Log(L"Simulating system shutdown in 60 seconds...");

    BOOL result = InitiateSystemShutdownExW(
        NULL,
        L"Simulating shutdown. This will be aborted.",
        60,     // timeout in seconds
        TRUE,   // force apps to close
        FALSE,  // no reboot
        SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_FLAG_PLANNED
    );

    if (!result) {
        Log(L"Failed to initiate shutdown.");
    } else {
        std::this_thread::sleep_for(std::chrono::seconds(30)); // simulate mid-cancel
        AbortSystemShutdown(NULL);
        Log(L"Shutdown aborted.");
    }
}

int main() {
    std::thread monitorThread(MonitorRunKeyChanges);
    std::thread shutdownThread(SimulateShutdown);

    monitorThread.join(); // Or run indefinitely
    shutdownThread.join();

    return 0;
}
