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
    ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp
)

add_library(bison_flex STATIC
${FLEX_Lex_OUTPUTS}
${BISON_Parser_OUTPUTS}
)

target_include_directories(bison_flex PUBLIC build/)

message(STATUS "HI ${BISON_Parser_OUTPUTS}")



add_executable(parser 
    src/main.cpp 
    src/driver.cpp 
    src/declarations.hpp 
    src/tokens.h src/tokens.cpp
    src/ast.cpp src/ast.hpp
)

target_link_libraries(parser bison_flex)

target_compile_options(parser PRIVATE -Wall)

file(GLOB_RECURSE TEST_FILES tests/ms2/*.txt TEST/ms2/*.t??  TEST/ms2/*.t?)
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
