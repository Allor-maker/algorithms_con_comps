add_library(calc_lib STATIC calc.h calc.cpp)


target_include_directories(calc_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})