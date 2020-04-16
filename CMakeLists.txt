cmake_minimum_required(VERSION 3.10)
project(Scanner LANGUAGES CXX)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(COPY tests DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

configure_file(tests/ms4/hw.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/hw.txt COPYONLY)

bison_target(
        Parser
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.ypp
        ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp
)

flex_target(
        Lex
        src/syntax.l
        ${CMAKE_CURRENT_BINARY_DIR}/syntax.yy.cc
)

ADD_FLEX_BISON_DEPENDENCY(Lex Parser)

message(STATUS
        ${FLEX_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/src)

add_executable(parser
        ${FLEX_INCLUDE_DIRS}
        src/main.cpp
        src/driver.cpp
        src/declarations.hpp
        src/tokens.h src/tokens.cpp
        src/ast.cpp src/ast.hpp
        src/scope_stack.cpp src/scope_stack.hpp
        ${FLEX_Lex_OUTPUTS}
        ${BISON_Parser_OUTPUTS}
        src/semantic_checker.cpp src/semantic_checker.h src/code_generator.cpp src/code_generator.h)

target_include_directories(parser
        PUBLIC ${FLEX_INCLUDE_DIRS})

target_compile_options(parser PRIVATE -Wall -Wpedantic)
if (${CMAKE_VERSION} VERSION_GREATER "3.11")
    target_link_options(parser PRIVATE -Wall -Wpedantic)
endif ()
