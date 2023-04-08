#include<iostream>
#include"CInI.h"

int main()
{


    CInI ini(L"./config.ini");

    int x = ini.FindValue<int>(L"a", L"v");
    std::cout << x << std::endl;
    
    std::string c = ini.FindValue<std::string>(L"a", L"s");
    std::cout << c << std::endl;

    std::wstring a = ini.FindValue<std::wstring>(L"a", L"e");
    std::wcout << a << std::endl;

    double b = ini.FindValue<double>(L"a", L"b");
    std::cout << b << std::endl;

    std::cout << ini.InIexist(L"a", L"e") << std::endl;//-1
    std::cout << ini.InIexist(L"a", L"v", L"1") << std::endl;//1
    std::cout << ini.InIexist(L"a", L"v") << std::endl;//1
    std::cout << ini.InIexist(L"a", L"x") << std::endl;//-1
    std::cout << ini.InIexist(L"a") << std::endl;//1
    std::cout << ini.InIexist(L"x") << std::endl;//-1

    std::cout << ini.CountSection() << std::endl;
    std::cout << ini.CountSectionKey(L"a") << std::endl;

    std::vector<std::wstring> f;
    ini.GetAllSection(f);
    for (auto i : f) {
        std::wcout << i << ' '<<std::endl;
    }




	return 0;
}