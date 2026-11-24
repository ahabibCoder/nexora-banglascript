add_executable(banglascript_tests
    main.cpp
)

target_link_libraries(banglascript_tests PRIVATE
    banglascript_compiler
    banglascript_runtime
)

target_compile_definitions(banglascript_tests PRIVATE DEBUG=1)
if(NOT MSVC)
    target_compile_options(banglascript_tests PRIVATE -UNDEBUG)
endif()

add_test(NAME BanglaScriptTests COMMAND banglascript_tests)
