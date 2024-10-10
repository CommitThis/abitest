cmake_minimum_required(VERSION 3.16)
project(CxxABITest)

add_library(cxx17lib SHARED cxx17lib.cpp)
# target_compile_features(cxx17lib PRIVATE cxx_std_17)
target_compile_options(cxx17lib PRIVATE -std=gnu++17) 


add_library(cxx98lib SHARED cxx98lib.cpp)
# target_compile_features(cxx98lib PRIVATE cxx_std_98) # Doesn't seem to work
target_compile_options(cxx98lib PRIVATE -std=gnu++98) 
target_compile_definitions(cxx98lib PRIVATE -D_GLIBCXX_USE_CXX11_ABI=0)


add_executable(cxx17main cxx17_main.cpp)
target_link_libraries(cxx17main PRIVATE cxx17lib)

add_executable(cxx98main cxx98_main.cpp)
target_link_libraries(cxx98main PRIVATE cxx98lib)
target_compile_options(cxx98main PRIVATE -std=gnu++98)
target_compile_definitions(cxx98main PRIVATE -D_GLIBCXX_USE_CXX11_ABI=0)
