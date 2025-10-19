file(GLOB TEST_SOURCES "*.cpp") 

add_executable(CalculatorTests ${TEST_SOURCES})

add_subdirectory(${CMAKE_SOURCE_DIR}/gtest ${CMAKE_BINARY_DIR}/gtest)

target_link_libraries(CalculatorTests PRIVATE calc_lib interface_lib parser_lib connect_lib stack_lib gtest)

# Указываем путь для поиска заголовков
target_include_directories(CalculatorTests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(CalculatorTests PRIVATE ${CMAKE_BINARY_DIR}/gtest)

# Добавляем команду для автоматического запуска тестов после сборки
add_test(CalculatorTests CalculatorTests)