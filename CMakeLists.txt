cmake_minimum_required(VERSION 3.16)

project(BasicShell LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(myshell
    src/main.cpp
    src/shell.cpp
    src/builtins.cpp
    src/parser.cpp
    src/lexer.cpp
)

target_include_directories(myshell PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
