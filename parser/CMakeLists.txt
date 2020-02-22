find_package(BISON)

BISON_TARGET(parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.h)
             
add_executable(parser main.cpp ${BISON_MyParser_OUTPUTS})

add_executable(parser 
    src/main.cpp
)