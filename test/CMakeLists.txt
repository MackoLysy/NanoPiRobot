cmake_minimum_required(VERSION 3.5)

project (google_test_example)

add_subdirectory(GTest)

enable_testing()

include_directories(${PROJECT_NAME} PUBLIC "../inc" "../Libs")

file(GLOB SOURCES 
    "../Libs/Serial/*.cpp"
    "../Libs/Display/*.cpp"
    "../src/*.cpp"
    )

add_executable(unit_tests unit_tests.cpp ${SOURCES})

target_link_libraries(
    unit_tests
    GTest::GTest 
    GTest::Main
    wiringPi
    wiringPiDev
    pthread
)

add_test(test_all unit_tests)
