#include "Misc.h"
#include <shlwapi.h>

template <typename t_string_container, 
          typename t_string = typename t_string_container::value_type>
void split(t_string_container& container,
    const typename t_string_container::value_type& str,
    typename t_string::value_type sep)
{
    container.clear();
    std::size_t i = 0, j = str.find(sep);
    while (j != t_string_container::value_type::npos) {
        container.emplace_back(std::move(str.substr(i, j - i)));
        i = j + 1;
        j = str.find(sep, i);
    }
    container.emplace_back(std::move(str.substr(i, -1)));
}

BOOL GetWondersDirectory(LPWSTR pszPath, INT cchPath)
{
    WCHAR szDir[MAX_PATH], szPath[MAX_PATH];
    GetModuleFileNameW(NULL, szDir, ARRAYSIZE(szDir));
    PathRemoveFileSpecW(szDir);

    lstrcpynW(szPath, szDir, ARRAYSIZE(szPath));
    PathAppendW(szPath, L"WondersXP");
    if (!PathIsDirectoryW(szPath))
    {
        lstrcpynW(szPath, szDir, ARRAYSIZE(szPath));
        PathAppendW(szPath, L"..\\WondersXP");
        if (!PathIsDirectoryW(szPath))
        {
            lstrcpynW(szPath, szDir, ARRAYSIZE(szPath));
            PathAppendW(szPath, L"..\\..\\WondersXP");
            if (!PathIsDirectoryW(szPath))
            {
                lstrcpynW(szPath, szDir, ARRAYSIZE(szPath));
                PathAppendW(szPath, L"..\\..\\..\\WondersXP");
                if (!PathIsDirectoryW(szPath))
                    return FALSE;
            }
        }
    }

    lstrcpynW(pszPath, szPath, cchPath);
    return TRUE;
}

BOOL DoLoadFunctions(functions_t& functions, LPCWSTR prefix, LPCWSTR suffix)
{
    functions.clear();

    std::wstring filename = prefix;
    filename += L"functions";
    filename += suffix;

    FILE *fp = _wfopen(filename.c_str(), L"r");
    if (!fp)
        return FALSE;

    char buf[512];
    fgets(buf, ARRAYSIZE(buf), fp);
    while (fgets(buf, ARRAYSIZE(buf), fp))
    {
        StrTrimA(buf, " \t\r\n");

        FUNCTION fn;
        split(fn.params, buf, '\t');
        if (fn.params.size() < 3)
            continue;

        fn.name = fn.params[0];
        fn.convention = fn.params[1];
        fn.ret = fn.params[2];
        fn.params.erase(fn.params.begin(), fn.params.begin() + 3);
        functions.insert(std::make_pair(fn.name, fn));
    }

    fclose(fp);
    return TRUE;
}
