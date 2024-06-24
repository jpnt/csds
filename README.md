# csds - C Simple Data Structures

## Overview

**csds** is a ANSI C/ISO C90 library focused on providing simple implementations
of basic and fundamental data structures. 

Designed with clarity and ease of use in mind, this library aims to serve as a 
solid foundation for building various applications.

## Data Structures

### Sequences:

- [x] **Vec** (Dynamic Array)
  - Growable dynamic array, with configurable growth factor and item type

- [x] **List** (Doubly Linked List)
  - Suitable for implementing a stack or queue

### Maps:

- [ ] **HashMap** (Hash Table)
  - Used to store key-value pairs and do fast lookups

- [ ] **Btmap** (Balanced Binary Search Tree)

### Trees:

- [ ] **Rbt** (Red-Black Tree)

- [ ] **Avl** (AVL Tree)

### Miscellaneous:

- [x] **Slice** (Pointer + a Length)
  - Intended to use with another types or data

- [ ] **MemDebug** (Memory Debugging)
  - Track allocations, detect leaks, double frees and print memory report

- [ ] **Heap** (Binary Heap)
  - Suitable for implementing a priority queue

## Non-Goals

- No "sort" functions

- No "get" funtions

- No "set" functions

- No support for niche features

## Goals

- **Stable:**
  - Provide a solid base for building applications with confidence.

- **Simple:**
  - Do few things and do them well, prioritizing ease of understanding and usage.

- **Extensible:**
  - Contain only the barebones in order to easily integrate and modify when needed.

- **Portable:**
  - Avoid libraries and use old standard to prioritize portability accross multiple systems.

- **Modular:**
  - Separate data structures and functionality, giving the possibility of including just what is needed.

## Contributions

Contributions to this project are welcome!

If you have ideas for new data structures, improvements, or bug fixes, feel free
to open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
