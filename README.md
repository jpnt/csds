# csds - C Simple Data Structures

## Overview

**csds** is a ANSI C/ISO C90 library focused on providing simple implementations
of basic and fundamental data structures.

Designed with clarity and ease of use in mind, this library aims to serve as a
solid foundation for building various applications.

For usage, consult the (./tests/)[tests].

## Data Structures

### Sequences:

- [x] **csds_vec.h** (Dynamic Array)
  - Growable dynamic array that can store any data type.
  - Uses 'hidden' header to keep track of the capacity and length of the vector.

- [ ] **csds_list.h** (Doubly Linked List)
  - Embeddable list header to put inside other structures, creating a doubly linked list.
  - Suitable for implementing a stack or queue.

### Maps:

- [ ] **csds_hash.h** (Hash Table)
  - Used to store key-value pairs and do fast lookups.

- [ ] **csds_treemap.h** (Balanced Binary Search Tree)

### Trees:

- [ ] **csds_rbtree.h** (Red-Black Tree)

- [ ] **csds_avltree.h** (AVL Tree)

### Miscellaneous:

Some of this files do not even contain structures but are still very
useful are were designed to work outside of csds.

- [x] **csds_slice.h** (Pointer + a Length)
  - Intended to use with another types or data.

- [ ] **csds_bheap.h** (Binary Heap)
  - Suitable for implementing a priority queue.

- [x] **csds_femtotest.h** (Unit Testing Framework)
  - Intended to be the smallest possible "framework" for testing C applications.
  - Used in all tests of this project.

- [x] **csds_error.h** (Error Handling Support)
  - Provide more robust error handling support, all functions return a integer
    which then is treated by the handle_error() function however you want.

- [ ] **csds_leakcheck.h** (Memory Debugging)
  - Track allocations, detect leaks, double frees and print memory report.

## Non-Goals

- No "sort" functions

- No "get" funtions

- No "set" functions

- No support for niche features

- No hidden control flow

- Excessive usage of macros

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
