#pragma once
#include <string>
#include <windows.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

#ifdef UNICODE
#define FindValue FindValueW
#else
#define FindValue FindValueA
#endif

#ifdef UNICODE
#define CInIW CInI
#else
#define CInIA CInI
#endif

#ifdef UNICODE
#define InIexist InIexistW
#else
#define InIexist InIexistA
#endif

#ifdef UNICODE
#define GetAllSection GetAllSectionW
#else
#define GetAllSection GetAllSectionA
#endif

#ifdef UNICODE
#define CountSection CountSectionW
#else
#define CountSection CountSectionA
#endif

#ifdef UNICODE
#define CountSectionKey CountSectionKeyW
#else
#define CountSectionKey CountSectionKeyA
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
        /*template<typename RA>
        RA ReadAllA(int index)
        {

        }
        template<typename RA>
        RA ReadAllW(const int index = )
        {

        }*/

    public:
        typedef enum {
            INI_READ_PATHERROR = -0x03,
            INI_WRITE_ERROR = -0x02,
            INI_READ_NOTEXIST = -0x01,
            INI_READ_FIND = 0x00,
            INI_READ_EXIST,
        }InIexstat;

    public:
    #ifdef UNICODE
        template<typename T_INI>
        struct INI_MAP {
            std::wstring section;
            std::map<std::wstring, T_INI> parameters;
        };
        template<typename T_INI>
        struct INI_PAIR {
            std::wstring section;
            std::pair<std::wstring, T_INI> parameters;
        };
        using M_InIData = INI_MAP<std::wstring>;
        using P_InIData = INI_PAIR<std::wstring>;
    #else
        template<typename T_INI>
        struct INI_MAP {
            std::string section;
            std::map<std::string, T_INI> parameters;
        };
        template<typename T_INI>
        struct INI_PAIR {
            std::string section;
            std::pair<std::string, T_INI> parameters;
        };
        using M_InIData = INI_MAP<std::string>;
        using P_InIData = INI_PAIR<std::string>;
    #endif


    public:	
    #ifdef UNICODE
        CInI(const std::wstring& inifile);
    #else
        CInI(const std::string& inifile);
    #endif
       /* CInI(const std::wstring& inifile);
        CInI(const std::string& inifile);*/
	    ~CInI();

    public:

        std::string InIfindA(std::string section, std::string name);
        std::wstring InIfindW(std::wstring section, std::wstring name);

        InIexstat InIexistA(const std::string& section, const std::string& name = "", const std::string& value = "");
        InIexstat InIexistW(const std::wstring& section, const std::wstring& name = L"", const std::wstring& value = L"");

        InIexstat InIWrite(std::string msg );
        InIexstat InIWriteW(std::wstring msg );
    
        InIexstat GetAllSectionA(std::vector<std::string> &section_list);
        InIexstat GetAllSectionW(std::vector<std::wstring> &section_list);

        int CountSectionA();
        int CountSectionW();
        
        int CountSectionKeyA(const std::string& section);
        int CountSectionKeyW(const std::wstring& section);
    private:
        std::string target_ini_path;
        std::wstring wtarget_ini_path;

        LPCSTR lpFileNameA;
        LPCWSTR lpFileNameW;

        
};

