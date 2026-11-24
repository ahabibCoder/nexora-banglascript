add_executable(banglascript
    src/main.cpp
    src/CommandLine.cpp
    src/REPL.cpp
)

target_include_directories(banglascript PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(banglascript PRIVATE
    banglascript_compiler
    banglascript_runtime
)

# Also create the convenient short alias executable 'bs'
add_executable(bs
    src/main.cpp
    src/CommandLine.cpp
    src/REPL.cpp
)

target_include_directories(bs PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(bs PRIVATE
    banglascript_compiler
    banglascript_runtime
)
