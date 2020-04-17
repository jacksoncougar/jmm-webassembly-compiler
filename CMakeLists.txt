cmake_minimum_required(VERSION 3.10)
project(Scanner LANGUAGES CXX)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(COPY tests DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

configure_file(tests/ms4/hw.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/hw.txt COPYONLY)
configure_file(tests/ms4/return_values.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/return_values.txt COPYONLY)
configure_file(tests/ms4/sum.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/sum.txt COPYONLY)
configure_file(tests/ms4/global_int.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/global_int.txt COPYONLY)
configure_file(tests/ms4/printi_tests.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/printi_tests.txt COPYONLY)
configure_file(tests/ms4/printc_tests.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/printc_tests.txt COPYONLY)
configure_file(tests/ms4/printb_tests.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/printb_tests.txt COPYONLY)
configure_file(tests/ms4/prints_tests.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/prints_tests.txt COPYONLY)
configure_file(tests/ms4/unary.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/unary.txt COPYONLY)
configure_file(tests/ms4/gen.t22 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t22 COPYONLY)
configure_file(tests/ms4/art-life.jmm ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/art-life.jmm COPYONLY)
configure_file(tests/ms4/art-select.jmm ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/art-select.jmm COPYONLY)
configure_file(tests/ms4/art-sieve.jmm ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/art-sieve.jmm COPYONLY)
configure_file(tests/ms4/gen.t1 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t1 COPYONLY)
configure_file(tests/ms4/gen.t5 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t5 COPYONLY)
configure_file(tests/ms4/gen.t10 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t10 COPYONLY)
configure_file(tests/ms4/gen.t11 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t11 COPYONLY)
configure_file(tests/ms4/gen.t12 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t12 COPYONLY)
configure_file(tests/ms4/gen.t13 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t13 COPYONLY)
configure_file(tests/ms4/gen.t14 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t14 COPYONLY)
configure_file(tests/ms4/gen.t15 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t15 COPYONLY)
configure_file(tests/ms4/gen.t18 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t18 COPYONLY)
configure_file(tests/ms4/gen.t26 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t26 COPYONLY)
configure_file(tests/ms4/gen.t29 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t29 COPYONLY)
configure_file(tests/ms4/gen.t30 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t30 COPYONLY)
configure_file(tests/ms4/gen.t31 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t31 COPYONLY)
configure_file(tests/ms4/gen.t32 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t32 COPYONLY)
configure_file(tests/ms4/gen.t33 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t33 COPYONLY)
configure_file(tests/ms4/gen.t34 ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/gen.t34 COPYONLY)
configure_file(tests/ms4/more-random.txt ${CMAKE_CURRENT_BINARY_DIR}/tests/ms4/more-random.txt COPYONLY)

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
        src/semantic_checker.cpp src/semantic_checker.h src/code_generator.cpp src/code_generator.h src/runtime_library.cpp src/runtime_library.h)

target_include_directories(parser
        PUBLIC ${FLEX_INCLUDE_DIRS})

target_compile_options(parser PRIVATE -Wall -Wpedantic)
if (${CMAKE_VERSION} VERSION_GREATER "3.11")
    target_link_options(parser PRIVATE -Wall -Wpedantic)
endif ()

file(GLOB_RECURSE TEST_FILES tests/ms4/*.txt tests/ms4/*.t[0-9][0-9] tests/ms4/*.t[0-9] tests/ms4/*.jmm)
set(VAR 0)
add_custom_target(ALLTEST)
foreach (test ${TEST_FILES})
    message(STATUS "Creating target for test-file '${test} ${VAR}'")
    if (${VAR} GREATER 0)
        MATH(EXPR PREVIOUS "${VAR}-1")
    endif ()
    get_filename_component(OUT ${test} NAME)
    add_custom_target(test-${VAR}
            COMMAND echo "\n"
            COMMAND echo "\n"
            COMMAND echo "Running test '${test}'"
            COMMAND echo parser ${test} > ${OUT}.wat
            COMMAND parser ${test} > ${OUT}.wat
            COMMAND ${CMAKE_CURRENT_LIST_DIR}/uat.sh ${OUT}.wat
            echo console.txt
            )
    if (${VAR} GREATER 0)
        message(STATUS "Creating dep.")
        add_dependencies(test-${VAR} test-${PREVIOUS})
    endif ()
    add_dependencies(ALLTEST test-${VAR})
    MATH(EXPR VAR "${VAR}+1")
endforeach (test ${TEST_FILES})