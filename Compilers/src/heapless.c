#include <stdlib.h>             /* for malloc and free */

#ifndef USE_HEAP                /* If you want a heap, you must ask */
void *malloc(size_t amt) {
    return (void *) 0;
}

void free(void * ptr) {
}
#endif
