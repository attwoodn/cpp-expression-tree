
# Cpp Expression Tree

Cpp Expression Tree is a header-only, C++14 library for creating logical expression trees and using them to evaluate instances of user-defined data types. 

Inspired by m-peko/booleval.

This project is under development and is subject to change. Project contributions and issue reports are welcome. The more the merrier! 
( ... well, maybe not so much for bug reports)

## Table of Contents

* [A Quick Example](#a-quick-example)
* [Creating Expression Trees](#creating-expression-trees)
* [Types of Expression Tree Nodes](#types-of-expression-tree-nodes)
    * [Expression Tree Leaf Nodes](#expression-tree-leaf-nodes)
    * [Expression Tree Op Nodes](#expression-tree-op-nodes)
* [Logical Operators](#logical-operators)
* [Boolean Operators](#boolean-operators)
* [Using this Library](#using-this-library)
* [Compilation](#compilation)
    * [Running the Unit Tests](#running-the-unit-tests)

## A Quick Example

```cpp
// some code here
// imagine we have some class struct whatever ...
// we can create an expression_tree for evaluating the contents of instances of this struct class whatever
```

Below is a tree diagram showing the content of the expression_tree that was created in the example code above:

<p align="center">
    <img src="docs/expression-tree.png"/>
</p>

## Creating Expression Trees

The expression_tree class is a templated, RAII container class that takes ownership of user-defined expressions. The template parameter of expression_tree is the type of object that the expression_tree can evaluate. The template parameter of expression_tree cannot be a primitive type, like `int` or `char`.

An expression_tree cannot be default constructed - it must be initialized with an expression. Users can easily and intuitively define expressions using one of the `make_expr` helper functions found in the namespace `attwoodn::expression_tree`.

`make_expr` generates heap-allocated pointers to expression tree nodes and returns them. As such, the returned expression tree node pointers should be managed carefully. If the returned pointers are not wrapped in an expression_tree or a smart pointer, they will need to be explicitly `delete`d by the calling code. 

Here are some examples of how you might handle the return value from one of the `make_expr` helper functions:
```cpp
#include <attwoodn/expression_tree.hpp>

using namespace attwoodn::expression_tree;

struct my_type {
   int my_int = 5;
   bool my_bool = true;
};

...

// The heap-allocated expression node pointer returned by make_expr becomes owned by the expression_tree
expression_tree<my_type> expr_tree_raw {
    make_expr(&my_type::my_bool, op::equals, true)
};
 
...

// The heap-allocated expression node pointer returned by make_expr becomes owned by the unique_ptr
std::unique_ptr<node::expression_tree_node<my_type>> smart_expr {
    make_expr(&my_type::my_bool, op::equals, true)
};

// the expression_tree takes ownership of the unique_ptr
expression_tree<my_type> expr_tree_smart(std::move(smart_expr));

...

// The heap-allocated expression node pointer returned by make_expr must be explicitly deleted
auto* expr_raw = make_expr(&my_type::my_bool, op::equals, true);
delete expr_raw;
```

Please see the section below for more information about expression tree nodes.

## Types of Expression Tree Nodes

There are two types of expression tree nodes: leaf nodes and op nodes. 

### Expression Tree Leaf Nodes

Expression tree leaf nodes contain individual, actionable expressions against which a class/struct instance is evaluated. Expression tree leaf nodes are only ever found at the extremities of the expression tree.

### Expression Tree Op Nodes

Expression tree op nodes contain a boolean operation (AND/OR) and have references to a left child node and a right child node. The child nodes may be expression tree leaf nodes, expression tree op nodes, or a permutation of the two. Expression tree op nodes are only ever found in the inner part of the tree. An expression tree op node is always a parent node and it always has two child nodes.

## Logical Operators

There are several logical operator functions defined in the namespace `attwoodn::expression_tree::op`, which can be used to create individual expressions within the tree. The included operators are:
 * equals
 * not_equals
 * less_than
 * greater_than

Users of the library can also easily define their own logical operators and use them when creating expressions. Here is an example of how a user might create their own operator functions and use them in an expression:

```cpp
// some code here
// is_pointer functions: always returns false (value parameters), always returns true (pointer parameters)
```

## Boolean Operators

Boolean operators are used to chain individual expression tree nodes together. There are two boolean operators that can be used: `AND` and `OR`. These boolean operators are accessible via function calls on the expression nodes. Calling these functions generates a new expression tree node which becomes the parent of the nodes on either side of the boolean operator

```cpp
// some code here
// shows how nodes are chained with AND and OR functions
```

A complex expression tree can be created by calling these functions to chain multiple expression tree nodes together.

## Using this Library

To include this library in your project, simply copy the content of the `include` directory into the `include` directory of your project. That's it! Now where did I put that Staples "Easy" button...?

## Compiling

This project uses the CMake build system. The minimum CMake version is set to 3.10.

First, clone the git repository and navigate into the local copy. Once you're there, run the following commands:

```
mkdir build && cd build
cmake ..
make
```

### Running the Unit Tests

After cloning and compiling the project, navigate to the build directory that was created. Enable the `BUILD_TESTING` CMake flag if it is not already enabled. Finally, run:

```
ctest .
```

CTest will execute the unit tests and provide a pass/fail indication for each one.
