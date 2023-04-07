#pragma once
#include <string>
#include <windows.h>
#include <sstream>
#include<iostream>

#ifdef UNICODE
#define FindValue FindValueW
#else
#define FindValue FindValueA
#endif




class CInI
{
    public :
        template<typename T>
        T FindValueA(const std::string &section, const std::string &name)
        {
            #if defined(NDEBUG) && defined(UNICODE)
                #pragma message("Warning: UNICODE use")
            #endif
            std::string value = InIfindA(section, name);
            if constexpr (std::is_same<T, std::string>::value)
                return value;
            else if constexpr (std::is_same<T, std::wstring>::value)
                return std::wstring(value.begin(), value.end());
            else
            {

                std::stringstream ss(value);
                T result;
                ss >> result;
                return result;
            }
        }

        template<typename T>
        T FindValueW(const std::wstring& section, const std::wstring& name)
        {
            
            std::wstring value = InIfindW(section, name);
            if constexpr (std::is_same<T, std::wstring>::value)
                return value;
            else if constexpr (std::is_same<T, std::string>::value)
                return std::string(value.begin(), value.end());
            else
            {
                std::wstringstream ss(value);
                T result;
                ss >> result;
                return result;
            }
        }


    public:
        typedef enum {
            INI_READ,
            INI_WRITE
        }InIexstat;

    public:	
	    CInI(const std::string &inifile);
        CInI(const std::wstring &inifile);
	    ~CInI();

    public:
        std::string InIRead();
        std::wstring InIReadW();

        std::string InIfindA(std::string section, std::string name);
        std::wstring InIfindW(std::wstring section, std::wstring name);

        InIexstat InIexist(std::string section ,std::string name, std::string vaule);
        InIexstat InIexistW(std::wstring section, std::wstring name, std::wstring vaule);

        InIexstat InIWrite(std::string msg );
        InIexstat InIWriteW(std::wstring msg );

    private:
        std::string target_ini_path;
        std::wstring wtarget_ini_path;

        LPCSTR lpFileNameA;
        LPCWSTR lpFileNameW;
};

