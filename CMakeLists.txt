cmake_minimum_required(VERSION 3.14)

project(VoiceBackend)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(cpp/src/include)

add_executable(${PROJECT_NAME}
cpp/src/main.cpp
cpp/src/audio/io.cpp
)

add_executable(${PROJECT_NAME}_test
cpp/src/audio/io_test.cpp
cpp/src/audio/io.cpp
)

target_link_libraries(${PROJECT_NAME}_test gtest_main)
add_test(NAME cpp_tests COMMAND ${PROJECT_NAME}_test)
