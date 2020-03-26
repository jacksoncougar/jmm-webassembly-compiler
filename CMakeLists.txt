cmake_minimum_required(VERSION 3.14)
project(Scanner LANGUAGES CXX)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(COPY tests DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

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
        )

target_include_directories(parser
        PUBLIC ${FLEX_INCLUDE_DIRS})

target_compile_options(parser PRIVATE  -Wall -Wpedantic)
target_link_options(parser PRIVATE  -Wall -Wpedantic)

add_custom_command(TARGET parser POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/tests $<TARGET_FILE_DIR:parser>/tests)



file(GLOB_RECURSE TEST_FILES tests/ms3/*.txt)
set(VAR 0)
add_custom_target(ALLTEST)
foreach(test ${TEST_FILES})
    message(STATUS "Creating target for test-file '${test} ${VAR}'")
    if(${VAR} GREATER  0)
        MATH(EXPR PREVIOUS "${VAR}-1")
    endif()
    add_custom_target(test-${VAR}
        COMMAND echo "Running test '${test}'"
        COMMAND cat ${test}
        COMMAND echo "\n"
        COMMAND parser ${test}
            )
                        if(${VAR} GREATER  0)
    message(STATUS "Creating dep.")
    add_dependencies(test-${VAR} test-${PREVIOUS})
    endif()
    add_dependencies(ALLTEST test-${VAR})
    MATH(EXPR VAR "${VAR}+1")
endforeach(test ${TEST_FILES})
