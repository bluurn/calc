cmake_minimum_required (VERSION 3.27)
project(calc)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

set(CALC_CMAKE_SOURCES 
  calc.cpp
  error.cpp
  parser.cpp
  token.cpp
  token_kind.cpp
  token_stream.cpp
)

set(CALC_CMAKE_TEST_SOURCES
  test.cpp
  error.cpp
  parser.cpp
  token.cpp
  token_kind.cpp
  token_stream.cpp
)

add_executable(${PROJECT_NAME} ${CALC_CMAKE_SOURCES})
add_executable(tests ${CALC_CMAKE_TEST_SOURCES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
