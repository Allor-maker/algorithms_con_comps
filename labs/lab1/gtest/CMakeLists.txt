set(target "gtest")

add_library(${target} STATIC gtest-all.cc)

if((${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") AND
    (${CMAKE_SYSTEM_NAME} MATCHES "Linux"))
    set(pthread "-pthread")
endif()

target_link_libraries(${target} ${pthread})

# Указываем путь для поиска заголовочных файлов gtest.h
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Определяем путь для тестовых исходников (для использования с target_link_libraries)
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})