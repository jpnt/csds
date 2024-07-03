TODO

* csds_femtotest.h (DONE)

* csds_leakcheck.h (simplify everything. get something to work first)

* csds_cachemiss.h (FUTURE)

* csds_vec.h (look into vec_header)

* csds_list.h (all into one file)

* csds_hash.h (HashMap -> hash_header or something. radically simple)

* csds_leakcheck.h change struct to data oriented (SOA), change functions

* csds_leakcheck.h test support for mutex

* MultiVec: try not to create this struct. Idea is to have elements all next
  to each other in memory in order to reduce cache misses. array of chars ??

* TreeMap, look into rbtree from linux and get inspiration

* Look at Arc from Rust, unique ptr from C++. Try something similar for fun

* More Data Oriented Stuff, does csds_vec.h work well with DOD? (this goes back
  to multivec question)

---

PROJECT REQUIREMENTS

* simple and minimal, easy to integrate and modify

* single header/stb style libraries for each data structure

* custom allocator/deallocator: csds_[de]alloc macro

* regex support or similar

* more explicit allocations

* leakcheck functionallity

* testing framework

---

LEARNING RESOURCES

* https://codeplea.com/minctest

* https://github.com/nothings/stb

* https://github.com/nothings/single_file_libs
