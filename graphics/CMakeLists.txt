cmake_minimum_required(VERSION 3.16)
project(graphics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System Audio)
find_package(TGUI REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(main src/main.cpp src/CircleManager.cpp src/EdgeManager.cpp src/Node.cpp src/ChatWindow.cpp src/SimHUD.cpp src/LLM.cpp) 
add_executable(messing_around src/messing_around.cpp)

# Required for cpp-httplib on Windows
if(WIN32)
    target_compile_definitions(main PRIVATE _WIN32_WINNT=0x0A00)
endif()

target_link_libraries(main PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    TGUI::TGUI 
    # OpenSSL provides the actual encryption layer that httplib uses for https support. httplib is just a header file that handles protocol logic (like building requests, parsing responses), it doesn't do encryption itself so we need OpenSSL 
    # if we didn't need to use HTTPS we wouldn't care about OpenSSL, but Groq API requires it 
    OpenSSL::SSL
    OpenSSL::Crypto
    nlohmann_json::nlohmann_json
)

# Windows socket and certificate libraries for httplib
if(WIN32)
    target_link_libraries(main PRIVATE ws2_32 crypt32)
endif()

target_link_libraries(messing_around PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    TGUI::TGUI 
)
