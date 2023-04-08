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
        return "error";//eummark
        free(temp);
    }
    std::string result = temp;
    free(temp);
    return result;
}

std::wstring CInI::InIfindW(std::wstring section, std::wstring name)
{
    WCHAR *content = (wchar_t*)malloc(sizeof(wchar_t) * 200);
    DWORD status = ::GetPrivateProfileStringW(section.c_str(), name.c_str(), TEXT(""), content, 200, this->lpFileNameW);
    std::wstring result = content;
    free(content);
    //return status ? L"INI READ ERROR" : (result.size() == 0 ? L"RESULT NULL" : L"");
    if (!status || result.size()==0)
        return L"";
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

/*CInI::InIexstat CInI::InIWrite(std::string msg)
{

}
CInI::InIexstat CInI::InIWritew(std::wstring msg)
{


}*/

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