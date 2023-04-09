# The minimum version of CMake required
cmake_minimum_required(VERSION 3.26)

# The project name
project(Physics)


include_directories("/opt/homebrew/Cellar/sfml/2.5.1_2/include")
link_directories("/opt/homebrew/Cellar/sfml/2.5.1_2/lib")


add_executable(Physics main.cpp)
target_link_libraries (Physics -lsfml-graphics -lsfml-window -lsfml-system)