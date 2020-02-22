cmake_minimum_required(VERSION 3.14)
project(Scanner LANGUAGES CXX)

find_package(FLEX REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${FLEX_Lex_INCLUDES})

file(COPY tests DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

flex_target(Lex src/syntax.l ${CMAKE_CURRENT_BINARY_DIR}/syntax.yy.cc)

add_executable(scanner 
    src/main.cpp
    src/tokens.h 
    src/tokens.cpp
    ${FLEX_Lex_OUTPUTS}
)

target_compile_options(scanner PRIVATE -Wall -Wextra -pedantic -Werror)

file(GLOB_RECURSE TEST_FILES tests/*.t*)
set(VAR 0)
add_custom_target(ALLTEST)
foreach(test ${TEST_FILES})
    message(STATUS "Creating target for test-file '${test}'")
    add_custom_target(test-${VAR} 
        COMMAND echo "Running test '${test}'"
        COMMAND scanner ${test})
    add_dependencies(ALLTEST test-${VAR})
    MATH(EXPR VAR "${VAR}+1")
endforeach(test ${TEST_FILES})


