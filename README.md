
# CPP Expression Tree

Header-only C++14 library for creating and evaluating logical expression trees. 

Inspired by m-peko/booleval.

<br/>

This project is under development and is subject to change. Project contributions and issue reports are welcome. The more the merrier! 
( ... well, hopefully not too many bug reports)

## Table of Contents

* [A Quick Example](#a-quick-example)
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
    <img src="docs/booleval-tree.png"/>
</p>

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

This will execute the unit tests and provide a pass/fail indication for each one.
