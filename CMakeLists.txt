cmake_minimum_required(VERSION 3.18) # I think this is a release where some fetchcontent stuff got fixed
include(FetchContent)

project(BattleSnek)

# target & file glob
file(GLOB_RECURSE sources src/*.cc)
add_executable(snek-server ${sources})

# compile options
target_compile_options(snek-server PUBLIC
  -march=native -mtune=native -std=c++2b
  -Wall -Wextra -Wpedantic)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# libraries
find_package(fmt)

FetchContent_Declare(Crow
  GIT_REPOSITORY https://github.com/CrowCpp/Crow
  GIT_PROGRESS TRUE
  GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(Crow)

target_link_libraries(snek-server PUBLIC fmt::fmt Crow::Crow)
