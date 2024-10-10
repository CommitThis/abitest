#pragma once

#include <string>

namespace abitest::cxx98 {

std::string get_string();

class widget
{
public:
    widget(std::string const & name)
        : m_name(name)
    {}
private:
    std::string m_name;
};

}