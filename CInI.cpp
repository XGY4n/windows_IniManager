#include "CInI.h"
#ifdef UNICODE
CInI::CInI(const std::wstring& inifile)
{
    this->wtarget_ini_path = inifile;
    lpFileNameW = this->wtarget_ini_path.c_str();
}
#else
CInI::CInI(const std::string& inifile)
{
    this->target_ini_path = inifile;
    lpFileNameA = this->target_ini_path.c_str();
}

#endif


CInI::~CInI()
{

}


std::string CInI::InIfindA(std::string section, std::string name)
{
    char* temp = (char*)malloc(sizeof(char) * 100);
    DWORD status = ::GetPrivateProfileStringA(section.c_str(), name.c_str(), "", temp, 100, this->lpFileNameA);
    if (!status)
    {
        return "";//eummark
        free(temp);
    }
    std::string result = temp;
    free(temp);

    return result;
}

std::wstring CInI::InIfindW(std::wstring section, std::wstring name)
{
    WCHAR* content = (wchar_t*)malloc(sizeof(wchar_t) * 200);
    DWORD status = ::GetPrivateProfileStringW(section.c_str(), name.c_str(), TEXT(""), content, 200, this->lpFileNameW);

    std::wstring result = content;
    free(content); // Free the memory allocated by malloc

    if (!status || result.empty())
    {
        return L"";
    }
    return result;

}

CInI::InIexstat CInI::InIexistA(const std::string& section, const std::string& name, const std::string& value)
{
    if (section.empty())
        return CInI::INI_READ_NOTEXIST;
    else if(name.empty() && value.empty())
    {
        char* temp = (char*)malloc(sizeof(char) * 100);
        DWORD status = ::GetPrivateProfileSectionA(section.c_str(), temp, 100, this->lpFileNameA);
        free(temp);
        if (!status)
            return CInI::INI_READ_NOTEXIST;

        return CInI::INI_READ_EXIST;
    }


    if (!name.empty()&& value.empty())
    {
        char* temp = (char*)malloc(sizeof(char) * 100);
        DWORD status = ::GetPrivateProfileStructA(section.c_str(), name.c_str(), temp, 100, this->lpFileNameA);
        free(temp);
        if (!status)
            return CInI::INI_READ_NOTEXIST;

        return CInI::INI_READ_EXIST;
        //go find name
    }


    if (!name.empty() && !value.empty())
    {
        char* temp = (char*)malloc(sizeof(char) * 100);
        DWORD status = ::GetPrivateProfileStringA(section.c_str(), name.c_str(), "", temp, 100, this->lpFileNameA);
        free(temp);
        if (!status)
            return CInI::INI_READ_NOTEXIST;

        return CInI::INI_READ_EXIST;
    }
    return CInI::INI_READ_NOTEXIST;

}


CInI::InIexstat CInI::InIexistW(const std::wstring& section, const std::wstring& name , const std::wstring& value )
{
    if (section.empty())
        return CInI::INI_READ_NOTEXIST;

    std::vector<wchar_t> temp(100);
    DWORD status = 0;
    int strcomp_temp;
    switch ((name.empty() ? 0 : 1) + (value.empty() ? 0 : 2))
    {
        case 0:
            status = ::GetPrivateProfileSectionW(section.c_str(), temp.data(), temp.size(), this->lpFileNameW);
            break;
        case 1:
            status = InIfindW(section, name).size();//status = ::GetPrivateProfileStringW(section.c_str(), name.c_str(), L"", temp.data(), temp.size(), this->lpFileNameW);
            break;
        case 3:        
            strcomp_temp = InIfindW(section, name).compare(value);
            if(strcomp_temp==0)
                status = 1;
            else
                status = 0;
            break;
    }
    if (!status)
        return CInI::INI_READ_NOTEXIST;

    return CInI::INI_READ_EXIST;
}



CInI::InIexstat CInI::GetAllSectionA(std::vector<std::string>& section_list)
{
    std::vector<char> buffer(1024);
    GetPrivateProfileSectionNamesA(buffer.data(), buffer.size(), this->lpFileNameA);
    int cout = 0;
    for (const char* section = buffer.data(); *section; section += strlen(section) + 1)//walk
        section_list.push_back(section);
    return INI_READ_PATHERROR;
}
CInI::InIexstat CInI::GetAllSectionW(std::vector<std::wstring>& section_list)
{
    std::vector<wchar_t> buffer(1024);
    GetPrivateProfileSectionNamesW(buffer.data(), buffer.size(), this->lpFileNameW);
    int cout = 0;
    // 遍历所有节
    for (const wchar_t* section = buffer.data(); *section; section += wcslen(section) + 1)
        section_list.push_back(section);

    return INI_READ_PATHERROR;
}

int CInI::CountSectionA()
{
    std::vector<char> buffer(1024);
    GetPrivateProfileSectionNamesA(buffer.data(), buffer.size(), this->lpFileNameA);
    int cout = 0;
    for (const char* section = buffer.data(); *section; section += strlen(section) + 1)//walk
        cout++;

    return cout;
}
int CInI::CountSectionW()
{
    std::vector<wchar_t> buffer(1024);
    GetPrivateProfileSectionNamesW(buffer.data(), buffer.size(), this->lpFileNameW);
    int cout = 0;
    // 遍历所有节
    for (const wchar_t* section = buffer.data(); *section; section += wcslen(section) + 1) 
        cout++;

    return cout;
}


int CInI::CountSectionKeyW(const  std::wstring& section)
{
    std::vector<wchar_t> buffer(1024);

    int cout = 0;

    std::vector<wchar_t> data(1024);
    GetPrivateProfileSectionW(section.c_str(), data.data(), data.size(), this->lpFileNameW);

        
    for (const wchar_t* pair = data.data(); *pair; pair += wcslen(pair) + 1) {
            cout++;
    }
    return cout;
}

int CInI::CountSectionKeyA(const  std::string& section)
{
    std::vector<char> buffer(1024);
    int cout = 0;
    
        // all 
    std::vector<char> data(1024);
    GetPrivateProfileSectionA(section.c_str(), data.data(), data.size(), this->lpFileNameA);

        // key
    for (const char* pair = data.data(); *pair; pair += strlen(pair) + 1) {
            cout++;
    }
   
    return cout;
}

CInI::InIexstat CInI::GetAllSectionKeyA(std::vector<std::string>& section_list, std::vector<std::string>& sectionkey_list)
{

    const int bufferSize = 1024;
    char buffer[bufferSize];

    for (const auto& sectionName : section_list)
    {
        GetPrivateProfileStringA(sectionName.c_str(), NULL, NULL, buffer, bufferSize, this->lpFileNameA);

        char* p = buffer;
        while (*p)
        {
            sectionkey_list.push_back(p);
            p += strlen(p) + 1;
        }
    }

    return INI_READ_PATHERROR;
}
CInI::InIexstat CInI::GetAllSectionKeyW(std::vector<std::wstring>& section_list,  std::vector<std::wstring>& sectionkey_list)
{
    const int bufferSize = 1024;
    wchar_t buffer[bufferSize];

    for (const auto& sectionName : section_list)
    {
        GetPrivateProfileStringW(sectionName.c_str(), NULL, NULL, buffer, bufferSize, this->lpFileNameW);

        wchar_t* p = buffer;
        while (*p)
        {
            sectionkey_list.push_back(p);
            p += wcslen(p) + 1;
        }
    }
    return INI_READ_PATHERROR;
}




CInI::InIexstat CInI::GetAllSectionKeyA(const std::string& sectionName, std::vector<std::string>& sectionkey_list)
{
    const int bufferSize = 1024;
    char buffer[bufferSize];

    if (GetPrivateProfileStringA(sectionName.c_str(), NULL, NULL, buffer, bufferSize, this->lpFileNameA) == 0)
        return INI_READ_SECKEY_ERR;

    char* p = buffer;
    while (*p)
    {
        sectionkey_list.push_back(p);
        p += strlen(p) + 1;
    }

    return INI_READ_SECKEY_SUCC;
}

CInI::InIexstat CInI::GetAllSectionKeyW(const std::wstring& sectionName, std::vector<std::wstring>& sectionkey_list)
{
    const int bufferSize = 1024;
    wchar_t buffer[bufferSize];

    if (GetPrivateProfileStringW(sectionName.c_str(), NULL, NULL, buffer, bufferSize, this->lpFileNameW) == 0)
        return INI_READ_SECKEY_ERR;

    wchar_t* p = buffer;
    while (*p)
    {
        sectionkey_list.push_back(p);
        p += wcslen(p) + 1;
    }

    return INI_READ_SECKEY_SUCC;
}





std::vector<CInI::INI_MAP<std::wstring>> CInI::ReadAllW()
{
    std::vector<INI_MAP<std::wstring>> result;
    std::vector<std::wstring> secsave;
    std::vector<std::wstring> keysave;
    GetAllSectionW(secsave);
    result.reserve(secsave.size());
    for (const auto& section : secsave)
    {
        //std::wcout << section << std::endl;
        INI_MAP<std::wstring> iniSection;
        iniSection.section = section;
        GetAllSectionKeyW(section, keysave);
        for (const auto& key : keysave)
        {
            iniSection.parameters[key] = InIfindW(section, key);
        }
        result.push_back(iniSection);
        keysave.clear();
    }
    return result;
}


std::vector<CInI::INI_MAP<std::string>> CInI::ReadAllA()
{
     std::vector<INI_MAP<std::string>> result;
     std::vector<std::string> secsave;
     std::vector<std::string> keysave;
     GetAllSectionA(secsave);
     result.reserve(secsave.size());
     for (const auto& section : secsave)
     {
         //std::cout << section << std::endl;
         INI_MAP<std::string> iniSection;
         iniSection.section = section;
         GetAllSectionKeyA(section, keysave);
         for (const auto& key : keysave)
         {
             iniSection.parameters[key] = InIfindA(section, key);
         }
         result.push_back(iniSection);
         keysave.clear();
     }
     return result;
}

std::vector<CInI::INI_PAIR<std::wstring>> CInI::ReadAllW(int) {
    std::vector<INI_PAIR<std::wstring>> result;
    std::vector<std::wstring> secsave;
    std::vector<std::wstring> keysave;
    GetAllSectionW(secsave);
    result.reserve(secsave.size());
    for (const auto& section : secsave) {
        INI_PAIR<std::wstring> iniSection;
        iniSection.section = section;
        GetAllSectionKeyW(section, keysave);
        for (const auto& key : keysave) {
            iniSection.parameters.emplace_back(key, InIfindW(section, key));
        }
        result.push_back(iniSection);
        keysave.clear();
    }
    return result;
}

std::vector<CInI::INI_PAIR<std::string>> CInI::ReadAllA(int) {
    std::vector<INI_PAIR<std::string>> result;
    std::vector<std::string> secsave;
    std::vector<std::string> keysave;
    GetAllSectionA(secsave);
    result.reserve(secsave.size());
    for (const auto& section : secsave) {
        INI_PAIR<std::string> iniSection;
        iniSection.section = section;
        GetAllSectionKeyA(section, keysave);
        for (const auto& key : keysave) {
            iniSection.parameters.emplace_back(key, InIfindA(section, key));
        }
        result.push_back(iniSection);
        keysave.clear();
    }
    return result;
}

CInI::InIexstat CInI::WriteValueA(const std::string& section, const std::string& key, const std::string& value)
{
    if (!WritePrivateProfileStringA(section.c_str(), key.c_str(), value.c_str(), this->lpFileNameA))
    {
        return INI_WRITE_ERR ;
    }
    return INI_WRITE_SUCC ;
}
CInI::InIexstat CInI::WriteValueW(const std::wstring& section, const std::wstring& key, const std::wstring& value)
{
    if (!WritePrivateProfileStringW(section.c_str(), key.c_str(), value.c_str(), this->lpFileNameW))
    {
        return INI_WRITE_ERR;
    }
    return INI_WRITE_SUCC;
}


char* CInI::wchUTF82StringUFT8(const const wchar_t* pWCStrKey)
{
    int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), NULL, 0, NULL, NULL);
    char* pCStrKey = new char[pSize + 1];

    WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), pCStrKey, pSize, NULL, NULL);
    pCStrKey[pSize] = '\0';

    char* ans;
    int wcsLen = MultiByteToWideChar(CP_UTF8, NULL, pCStrKey, (int)strlen(pCStrKey), NULL, 0);
    wchar_t* wszString = new wchar_t[wcsLen + 1];
    MultiByteToWideChar(CP_UTF8, NULL, pCStrKey, (int)strlen(pCStrKey), wszString, wcsLen);
    wszString[wcsLen] = '\0';
    int len = WideCharToMultiByte(CP_ACP, 0, wszString, (int)wcslen(wszString), NULL, 0, NULL, NULL);
    char* c = new char[len + 1];
    WideCharToMultiByte(CP_ACP, 0, wszString, (int)wcslen(wszString), c, len, NULL, NULL);
    c[len] = '\0';
    delete[] wszString;
    ans = c;
    return ans;
}

std::wstring CInI::strToWstr(std::string input)
{
    size_t len = input.size();
    wchar_t* b = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
    MBCSToUnicode(b, input.c_str());
    std::wstring r(b);
    free(b);
    return r;
}

wchar_t* CInI::MBCSToUnicode(wchar_t* buff, const char* str)
{
    wchar_t* wp = buff;
    char* p = (char*)str;
    while (*p)
    {
        if (*p & 0x80)
        {
            *wp = *(wchar_t*)p;
            p++;
        }
        else
        {
            *wp = (wchar_t)*p;
        }
        wp++;
        p++;
    }
    *wp = 0x0000;
    return buff;
}

