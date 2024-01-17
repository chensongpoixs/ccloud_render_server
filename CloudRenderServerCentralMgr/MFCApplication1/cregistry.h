/***********************************************************************************************
    created:         2019-03-06

    author:            chensong

    purpose:        crc4
************************************************************************************************/
#ifndef _C_REGISTRY_H_
#define _C_REGISTRY_H_
#include <string>
namespace chen
{
    bool writetoregistry(const char* key_path, const char * key,  const std::string &value);
    bool readfromregistry(const char * key_path, const char * key, std::string & value);
}

#endif // _C_REGISTRY_H_