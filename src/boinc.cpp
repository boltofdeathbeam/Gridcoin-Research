#include "boinc.h"
#include <boost/filesystem.hpp>
#ifdef _WIN32
#include <windows.h>
#define KEY_WOW64_64KEY 0x0100
#endif // _WIN32

std::string CBoinc::GetBoincDataPath(){
    #ifdef _WIN32
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                     L"SOFTWARE\\Space Sciences Laboratory, U.C. Berkeley\\BOINC Setup\\",
                     0,
                     KEY_READ|KEY_WOW64_64KEY,
                     &hKey) == ERROR_SUCCESS){

        wchar_t szPath[MAX_PATH];
        DWORD dwSize = sizeof(szPath);

        if (RegQueryValueEx(hKey,
                        L"DATADIR",
                        NULL,
                        NULL,
                        (LPBYTE)&szPath,
                        &dwSize) == ERROR_SUCCESS){
            RegCloseKey(hKey);
            std::wstring wsPath = szPath;
            std::string path(wsPath.begin(),wsPath.end());
            return path;
        }
        RegCloseKey(hKey);
    }

    if (boost::filesystem::exists("C:\\ProgramData\\BOINC\\")){
        return "C:\\ProgramData\\BOINC\\";
    }
    else if(boost::filesystem::exists("C:\\Documents and Settings\\All Users\\Application Data\\BOINC\\")){
        return "C:\\Documents and Settings\\All Users\\Application Data\\BOINC\\";
    }
    #endif // _WIN32

    #ifdef __linux__
    if (boost::filesystem::exists("/var/lib/boinc-client/")){
        return "/var/lib/boinc-client/";
    }
    #endif // __linux__

    #ifdef __APPLE__
    if (boost::filesystem::exists("/Library/Application Support/BOINC Data/")){
        return "/Library/Application Support/BOINC Data/";
    }
    #endif // __APPLE__
    return "";
}
