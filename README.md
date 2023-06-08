# Raytrace2

## Conventions

### Basic conventions

Do not use the standard namespace library, especially in header files.

<h5 a><strong>Wrong usage: <code>example.h</code></strong></h5>

```cpp
using namespace std; THIS IS WRONG!!!
```

<h5 a><strong>Correct usage: <code>example.h</code></strong></h5>

```cpp
void function() 
{
    std::cout << "Hello" << std::endl;
}
```

After each statement (if, for, foreach, switch, etc), 
the brackets must always go in new line.

Examples:

```cpp
if (...)
{
    // code goes here...
}
```

```cpp
for (...)
{
    // code goes here...
}
```

```cpp
switch (...)
{
    // code goes here...
}
```

```cpp
if (...)
{
    // code goes here...
}
```

### Variables

Every variable should use the camel case naming convention.


```cpp
class Example
{
private:
    int camelCaseExample;
public:
    Example() {};
}
```

```cpp
int main()
{
    int camelCaseExample = 1;

    return 0;
}
```

### Classes

Class names should follow the upper camel case naming convention.

<h5 a><strong>Correct naming: <code>example.h</code></strong></h5>

```cpp
class ExampleClass 
{
}
```

<h5 a><strong>Wrong naming: <code>example.h</code></strong></h5>

```cpp
class exampleClass 
{
}

class example_class 
{
}

class exampleclass 
{
}
```

Classes must be separated into different .h and .cpp files.

Header files must not contain any implementation just the header of the functions and the variable declarations.

<h5 a><strong>Header file: <code>example.h</code></strong></h5>

```cpp
int main()
{
    int camelCaseExample = 1;

    return 0;
}
```

<h5 a><strong>Source file: <code>example.cpp</code></strong></h5>

```cpp
int main()
{
    int camelCaseExample = 1;

    return 0;
}
```

### Functions

Function names should always use the snakecase naming convention.

Example: 

```cpp
void snake_case_example_function() 
{
    // Function body
}
```
