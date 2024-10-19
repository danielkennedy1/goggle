cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Goggle VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_definitions(-DTEST_DATA_DIR=\"${CMAKE_SOURCE_DIR}/data/simple_documents\")
add_definitions(-DSERIALIZED_DATA_DIR=\"${CMAKE_SOURCE_DIR}/data/serialized_data\")

add_executable(goggle
    src/main.cpp
    src/index/file/FileReader.cpp
)

include_directories(
  src/
  src/core/
  src/index/
  src/index/file/
)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
  test_index
  test/index/file/FileReader.cpp
  test/index/file/DocumentSet.cpp
  test/index/FrequencyCounter.cpp
)

target_sources(test_index PRIVATE 
  src/index/file/FileReader.cpp
  src/index/FrequencyCounter.hpp
)

target_link_libraries(
  test_index
  GTest::gtest_main
)

add_executable(
  test_core
  test/core/ArrayList.cpp
  test/core/Trie.cpp
)
target_sources(test_core PRIVATE src/core/ArrayList.h)
target_sources(test_core PRIVATE src/core/Trie.hpp)
target_link_libraries(
  test_core
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_index)
gtest_discover_tests(test_core)
