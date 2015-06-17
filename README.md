# MemoryPool
Single Thread MemoryPool - just for practice

_BKE_allocator is the global singleton class for a fixed-size memory pool, and BKE_allocator is a wrapper for spercific type.

Allow manually shrink to free the memory to system.

dynamic_allocate function is used when malloc object with different size on runtime. We init many _BKE_allocator first and store them in an array, then retrive them according to a spercific size. The return pointer's type is always _BKE_allocator<1>* while they can allocate memory of correct size.