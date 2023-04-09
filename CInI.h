#pragma once
#include <string>
#include <windows.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <comutil.h>  
#include <tchar.h>
#include <windows.h>
#include <comutil.h>  
#include <unknwn.h>
#include <queue>
#include <thread>
#include <stdio.h>
#include <deque>
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
#define GetAllSectionKey GetAllSectionKeyW
#else
#define GetAllSectionKey GetAllSectionKeyA
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



#ifdef UNICODE
#define ReadAll ReadAllW
#else
#define ReadAll ReadAllA
#endif


#define _MAPTYPE_ 1
#define _PAIRTYPE_ 2


class CInI
{

    public :
        template<typename T>
        T  FindValueW(const std::wstring& section, const std::wstring& name)
        {

            std::wstring value = InIfindW(section, name);
            if constexpr (std::is_same<T, std::wstring>::value)
                return value;
            else if constexpr (std::is_same<T, std::string>::value)
                return wchUTF82StringUFT8(value.c_str());
            else
            {
                std::wstringstream ss(value);
                T result;
                ss >> result;
                return result;
            }
        }

        template<typename T>
        T FindValueA(const std::string& section, const std::string& name)
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
        template<typename RA>
        RA ReadAllT() {
            RA result;
            // Process the data and store the result in result
            // ...
            return result;
        }
        /*template<typename RA>
        RA ReadAllA(RA& data)
        {
            if constexpr (std::is_same_v<RA, INI_MAP<std::wstring>>)
                return 1;
            else //if constexpr (std::is_same<T, std::wstring>::value)
                return 2;
        }
        template<typename RA>
        RA ReadAllW()
        {
            if constexpr (std::is_same_v<RA, INI_MAP<std::wstring>>)
                return 1;
            else //if constexpr (std::is_same<T, std::wstring>::value)
                return 2;
        }*/

    public:
        typedef enum {
            INI_READ_PATHERROR = -0x03,
            INI_WRITE_ERROR = -0x02,
            INI_READ_SECKEY_ERR = 0x00,
            INI_READ_SECKEY_SUCC = 0x01,

            INI_READ_NOTEXIST = 0x00,
            INI_READ_FIND = 0x01,
            INI_READ_EXIST = 0x01,
        }InIexstat;

    public:
    #ifdef UNICODE
        template<typename T_INI>
        struct INI_MAP {
            std::wstring section;
            std::map<std::wstring, std::wstring> parameters;
        };
        template<typename T_INI>
        struct INI_PAIR {
            std::wstring section;
            std::vector<std::pair<std::wstring, T_INI>> parameters;
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

        InIexstat GetAllSectionKeyA(std::vector<std::string>& section_list, std::vector<std::string>& sectionkey_list );
        InIexstat GetAllSectionKeyW(std::vector<std::wstring>& section_list,  std::vector<std::wstring>& sectionkey_list);

        InIexstat GetAllSectionKeyA(const std::string & sectionName, std::vector<std::string>& sectionkey_list);
        InIexstat GetAllSectionKeyW(const std::wstring & sectionName, std::vector<std::wstring>& sectionkey_list);

        int CountSectionA();
        int CountSectionW(); 
        
        int CountSectionKeyA(const std::string& section);
        int CountSectionKeyW(const std::wstring& section);

        P_InIData ReadAllW(int);
        std::vector<INI_MAP<std::wstring>> ReadAllW();

        M_InIData ReadAllA();
        P_InIData ReadAllA(int);

        /*M_InIData ReadAllW();
        P_InIData ReadAllA(int);*/


    private:
        std::string target_ini_path;
        std::wstring wtarget_ini_path;

        LPCSTR lpFileNameA;
        LPCWSTR lpFileNameW;

    private:
        char* wchUTF82StringUFT8(const  wchar_t* pWCStrKey);
        //std::string wstrToStr(std::wstring& wstr);
        wchar_t* MBCSToUnicode(wchar_t* buff, const char* str);
        std::wstring strToWstr(std::string input);

};

