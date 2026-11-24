cmake_minimum_required(VERSION 3.20)
project(NEXORA_BanglaScript 
    VERSION 1.0.0 
    DESCRIPTION "The Official Compiler, Virtual Machine, CLI and Toolchain for BanglaScript"
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Global compiler flags & optimization
if(MSVC)
    add_compile_options(/W4 /utf-8 /EHsc)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
    if(WIN32)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
    endif()
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include modules
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/compiler/include
    ${CMAKE_CURRENT_SOURCE_DIR}/runtime/include
)

# Optional Flex and Bison support
# If Flex/Bison are found, build rules will regenerate scanner/parser.
# If NOT found, pre-generated C++ files in generated/ will be used seamlessly.
find_package(FLEX 2.6 QUIET)
find_package(BISON 3.7 QUIET)

# Subdirectories
add_subdirectory(compiler)
add_subdirectory(runtime)
add_subdirectory(cli)

# Optional IDE build if Qt6 is found
find_package(Qt6 COMPONENTS Widgets Core Gui QUIET)
if(Qt6_FOUND)
    message(STATUS "Qt6 found - NEXORA IDE target enabled")
    add_subdirectory(ide)
else()
    message(STATUS "Qt6 not found - NEXORA IDE target will be skipped (CLI & Core are independent)")
endif()

# Tests
enable_testing()
add_subdirectory(tests)
