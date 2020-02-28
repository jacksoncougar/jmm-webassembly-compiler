cmake_minimum_required(VERSION 3.14)
project(Scanner LANGUAGES CXX)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

file(COPY tests DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

flex_target(
    Lex 
    src/syntax.l 
    ${CMAKE_CURRENT_BINARY_DIR}/syntax.yy.cc
)

bison_target(
    Parser 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.ypp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.cpp
    DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.hpp
)

include_directories(${FLEX_Lex_INCLUDES})
include_directories(${BISON_Parser_INCLUDES})


add_executable(parser 
    ${FLEX_Lex_OUTPUTS}
    ${BISON_Parser_OUTPUTS}
    src/main.cpp 
    src/driver.cpp 
    src/declarations.hpp 
    src/tokens.h src/tokens.cpp
    src/ast.cpp src/ast.hpp
)

target_compile_options(parser PRIVATE -Wall)

file(GLOB_RECURSE TEST_FILES tests/ms2/*.txt TEST/ms2/*.t??)
set(VAR 0)
add_custom_target(ALLTEST)
foreach(test ${TEST_FILES})
    message(STATUS "Creating target for test-file '${test} ${VAR}'")
    if(${VAR} GREATER  0)
        MATH(EXPR PREVIOUS "${VAR}-1")
    endif()
    add_custom_target(test-${VAR} 
        COMMAND echo "Running test '${test}'"
        COMMAND parser ${test}
            )
                        if(${VAR} GREATER  0)
    message(STATUS "Creating dep.")
    add_dependencies(test-${VAR} test-${PREVIOUS})
    endif()
    add_dependencies(ALLTEST test-${VAR})
    MATH(EXPR VAR "${VAR}+1")
endforeach(test ${TEST_FILES})
