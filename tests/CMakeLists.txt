add_executable(banglascript_tests
    main.cpp
)

target_link_libraries(banglascript_tests PRIVATE
    banglascript_compiler
    banglascript_runtime
)

add_test(NAME BanglaScriptTests COMMAND banglascript_tests)
