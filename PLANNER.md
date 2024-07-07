TODO

* csds_vec.h single header lib (look into vec_header)

* csds_regex.h

* csds_leakcheck.h (simplify everything. get something to work first)

* csds_cachemiss.h (FUTURE)

* More Data Oriented Stuff, does csds_vec.h work well with DOD? (this goes back
  to multivec question)

* csds_list.h (all into one file)

* csds_hash.h (HashMap -> hash_header or something. radically simple)

* csds_leakcheck.h change struct to data oriented (SOA), change functions

* csds_leakcheck.h test support for mutex

* MultiVec: try not to create this struct. Idea is to have elements all next
  to each other in memory in order to reduce cache misses. array of chars ??

* TreeMap, look into rbtree from linux and get inspiration

* Look at Arc from Rust, unique ptr from C++. Try something similar for fun

* csds_defer.h (when need arises, doesn't seem fun to implement)

---

PROJECT REQUIREMENTS

* simple and minimal, easy to integrate and modify

* single header/stb style libraries for each data structure

* custom allocator/deallocator: csds_(alloc|dealloc) macro

* regex support or similar

* more explicit allocations

* leakcheck functionallity

* testing framework

---

VEC REQUIREMENTS

* simple syntax, straightforward declaration: int* vec = NULL;

* alloc if NULL

---

LEARNING RESOURCES

* https://codeplea.com/minctest

* https://github.com/nothings/stb

* https://github.com/nothings/single_file_libs

---

ANSI C vs C99

Like:

* explicit division of variables and code inside a function (ANSI C)

* inline functions (C99)

* snprintf (C99)

Dislike:

* variable length arrays (C99)
