#include<iostream>
#include"CInI.h"

int main()
{


    CInI ini(L"./config.ini");

    int x = ini.FindValue<int>(L"a", L"v");
    std::cout << x << std::endl;
    
    std::string a = ini.FindValue<std::string>(L"a", L"s");
    std::cout << a << std::endl;

    double b = ini.FindValue<double>(L"a", L"b");
    std::cout << b << std::endl;


    /*double y = ini.FindValue<double>("y");
    std::string name = ini.FindValue<std::string>("name");*/
	return 0;
}