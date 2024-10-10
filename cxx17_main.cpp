#include "cxx17lib.hpp"
#include "demangle.hpp"

#include <iostream>

auto main() -> int
{
    auto str = abitest::cxx17::get_string();
    std::cout << "String is: " << str << " (" << demangle<std::string>() << ")\n";
}