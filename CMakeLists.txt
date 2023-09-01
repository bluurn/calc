cmake_minimum_required (VERSION 3.27)
project(calc)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

set(CALC_DEPS_SOURCES
  ./src/lib/error.cpp
  ./src/lib/parser.cpp
  ./src/lib/token.cpp
  ./src/lib/token_kind.cpp
  ./src/lib/token_stream.cpp
)
set(CALC_CMAKE_SOURCES ./src/main.cpp ${CALC_DEPS_SOURCES})
set(CALC_CMAKE_TEST_SOURCES ./src/test.cpp ${CALC_DEPS_SOURCES})

add_executable(${PROJECT_NAME} ${CALC_CMAKE_SOURCES})
add_executable(tests ${CALC_CMAKE_TEST_SOURCES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
