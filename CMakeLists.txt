cmake_minimum_required(VERSION 3.25)
project(seabattle)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SRCFILES "*.cpp")

add_executable(seabattle)
target_sources(seabattle PRIVATE ${SRCFILES})

target_link_libraries(seabattle sfml-graphics sfml-window sfml-system)


# add_subdirectory(states)