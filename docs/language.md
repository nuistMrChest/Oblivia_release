# Oblivia Programming Language

## 1. Right Values

Currently, Oblivia provides five built-in types:

-   number\
-   string\
-   array\
-   reference\
-   object 

### 1.1 Number

In this version, `number` is implemented as C `float`.

Division is floating-point division.\
Modulo uses floating-point `fmod` behavior.

Examples:

    3 / 2;
    3 % 2;

Boolean rules:

-   `0` is false
-   Any non-zero value is true
-   All comparison and logical operators return `1` for true

------------------------------------------------------------------------

### 1.2 String

There is no `char` type, only `string`.

Properties:

-   Strings are immutable.
-   Accessing a single character returns a one-character string.
-   Supported escape sequences:

```{=html}
<!-- -->
```
    \n \" \a \b \f \r \t \v \\

`\'` is illegal.

------------------------------------------------------------------------

### 1.3 Array

Arrays are fixed-length contiguous memory blocks.

-   Length cannot change after creation.
-   Different elements can store different types.
-   Default value of each element is `0`.

Example:

    let a[5];
    a[0] = 10;

Internally:

    a#(0)

`#` is the array element access operator.

------------------------------------------------------------------------

### 1.4 Object

Objects are like dicts in pyhton. They are contiguous memory blocks,but indexed by identifier.

-   Length can be changed by adding attributes.
-   Different attribute can store different types.
-   Default value of each element is `0`.

Example:

    let a@;
    a+=b;
    a->b="giao";

`->`is the attribute access operator.

------------------------------------------------------------------------

### 1.5 Reference

Reference has no literal and can only be used in borrow statement.\
It acts like what references do in c++.

------------------------------------------------------------------------

## 2. Left Values

There are three reference types:

-   variable\
-   array element\
-   object attribute

Right values must be stored in left values, otherwise they are literals.

------------------------------------------------------------------------

### 2.1 Variable

Variables are dynamically typed.

Rules:

-   Must have a name.
-   Default value is `0`.
-   Identifier characters: `a-z`, `A-Z`, `_`
-   Digits are not allowed.
-   Keywords are currently allowed but not recommended.

Examples:

    let a;
    let b = 10;

If initialized through borrow statement, all the calculation of it is the calculation of it's refered left value.

------------------------------------------------------------------------

### 2.2 Array Element

Array elements are left values inside arrays.

Example:

    let a[3];
    a[0] = 5;

------------------------------------------------------------------------

### 2.3 Object Attribute

Object attributes are left values inside objects.

Example:

    let a@;
    a+=b;
    a->b="giao";

------------------------------------------------------------------------

## 3. Expressions

Supported operators:

    + - * / % = == != > < >= <= && || ! # -> += -= *= /= %=

### 3.1 Operator Priority

From highest to lowest:

    8  : # ->
    7  : !
    6  : * / %
    5  : + -
    4  : > < >= <=
    3  : == !=
    2  : &&
    1  : ||
    0  : = += -= *= /= %=

### 3.2 Associativity

Right associative:

    ! = += -= *= /= %=

All others are left associative.

### 3.3 Deep Copy and Deep Compare

-   All assignments perform deep copy.
-   All comparisons perform deep comparison.

### 3.4 Expression Rules

After removing unary `!`, the checker sees only:

-   value
-   operator

Legal expression rules:

1.  Must alternate between value and operator.
2.  Must start and end with value.

Parentheses are validated recursively and replaced as value during
checking.

Unary `!` must be followed by:

-   value
-   `(`
-   another `!`

Example of legal but runtime-error expression:

    1 = 1;

------------------------------------------------------------------------

## 4. Statements

Three types:

-   normal statement\
-   expression statement\
-   block

A statement must end with `;` or be wrapped in `{}`.

------------------------------------------------------------------------

### 4.1 Block

A block contains more than one statement and defines scope.

Example:

    {
        let a = 9;
        {
            let a = 8;
            print a;
        }
        print a;
    }

------------------------------------------------------------------------

### 4.2 Expression Statement

An expression followed by `;`.

    a = 10;
    1 + 1;

------------------------------------------------------------------------

### 4.3 Let

Variable declaration.

Examples:

    let a;
    let b = 1 + 9;
    let c = "giao";
    let d[3];
    let e[9];

------------------------------------------------------------------------

### 4.4 Print

Prints evaluated expression to stdout.

    print "Hello World!\n";

------------------------------------------------------------------------

### 4.5 Scan

Reads input as string and assigns to assignable reference.

    scan a;

------------------------------------------------------------------------

### 4.6 If

    if expr:stat

`expr` must evaluate to number.

------------------------------------------------------------------------

### 4.7 Else

    else stat;

Links to nearest previous `if` in same block.

------------------------------------------------------------------------

### 4.8 While

    while expr:stat

Repeats while `expr` is non-zero.

------------------------------------------------------------------------

### 4.9 Break

    break;

Stops nearest `while` loop.

------------------------------------------------------------------------

### 4.10 Continue

    continue;

Skips to next loop iteration.

------------------------------------------------------------------------

### 4.11 Execute

    execute expr;

`expr` must evaluate to string containing a legal Oblivia statement.

Example:

    execute "print\"hello\";";

------------------------------------------------------------------------

### 4.12 Move

    move expr_a,expr_b;

The result of both `expr_a` and `expr_b` must be a left value.\
Value stored in the result pf `expr_a` moves to the result of `expr_b`, and replaced with number 0.\
Although references behaves like whatever they are refered to in expressions, in move statements, moving a reference is literally move the reference it self, not the thing it refered to.

------------------------------------------------------------------------

### 4.13 Borrow

    borrow expr,a;

The result of `expr` must be a left value.\
Initialize a variable named `a` with a reference pointed towards the result of `expr`.

------------------------------------------------------------------------

### 4.14 Include

    include expr;

The result of expr must be a string.\
The string must be a legal path to an oblivia source file. Unlike the file that will be runned directly by the interpreter, the file included only need to be several legal oblivia statement.\
The basic scope of the statements inside the included file is the scope level og the include statement.

------------------------------------------------------------------------

## 5. Interpreter

Two modes:

-   REPL mode
-   File mode

### 5.1 REPL Mode

Commands:

    /exit
    /help
    /list_variables
    /scope
    /scope_up
    /scope_down

Statements are tokenized, checked, built, and executed.

------------------------------------------------------------------------

### 5.2 File Mode

The entire main file must be a legal statement.

Example:

    print "Hello World!\n";

Or:

    {
        let a = 100;
        while a > 0:{
            print a;
            print "\n";
            if a % 2 == 0:{
                print "AAAAA\n";
            }
            else{
                print "BBBBB\n";
            }
            if a == 50:{
                break;
            }
            a = a - 1;
        }
    }
