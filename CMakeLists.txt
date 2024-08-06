cmake_minimum_required(VERSION 3.14)

project(VoiceBackend)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(COPY cpp/src/test/test.wav DESTINATION ${CMAKE_BINARY_DIR})

include_directories(cpp/src/include)

add_executable(${PROJECT_NAME}
cpp/src/main.cpp
cpp/src/audio/io.cpp
# cpp/src/audio/AudioHandler.cpp
cpp/src/audio/WAVHandler.cpp
cpp/src/data/Buffer.cpp
cpp/src/data/BinaryTree.cpp

)

add_executable(${PROJECT_NAME}_test
cpp/src/audio/io.cpp
# cpp/src/audio/AudioHandler.cpp
cpp/src/audio/WAVHandler.cpp
cpp/src/data/BinaryTree.cpp
cpp/src/data/Buffer.cpp
cpp/src/audio/io_test.cpp
cpp/src/test/BinaryTree_test.cpp
# cpp/src/test/AudioHandler_test.cpp
cpp/src/test/Task_test.cpp
cpp/src/test/WAVHandler_test.cpp
)

add_executable(${PROJECT_NAME}_sandbox
cpp/src/sandbox.cpp
cpp/src/audio/io.cpp
cpp/src/audio/AudioHandler.cpp
cpp/src/audio/WAVHandler.cpp
cpp/src/data/BinaryTree.cpp
)

target_link_libraries(${PROJECT_NAME}_test gtest_main)
add_test(NAME cpp_tests COMMAND ${PROJECT_NAME}_test)
