# Oblivia

Oblivia is a lightweight interpreted scripting language with a
statement-oriented execution model.

This repository contains the release version of the Oblivia interpreter.

Repository: https://github.com/nuistMrChest/Oblivia_release

------------------------------------------------------------------------

## Current Version Status

Working components:

-   File interpreter
-   REPL (interactive mode)

### Supported Types

-   `number`
-   `string`

> Array and object syntax exist but are not implemented yet.

------------------------------------------------------------------------

## Supported Statements

-   `let`
-   `print`
-   `scan`
-   `if`
-   `else`
-   `while`
-   block statements `{ ... }`
-   expression statements

------------------------------------------------------------------------

## REPL Commands

-   `/help` (help system not implemented yet)
-   `/exit`

------------------------------------------------------------------------

## Usage

### Run a file

    oblivia program.obl

### Start REPL

    oblivia

------------------------------------------------------------------------

## Build

Requirements:

- C++23 compatible compiler
- CMake 3.24.4+

### Release build (recommended)


cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

-----------------------------------------------------------------------

## License

MIT License\
See the LICENSE file for details.
