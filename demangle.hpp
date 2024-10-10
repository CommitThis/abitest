#include <memory>
#include <string>

#include <cxxabi.h>


#if __cplusplus >= 201103L 

template <class T>
auto demangle() -> std::string
{
    using without_ref_t = typename std::remove_reference<T>::type;
    std::unique_ptr<char, void(*)(void*)> own
           (
                abi::__cxa_demangle(
                        typeid(without_ref_t).name(),
                        nullptr,
                        nullptr, 
                        nullptr),
                std::free
           );
    std::string r = own != nullptr ? own.get() : typeid(without_ref_t).name();
    if (std::is_const<without_ref_t>::value)
        r += " const";
    if (std::is_volatile<without_ref_t>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

#else

#include <cstdlib>

namespace detail {

template<class T, T v>
struct integral_constant { static const T value = v; };

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template<class T> struct remove_reference { typedef T type; };
template<class T> struct remove_reference<T&> { typedef T type; };

template<class T> struct is_const          : false_type {};
template<class T> struct is_const<const T> : true_type {};

template<class T> struct is_lvalue_reference     : false_type {};
template<class T> struct is_lvalue_reference<T&> : true_type {};

template<class T> struct is_volatile             : false_type {};
template<class T> struct is_volatile<volatile T> : true_type {};
}

template <class T>
std::string demangle()
{
    typedef typename detail::remove_reference<T>::type without_ref_t;

    char * own = abi::__cxa_demangle(
                        typeid(without_ref_t).name(),
                        NULL,
                        NULL, 
                        NULL);

    std::string r = own != NULL ? own : typeid(without_ref_t).name();
    if (detail::is_const<without_ref_t>::value)
        r += " const";
    if (detail::is_volatile<without_ref_t>::value)
        r += " volatile";
    if (detail::is_lvalue_reference<T>::value)
        r += "&";

    std::free(own);
    return r;
}


#endif