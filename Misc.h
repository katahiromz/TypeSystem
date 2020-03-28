#pragma once

#ifndef _INC_WINDOWS
    #include <windows.h>
#endif
#include <string>
#include <map>
#include <vector>

struct FUNCTION
{
    std::string name;
    std::string convention;
    std::string ret;
    std::vector<std::string> params;
};

typedef std::map<std::string, FUNCTION> functions_t;

BOOL GetWondersDirectory(LPWSTR pszPath, INT cchPath);
BOOL DoLoadFunctions(functions_t& funcs, LPCWSTR prefix, LPCWSTR suffix);
