cmake_minimum_required(VERSION 3.14)

project(VoiceBackend)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(COPY test/test.wav DESTINATION ${CMAKE_BINARY_DIR})

include_directories(src/include)


add_executable(${PROJECT_NAME}
src/main.cpp
src/audio/io.cpp
# src/audio/AudioHandler.cpp
src/audio/WAVHandler.cpp
src/data/Buffer.cpp
src/data/BinaryTree.cpp
src/task/Task.cpp
)

add_executable(${PROJECT_NAME}_test
src/audio/io.cpp
# src/audio/AudioHandler.cpp
src/audio/WAVHandler.cpp
src/data/BinaryTree.cpp
src/data/Buffer.cpp
src/task/Task.cpp
src/task/TaskPool.cpp
src/processing/Spectrogram.cpp
test/io_test.cpp
test/BinaryTree_test.cpp
# test/AudioHandler_test.cpp
test/Task_test.cpp
test/TaskPool_test.cpp
test/WAVHandler_test.cpp
test/Spectrogram_test.cpp
)

add_executable(${PROJECT_NAME}_sandbox
src/sandbox.cpp
src/audio/io.cpp
src/audio/AudioHandler.cpp
src/audio/WAVHandler.cpp
src/data/BinaryTree.cpp
src/task/Task.cpp
src/task/TaskPool.cpp
src/processing/Spectrogram.cpp
)

target_link_libraries(${PROJECT_NAME}_test gtest_main)
target_include_directories(${PROJECT_NAME}_test PUBLIC test/include)
add_test(NAME cpp_tests COMMAND ${PROJECT_NAME}_test)
