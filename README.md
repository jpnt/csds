# csds - C Simple Data Structures

## Overview

**csds** is a ANSI C/ISO C90 library focused on providing simple implementations
of basic and fundamental data structures.

Designed with clarity and ease of use in mind, this library aims to serve as a
solid foundation for building various applications.

## Data Structures

### Sequence:

- [x] **csds_vec.h** (Dynamic Array)
  - Growable dynamic array that can store any data type.
  - Uses 'hidden' header to keep track of the capacity and length of the vector.
  - Can also be used as a stack or queue.

- [ ] **csds_list.h** (Doubly Linked List)
  - Embeddable list header to put inside other structures, creating a doubly linked list.
  - Suitable for implementing a stack or queue.

- [ ] **csds_rbuf.h** (Circular Array / Ring Buffer)
  - Contiguous block of memory to emulate a wrap-around in memory as if it was circular.

### Hash:

- [ ] **csds_hmap.h** (Hash Map)
  - Used to store key-value pairs and do fast lookups.

- [ ] **csds_hset** (Hash Set)
  - Used to store a collection of unique values

### Tree:

- [ ] **csds_treemap.h** (Balanced Binary Search Tree)
  - Red-black tree that supports insertion, deletion and look-up in O(logN) time.

- [ ] **csds_bheap.h** (Binary Heap)
  - Complete binary tree used to store data efficiently to get the max or min item.
  - Suitable for implementing a priority queue.

### Miscellaneous:

Some of this files do not even contain structures but are still very
useful and were designed to work outside of csds.

- [x] **csds_slice.h** (Pointer + a Length)
  - Provides a length attribute to a pointer to prevent out of bounds errors and
    handles them properly.
  - Intended to use with another types or data.

- [x] **csds_femtotest.h** (Unit Testing Framework)
  - Intended to be the smallest possible "framework" for testing C applications.
  - Used in all tests of this project.

- [x] **csds_error.h** (Error Handling Support)
  - Provide more robust error handling support, all functions return a integer
    which then is treated by the handle_error() function however you want.

## Non-Goals

- "Sort" functions

- "Get" funtions

- "Set" functions

- Support for niche features

- Hidden control flow

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
