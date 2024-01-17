#include "cregistry.h"

#include <stdio.h>
#include <Windows.h>
#include "clog.h"
#define KEY_PATH "Software\\MyCompany\\MyApp3" // 你的注册表路径
namespace chen {


bool writetoregistry(const char * key_path, const char * key, const std::string & data) {
    HKEY hKey;
    DWORD dwDisposition;

    // 创建或打开注册表键
    LONG regStatus = RegCreateKeyEx(HKEY_CURRENT_USER, LPCWSTR(key_path), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &dwDisposition);
    if (regStatus != ERROR_SUCCESS) {
        WARNING_EX_LOG("Unable to create/open registry key. Error code: %d\n", regStatus);
        return false;
    }

    // 设置要写入的数据
   // char  value[1024] = "chensong-----";
    regStatus = RegSetValueEx(hKey, LPCWSTR(key), 0, REG_BINARY, (BYTE*)data.c_str(), sizeof(char ) * data.length());
    RegCloseKey(hKey);
    if (regStatus != ERROR_SUCCESS) 
    {
        WARNING_EX_LOG("Unable to write to registry. Error code: %d\n", regStatus);
        return false;
    }
    else 
    {
        WARNING_EX_LOG("Data written to registry successfully!\n");
    }
    return true;
    // 关闭注册表键
   
}

bool readfromregistry(const char* key_path,  const char * key, std::string & data) 
{
    HKEY hKey;
      char  value[2048] = {0};
    DWORD dataSize = sizeof(value);
    DWORD valueType;

    // 打开注册表键
    LONG regStatus = RegOpenKeyEx(HKEY_CURRENT_USER, LPCWSTR(key_path), 0, KEY_READ, &hKey);
    if (regStatus != ERROR_SUCCESS)
    {
        WARNING_EX_LOG("Unable to open registry key. Error code: %d\n", regStatus);
        return false;
    }

    // 读取数据
    regStatus = RegQueryValueEx(hKey, LPCWSTR(key), NULL, &valueType, (BYTE*)&value, &dataSize);

    // 关闭注册表键
    RegCloseKey(hKey);
    if (regStatus != ERROR_SUCCESS) 
    {
        WARNING_EX_LOG("Unable to read from registry. Error code: %d\n", regStatus);
        return false;
    }
    else {
        if (valueType == REG_BINARY) {
           // printf("Read value from registry: %s\n", value);
            //return std::string(value);
            data = std::string(value);
        }
        else 
        {
            WARNING_EX_LOG("Invalid data type in registry. %d\n", valueType);
            return false;
        }
    }

    return true;
}
}
//int main() {
//    writeToRegistry(); // 写入数据到注册表
//    readFromRegistry(); // 从注册表中读取数据
//
//    return 0;
//}
