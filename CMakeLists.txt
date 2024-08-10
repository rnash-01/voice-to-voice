cmake_minimum_required(VERSION 3.14)

project(VoiceBackend)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(COPY cpp/test/test.wav DESTINATION ${CMAKE_BINARY_DIR})

include_directories(cpp/src/include)


add_executable(${PROJECT_NAME}
cpp/src/main.cpp
cpp/src/audio/io.cpp
# cpp/src/audio/AudioHandler.cpp
cpp/src/audio/WAVHandler.cpp
cpp/src/data/Buffer.cpp
cpp/src/data/BinaryTree.cpp
cpp/src/task/Task.cpp
)

add_executable(${PROJECT_NAME}_test
cpp/src/audio/io.cpp
# cpp/src/audio/AudioHandler.cpp
cpp/src/audio/WAVHandler.cpp
cpp/src/data/BinaryTree.cpp
cpp/src/data/Buffer.cpp
cpp/src/task/Task.cpp
cpp/src/task/TaskPool.cpp
cpp/src/audio/io_test.cpp
cpp/test/BinaryTree_test.cpp
# cpp/test/AudioHandler_test.cpp
cpp/test/Task_test.cpp
cpp/test/TaskPool_test.cpp
cpp/test/WAVHandler_test.cpp
)

add_executable(${PROJECT_NAME}_sandbox
cpp/src/sandbox.cpp
cpp/src/audio/io.cpp
cpp/src/audio/AudioHandler.cpp
cpp/src/audio/WAVHandler.cpp
cpp/src/data/BinaryTree.cpp
cpp/src/task/Task.cpp
cpp/src/task/TaskPool.cpp
)

target_link_libraries(${PROJECT_NAME}_test gtest_main)
target_include_directories(${PROJECT_NAME}_test PUBLIC cpp/test/include)
add_test(NAME cpp_tests COMMAND ${PROJECT_NAME}_test)
