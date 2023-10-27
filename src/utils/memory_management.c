
#include <stdio.h>
#include <stdlib.h>

// char *ft_malloc(size_t size)

//The realloc() function tries to change the size of the allocation pointed
//to by ptr to size, and returns ptr.  If there is not enough room to
//        enlarge the memory allocation pointed to by ptr, realloc() creates a new
//        allocation, copies as much of the old data pointed to by ptr as will fit
//        to the new allocation, frees the old allocation, and returns a pointer to
//the allocated memory.  If ptr is NULL, realloc() is identical to a call
//        to malloc() for size bytes.  If size is zero and ptr is not NULL, a new,
//        minimum sized object is allocated and the original object is freed.  When
//        extending a region allocated with calloc(3), realloc(3) does not
//guarantee that the additional memory is also zero-filled.