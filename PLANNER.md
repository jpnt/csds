TODO

* csds_list.h

* csds_rbuf.h

* csds_hash.h

* csds_treemap.h (look at linux rbtree for inspiration)

* csds_bheap.h

* csds_leakcheck.h (simplify everything. get something to work first. prob easier to just use valgrind)

* csds_regex.h

* csds_cachemiss.h (how do we even begin this)

* Look at Arc from Rust, unique ptr from C++. Try something similar for fun

* csds_defer.h (when need arises, doesn't seem fun to implement)

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

---

ANSI C vs C99

Like:

* explicit division of variables and code inside a function (ANSI C)

* inline functions (C99)

* snprintf (C99)

* %zu size_t formatter (C99)

Dislike:

* variable length arrays (C99)
