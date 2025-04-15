cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(project3)

# If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

# Path to SFML configuration files
set(SFML_DIR "C:/Users/krist/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

add_executable(project3 main.cpp
        welcome_window.cpp
        game_window.h
        game_window.cpp)
target_link_libraries(project3 sfml-system sfml-window sfml-graphics sfml-audio)