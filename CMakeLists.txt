cmake_minimum_required(VERSION 3.10)
project(autoComander)

set(CMAKE_CXX_STANDARD 11)

# Dodaj folder z FLTK
add_subdirectory(third_party/fltk)

# Twój program
add_executable(autoComander src/main.cpp)

# Linkowanie FLTK
target_link_libraries(autoComander FLTK::FLTK)