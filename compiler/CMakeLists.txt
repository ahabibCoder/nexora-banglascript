add_library(banglascript_compiler STATIC
    src/ast/AST.cpp
    src/ast/ASTPrettyPrinter.cpp
    src/semantic/TypeChecker.cpp
    src/ir/TACGenerator.cpp
    src/optimizer/Optimizer.cpp
    src/parser/Driver.cpp
    generated/parser.tab.cpp
    generated/lex.yy.cpp
)

target_include_directories(banglascript_compiler PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/generated
)
