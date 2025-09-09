#include "philosophers.h"

void *protected_malloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
        //cleanup(NULL, FAILURE, "MALLOC FAILED!"); TODO
    return (ptr);
}