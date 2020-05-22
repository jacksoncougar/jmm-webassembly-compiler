# Compiler Construction (CPSC 411) Project
Jackson Cougar Wiebe &bull; University of Calgary &bull; Winter 2020

## Overview

Compiler written in c++ for compiling the fictional language `J--` into `WebAssembly`.

### J--

J-- is a c style language that implements a subset of the Java syntax. 

Valuetypes
- Integers
- Booleans

Strings
- Strings support a small set of escape sequences `\',\",\n,\b,\t,\f,\\`.
- Strings can only be used as arguments to system calls and cannot be used as valuetypes.

Functions
- arguments can be `integer` or `boolean` valuetypes.
- function can return valuetypes (`void` returning is also supported). 

Operators
- built-in binary operators `+,-,*,/,%,<,>,<=,>=,=,==,!=,!,&&,||` and unary operators `-`.

Control Statements
- `break`, `return`, `if`, `if-else`, and `while`

Scope
- Local and globals scopes; nested scopes can be create by opening and closing curly braces (`{`,`}`).

Strong Type Checking
- Everything is type checked at compiler time.


#### Example J-- program

```java
    main() {
        prints("Hello, world!");
    }
```

## Dependancies

- flex (>2.5)
- bison

## Usage

    jcc [INPUT_JMM_FILE]