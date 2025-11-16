cmake_minimum_required(VERSION 3.11)
project(build_setup)

# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Fetch Content
include(FetchContent)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Fetch SFML ####
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)

# Download + add the SFML project
FetchContent_MakeAvailable(SFML)

#### Practical 1 ####
add_executable(game main.cpp)
target_link_libraries(game
    PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)
