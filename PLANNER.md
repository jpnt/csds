TODO

NOTE: Some structures will only be done when the need arises.

- [x] csds_vec.h
    - [ ] fix memory leak when it grows
- [ ] csds_list.h
- [ ] csds_rbuf.h
- [ ] csds_hmap.h
- [ ] csds_hset.h
- [ ] csds_treemap.h (linux rbtree based)
- [ ] csds_bheap.h
- [ ] csds_regex.h
- [ ] Doxygen Documentation

---

PROJECT REQUIREMENTS

* simple and minimal, easy to integrate and modify

* custom allocator/deallocator: csds_(alloc|dealloc) macro

* explicit allocations

* testing framework

* error handling

* regex support or similar (when need arises)

* leakcheck functionallity

---

LEARNING RESOURCES

* https://codeplea.com/minctest

* https://github.com/nothings/stb
    * not a big fan of single header libraries, but it has some
      really good ideas

---

ANSI C vs C99

Like:

* explicit division of variables and code inside a function (ANSI C)

* inline functions (C99)

* snprintf (C99)

* %zu size_t formatter (C99)

Dislike:

* variable length arrays (C99)
