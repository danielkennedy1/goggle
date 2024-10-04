cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Goggle VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(goggle
    src/main.cpp
    src/index/file/FileReader.cpp
)

include_directories(
  src/
  src/index/file/
  src/core/
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  index_tests
  tests/filereader_tests.cpp
)

target_sources(index_tests PRIVATE src/index/file/FileReader.cpp)

target_link_libraries(
  index_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(index_tests)
