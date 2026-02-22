# Oblivia Language Specification (v0.2.0)

This document describes the currently implemented features of the
Oblivia language.

------------------------------------------------------------------------

# 1. Overview

Oblivia is a statement-oriented interpreted scripting language.

A source file must contain exactly one statement. Complex programs must
wrap multiple statements inside a block `{ ... }`.

Recommended file extension:

    .obl

------------------------------------------------------------------------

# 2. Type System

## 2.1 Implemented Internal Types

-   number
-   string
-   array
-   object (internal only, not usable yet)

## 2.2 Currently Usable Types

Users can currently use:

-   number
-   string
-   array

Array and object literal syntax are not implemented yet.

## 2.3 Number Type

`number` is currently implemented as C `float`.

This means:

-   `==` comparisons may be imprecise
-   Floating-point rounding errors may occur

Future versions may replace this with a more advanced numeric type.

------------------------------------------------------------------------

# 3. Operators

Supported operators:

    +  -  *  /  %
    =  ==  !=  >  <  >=  <=
    += -= *= /= %=
    && || !
    #  ->

## 3.1 Element Dereference Operator (#)

Used for string and array (array not usable yet).

Example:

    "hello"#1

Result:

    "e"

Strings are indexed from 0.

Bracket syntax is supported:

    "hello"[1]

Equivalent to:

    "hello"#1

## 3.2 Object Dereference Operator (-\>)

Object support exists internally but is not currently usable.

------------------------------------------------------------------------

# 4. Statements

Supported statements:

    let
    print
    scan
    if
    else
    while
    break
    continue
    block statement
    expression statement

## 4.1 Variable Declaration (let)

    let a;
    let a = 9;
    let b = "hello";

If not initialized, default value is:

    number(0)

Multiple declarations of the same name in the same scope are allowed.
Only the last declared variable is effective.

## 4.2 Print

    print expr;

Prints the evaluated result to standard output.

Example:

    print "hello world\n";

Supported escape sequences:

    \n  \\  \a  \b  \f  \r  \t  \v  \"

Not supported:

    \'

## 4.3 Scan

    scan expr;

1.  Evaluate expr
2.  Read a string from standard input
3.  Assign it to the evaluated result

The result must be assignable. Otherwise behavior is undefined.

## 4.4 If

    if expr: statement

expr must evaluate to number.

If value != 0 → execute statement.

Example:

    if 1==1:print "giao";

## 4.5 Else

    else statement

Associates with the nearest unmatched if inside the same block.

If no matching if is found, it is syntactically valid but does nothing.

## 4.6 While

    while expr: statement

Evaluates expr before each iteration.

Example:

    while a>0:{
        print a;
        a=a-1;
    }

## 4.7 Break and Continue

Behavior similar to common C-style languages.

They may appear anywhere. If used inside a normal block, execution of
that block stops immediately.

## 4.8 Block Statement

    {
        statement
    }

Empty block `{}` is not allowed.

## 4.9 Expression Statement

If a statement does not begin with a keyword and is not a block, it is
treated as an expression statement.

Example:

    1+1;
    a=a+1;

Empty statement `;` is not allowed.

------------------------------------------------------------------------

# 5. Scope Rules

Scope behavior is similar to C.

Inner scope variables shadow outer ones.

Example:

    {
        let a=9;
        {
            let a=8;
            print a;
        }
        print a;
    }

Output:

    8
    9

------------------------------------------------------------------------

# 6. Source File Rules

A source file must contain exactly one statement.

Valid:

    let a=9;

Or:

    {
        let a=9;
        print a;
    }

------------------------------------------------------------------------

# 7. Example Program

    {
        let a=100;
        while a>0:{
            print a;
            print "\n";
            if a%2==0:{
                print "AAAAA\n";
            }
            else{
                print "BBBBB\n";
            }
            if a==50:{
                break;
            }
            a=a-1;
        }
    }

------------------------------------------------------------------------

# 8. Interpreter Modes

## 8.1 File Execution

    oblivia program.obl

## 8.2 REPL Mode

    oblivia

Users may input a single statement or REPL commands.

## 8.3 REPL Commands

    /exit
    /help

/help currently exists but is not implemented.

------------------------------------------------------------------------

# 9. Arrays

## 9.1 Array Declaration

Arrays can now be declared using the syntax `let name#expr;`, where `expr` must evaluate to a `number`. The result of this expression will be the length of the array. Additionally, the following shorthand is supported: `let name[expr];`. Arrays are initialized with all elements set to `0`.

Example:

    let arr#5;      // Array of length 5
    let arr[3];     // Shorthand for array of length 3

## 9.2 Array Elements

Arrays can store any type of value, including `number`, `string`, or other arrays. The elements of the array can be modified after initialization.

Example:

    let arr[5];
    arr[0] = 10;
    arr[1] = "hello";
    arr[2] = arr;   // Arrays can store themselves (self-references are allowed)

## 9.3 Array Output

The `print` statement can output arrays. The elements of the array will be printed in a space-separated format enclosed in `{}`.

Example:

    let arr[5];
    print arr;      // Output: {0 0 0 0 0}

## 9.4 Array Comparisons and Copying

Arrays support deep comparison using `==` and `!=`, which compares both the length and the values of each element. Assigning one array to another will perform a deep copy, duplicating each element.

Example:

    let arr1[3];
    let arr2[3];
    arr1[0] = 1;
    arr1[1] = 2;
    arr1[2] = 3;
    arr2 = arr1;    // Deep copy of arr1

## 9.5 Self-referencing Arrays

Arrays can reference themselves, creating a loop or self-reference, which will result in a runtime error when output is attempted due to infinite recursion.

Example:

    let a[9];
    a[0] = a;       // Self-referencing array
    print a;        // Will cause a crash (infinite recursion)

------------------------------------------------------------------------

# 10. Identifier Rules

Identifiers can only contain uppercase letters, lowercase letters, and underscores. Numbers are not allowed in identifiers.
