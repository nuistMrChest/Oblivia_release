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
-   `array`
-   `reference`

> object syntax exist but are not implemented yet.

------------------------------------------------------------------------

## Supported Statements

-   `let`
-   `print`
-   `scan`
-   `if`
-   `else`
-   `while`
-   `execute`
-   `borrow`
-   `move`
-   `include`
-   block statements `{ ... }`
-   expression statements

------------------------------------------------------------------------

## REPL Commands

-   `/help`
-   `/exit`
-   `/list_variables`
-   `/scope`
-   `/scopr_up`
-   `/scope_down`

------------------------------------------------------------------------

## Usage

### Run a file

    oblivia program.obl

### Start REPL

    oblivia

------------------------------------------------------------------------

## Build

### Requirements

-   C++23 compatible compiler
-   CMake 3.24.4+

------------------------------------------------------------------------

## Linux

### Default Build (Dynamic - glibc)

``` bash
cmake -B build_test -DCMAKE_BUILD_TYPE=Release
cmake --build build_test
```

This builds a dynamically linked binary using your system's glibc.

------------------------------------------------------------------------

### Static Release Build (Alpine Recommended)

⚠️ Fully static builds are officially supported only on **Alpine Linux
(musl)**.\
Building fully static binaries on glibc-based systems (Fedora, Ubuntu,
etc.) is not recommended.

``` bash
cmake -B build_linux \
  -DCMAKE_BUILD_TYPE=Release \
  -DOBLIVIA_STATIC_RELEASE=ON

cmake --build build_linux
```

Official release binaries are built on Alpine Linux using musl and are
fully static. They should run on most modern Linux distributions without
additional runtime dependencies.

------------------------------------------------------------------------

## Windows (MSVC)

### Requirements

-   Visual Studio 2022 or newer
-   CMake 3.24+

``` powershell
cmake -B build_windows -DCMAKE_BUILD_TYPE=Release
cmake --build build_windows --config Release
```

On Windows, the MSVC runtime is linked statically by default, producing
a standalone executable without requiring the VC++ redistributable.

------------------------------------------------------------------------

## macOS

### Requirements

-   Xcode 14+ (or Clang with C++23 support)
-   CMake 3.24+

``` bash
cmake -B build_macos -DCMAKE_BUILD_TYPE=Release
cmake --build build_macos
```

Static release builds are not officially supported on macOS. The default
dynamic build is recommended.

------------------------------------------------------------------------

## Official Release Policy

Official release binaries are provided for:

-   Linux (Alpine-based fully static build)
-   Windows (MSVC static runtime build)

Other platforms may build successfully, but are not officially supported
for static release.


-----------------------------------------------------------------------

## License

MIT License\
See the LICENSE file for details.
