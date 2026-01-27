cmake_minimum_required(VERSION 3.16)
project(graphics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)

add_executable(test src/test.cpp)
add_executable(lines src/lines.cpp)
add_executable(nodes_and_edges src/nodes_and_edges.cpp) 
add_executable(camera src/camera.cpp)

target_link_libraries(test PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

target_link_libraries(lines PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

target_link_libraries(nodes_and_edges PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

target_link_libraries(camera PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)