cmake_minimum_required(VERSION 3.16)
project(graphics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)

add_executable(connecting_edge src/connecting_edge.cpp)
add_executable(main src/main.cpp src/CircleManager.cpp src/EdgeManager.cpp src/Node.cpp)

target_link_libraries(main PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

target_link_libraries(connecting_edge PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)