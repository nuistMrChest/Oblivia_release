cmake_minimum_required(VERSION 3.24.4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(oblivia)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

add_executable(oblivia 
    main.cpp
    ./implement/relp.cpp
    ./implement/interpreter.cpp

    ./Situation/implement/situation.cpp

    ./TypeSystem/implement/string.cpp
    ./TypeSystem/implement/array.cpp 
    ./TypeSystem/implement/number.cpp
    ./TypeSystem/implement/object.cpp
    ./TypeSystem/implement/value.cpp
    ./TypeSystem/implement/variable.cpp
    ./TypeSystem/implement/operator.cpp

    ./Tokenize/implement/checker.cpp
    ./Tokenize/implement/tokenize.cpp

    ./Expression/implement/expression.cpp
    
    ./Statement/implement/block.cpp
    ./Statement/implement/break.cpp
    ./Statement/implement/continue.cpp
    ./Statement/implement/else.cpp
    ./Statement/implement/expr.cpp
    ./Statement/implement/if.cpp
    ./Statement/implement/let.cpp
    ./Statement/implement/print.cpp
    ./Statement/implement/scan.cpp
    ./Statement/implement/statement.cpp
    ./Statement/implement/while.cpp
)
# ===== Static build configuration =====

if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    target_link_options(oblivia PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
    )
endif()