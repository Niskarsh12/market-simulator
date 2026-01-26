
cmake_minimum_required(VERSION 3.16)
project(market_simulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(market_sim
    src/main.cpp
    src/EventQueue.cpp
    src/Simulator.cpp
    src/NoiseAgent.cpp
)

target_include_directories(market_sim
    PRIVATE include
)

if (MSVC)
    target_compile_options(market_sim PRIVATE /W4)
else()
    target_compile_options(market_sim PRIVATE -Wall -Wextra -Wpedantic)
endif()

