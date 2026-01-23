cmake_minimum_required(VERSION 3.16)
project(graphics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(test src/test.cpp)

target_link_libraries(test PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)
