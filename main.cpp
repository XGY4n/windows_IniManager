#include<iostream>
#include"CInI.h"


void check(const CInI::INI_MAP<std::wstring>* input, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        const auto& data = input[i];
        std::wcout << L"Section: " << data.section << std::endl;
        for (const auto& [key, value] : data.parameters) {
            std::wcout << key << L": " << value << std::endl;
        }
    }
}

int main()
{
    //setlocale(LC_ALL, "chs");
   // std::wcout << InIfindA(L"a", L"s") << std::endl;

    CInI ini(L"./c.ini");

    /*int x = ini.FindValue<int>(L"a", L"x");
    std::cout << x << std::endl;*/
    
    std::string c = ini.FindValue<std::string>(L"a", L"s");
    std::cout << c << std::endl;
    //SetConsoleOutputCP(936);
    std::wstring a = ini.FindValue<std::wstring>(L"a", L"s");
    std::wstring b = ini.FindValue<std::wstring>(L"a", L"x");
    std::cout << a.compare(b) << std::endl;
    double e = ini.FindValue<double>(L"a", L"b");
    std::cout << e << std::endl;
    std::cout << std::endl;

    std::cout << ini.InIexist(L"a", L"e") << std::endl;//0
    std::cout << ini.InIexist(L"a", L"v", L"1") << std::endl;//1
    std::cout << ini.InIexist(L"a", L"v") << std::endl;//1
    std::cout << ini.InIexist(L"a", L"x") << std::endl;//0
    std::cout << ini.InIexist(L"a") << std::endl;//1
    std::cout << ini.InIexist(L"x") << std::endl;//0

    std::cout << std::endl;
    std::cout << ini.CountSection() << std::endl;
    std::cout << ini.CountSectionKey(L"a") << std::endl;
    std::cout << std::endl;

    std::vector<std::wstring> f;
    ini.GetAllSection(f);
    for (auto i : f) {
        std::wcout << i << ' '<<std::endl;
    }
    std::cout << std::endl;
    std::vector<std::wstring> all;
    std::vector<std::wstring> finder;
    ini.GetAllSectionKey(f,all );
    ini.GetAllSectionKey(L"a", finder);
    std::cout<<"all:" << std::endl;;
    for (auto i : all) {
        std::wcout << i << ' ' << std::endl;
    }
    std::cout << std::endl;
    std::cout << "finder:" << std::endl;;
    for (auto i : finder) {
        std::wcout << i << ' ' << std::endl;
    }
    std::cout << std::endl;
    CInI::INI_MAP<std::wstring> save;
    CInI::INI_PAIR<std::wstring> save1;
    /*save = ini.ReadAllW();
    save1 = ini.ReadAllW(_PAIRTYPE_);*/
    std::vector<CInI::INI_MAP<std::wstring>> result = ini.ReadAllW();
    for (const auto& iniSection : result) {
        std::wcout << L"[" << iniSection.section << L"]" << std::endl;
        for (const auto& keyValue : iniSection.parameters) {
            std::wcout << keyValue.first << L"=" << keyValue.second << std::endl;
        }
    }
    std::cout << std::endl;
    //check(save, 10);
    getchar();


	return 0;
}