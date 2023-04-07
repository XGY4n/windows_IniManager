#include "CInI.h"
CInI::CInI(const std::string &inifile)
{
    this->target_ini_path = inifile;
    lpFileNameA = this->target_ini_path.c_str();
}
CInI::CInI(const std::wstring &inifile)
{
    this->wtarget_ini_path = inifile;
    lpFileNameW = this->wtarget_ini_path.c_str();
}
CInI::~CInI()
{

}

std::string CInI::InIRead()
{
    return "";
}
std::wstring CInI::InIReadW()
{
    return L"";
}

std::string CInI::InIfindA(std::string section, std::string name)
{
    char* temp = (char*)malloc(sizeof(char) * 100);
    DWORD status = ::GetPrivateProfileStringA(section.c_str(), name.c_str(), "", temp, 100, this->lpFileNameA);
    std::string result;
    if (!status)
    {
        return "error";//eummark
        free(temp);
    }
    return result;
}

std::wstring CInI::InIfindW(std::wstring section, std::wstring name)
{
    WCHAR *content = (wchar_t*)malloc(sizeof(wchar_t) * 100);
    DWORD status = ::GetPrivateProfileStringW(section.c_str(), name.c_str(), TEXT(""), content, 100, this->lpFileNameW);
    if (!status)
    {
        return L"error";
        free(content);
    }
    return content;
}

/*CInI::InIexstat CInI::InIWrite(std::string msg)
{

}
CInI::InIexstat CInI::InIWritew(std::wstring msg)
{

}*/