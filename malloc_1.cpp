#include <unistd.h>
#include <cmath>

void* smalloc(size_t size)
{
    if(size == 0 || size > (size_t)pow(10,8))
    {
        return NULL;
    }
    void* ptr = sbrk((intptr_t)size);
    if(ptr == (void*)(-1))
    {
        return NULL;
    }
    return ptr;
}