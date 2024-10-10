#include "cxx98lib.hpp"
#include "demangle.hpp"

#include <iostream>

int main()
{
    std::string str = abitest::cxx98::get_string();
    std::cout << "String is: " << str << " (" << demangle<std::string>() << ")\n";
}