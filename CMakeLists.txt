cmake_minimum_required(VERSION 3.24.4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(OBLIVIA_STATIC_RELEASE
    "Build fully static Linux release binary (recommended on Alpine)"
    OFF
)

project(oblivia LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(OBLIVIA_SOURCES
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
    ./TypeSystem/implement/reference.cpp
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
    ./Statement/implement/execute.cpp
    ./Statement/implement/move.cpp
    ./Statement/implement/borrow.cpp
)

# Windows only: add icon resource
if (WIN32)
    list(APPEND OBLIVIA_SOURCES resource.rc)
endif()

add_executable(oblivia ${OBLIVIA_SOURCES})

# Windows: always build with static MSVC runtime
if (MSVC)
    set_property(TARGET oblivia PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    )

# Linux static release (recommended on Alpine)
elseif(OBLIVIA_STATIC_RELEASE)
    target_link_options(oblivia PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
    )
endif()