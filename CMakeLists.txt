cmake_minimum_required(VERSION 3.5)

project(Robot)

file(GLOB SOURCES 
    "Libs/Serial/*.cpp"
    "Libs/Display/*.cpp"
    "src/*.cpp"
    )
add_subdirectory(test)
include_directories(${PROJECT_NAME} PUBLIC "inc" "Libs")
# set(CMAKE_C_COMPILER /usr/bin/clang)
# set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabihf-gcc-5)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++-5)
set(CMAKE_CXX_STANDARD 17)
# SET(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
target_link_libraries(${PROJECT_NAME} wiringPi)
target_link_libraries(${PROJECT_NAME} wiringPiDev)
target_link_libraries(${PROJECT_NAME} pthread)