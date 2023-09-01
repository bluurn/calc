cmake_minimum_required (VERSION 3.27)
project (calc)
set( LEARN_CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( LEARN_CMAKE_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR} )

set( LEARN_CMAKE_SOURCES 
        calc.cpp
        error.cpp
        parser.cpp
        token.cpp
        token_kind.cpp
        token_stream.cpp
)
add_executable( ${PROJECT_NAME} ${LEARN_CMAKE_SOURCES} )
