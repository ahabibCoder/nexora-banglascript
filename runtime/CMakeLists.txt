add_library(banglascript_runtime STATIC
    src/VirtualMachine.cpp
)

target_include_directories(banglascript_runtime PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(banglascript_runtime PUBLIC
    banglascript_compiler
)
