#include <stdlib.h>                   // for malloc and free

void *operator new(size_t size) throw() { return malloc(size); }

void operator delete(void *p) throw() { free(p); }

int raise(int sig) { return 0; }

extern "C" int __aeabi_atexit(void *object,
                              void (*destructor)(void *),
                              void *dso_handle)
{
  return 0;
}
