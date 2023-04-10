#include<iostream>
#include"CInI.h"



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
    std::cout << ini.InIexist(L"a", L"s", L"жа") << std::endl;//1
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

    std::vector<CInI::INI_MAP<std::wstring>> result = ini.ReadAll();
    for (const auto& iniSection : result) 
    {
        std::wcout << L"[" << iniSection.section << L"]" << std::endl;
        for (const auto& keyValue : iniSection.parameters)
        {
            std::wcout << keyValue.first << L"=" << keyValue.second << std::endl;
        }
    }
    std::cout<<ini.WriteValue(L"a", L"s", L"88888")<<std::endl;



    std::cout << std::endl;
    //check(save, 10);
    getchar();


	return 0;
}