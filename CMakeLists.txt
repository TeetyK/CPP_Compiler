cmake_minimum_required(VERSION 3.18)

project(Compiler_TTT VERSION 1.0.0 LANGUAGES CXX)
include(FetchContent)

# FetchContent_Declare(
#   Catch2
#   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#   GIT_TAG        v3.3.2 # Or your desired version
# )

# FetchContent_MakeAvailable(Catch2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# find_package(Catch2 3 REQUIRED NO_VERSION_CHECK)

find_package(CLI11 CONFIG REQUIRED)
find_package(Catch2 3 REQUIRED NO_VERSION_CHECK)
add_executable(program_main src/main.cpp)


target_link_libraries(program_main PRIVATE
    CLI11::CLI11 # Command Line Parse for Complier Argument
    # Catch2WithMain
    # Catch2::Catch2WithMain
    Catch2::Catch2 # TEST CASE for C++
)
if (VCPKG_ROOT)
    vcpkg_link_libraries(Catch2WithMain)
endif()