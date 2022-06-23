#include <unistd.h>
#include <cstring>
#include <cmath>

struct MallocMetadata;

static size_t num_free_blocks = 0; 
static size_t num_free_bytes = 0; 
static size_t num_allocated_blocks = 0; 
static size_t num_allocated_bytes = 0;
static struct MallocMetadata* list_by_memory = NULL;

struct MallocMetadata
{
    size_t size;
    bool is_free;
    struct MallocMetadata* next_by_memory;
    struct MallocMetadata* prev_by_memory;
};

void* smalloc(size_t size)
{
    if(size == 0 || size > (size_t)pow(10,8))
    {
        return NULL;
    }

    struct MallocMetadata* itr = list_by_memory, *last = NULL;

    while(itr != NULL)
    {
        if(itr->size >= size && itr->is_free) 
        {
            break;
        }
        last = itr;
        itr = itr->next_by_memory;
    }

    if(itr == NULL)
    {
        void* ptr = sbrk((intptr_t)(size + sizeof(struct MallocMetadata)));
        if(ptr == (void*)(-1))
        {
            return NULL;
        }
        num_allocated_blocks++;
        num_allocated_bytes += size;
        itr = static_cast<struct MallocMetadata*>(ptr);
        if(list_by_memory == NULL)
        {
            list_by_memory = itr;
        }
        itr->size = size;
        itr->next_by_memory = NULL;
        itr->prev_by_memory = last;

        if(last != NULL)
        {
            last->next_by_memory = itr;
        }
    }
    else
    {
        num_free_blocks--;
        num_free_bytes -= itr->size;
    }

    itr->is_free = false;
    struct MallocMetadata* p = static_cast<struct MallocMetadata*>(itr);
    p += 1;
    void* r_p = static_cast<void *>(p);
    return r_p;
}

void* scalloc(size_t num, size_t size)
{
    void* ptr = smalloc(num * size);
    if(ptr == NULL)
    {
        return NULL;
    }
    std::memset(ptr, 0x0, num * size);
    return ptr;
}

void sfree(void* p)
{
    if(p == NULL)
        return;
    struct MallocMetadata* mmd = static_cast<struct MallocMetadata*>(p);
    mmd--;
    if(mmd->is_free)
    {
        return;
    }
    mmd->is_free = true;
    num_free_blocks++;
    num_free_bytes += mmd->size;
}

void* srealloc(void* oldp, size_t size)
{
    if(size == 0)
        return NULL;
    if(oldp == NULL)
    {
        return smalloc(size);
    }
    struct MallocMetadata* mmd = static_cast<struct MallocMetadata*>(oldp);
    mmd--;

    if(mmd->size >= size) 
        return oldp;
    void* ptr = smalloc(size);
    if(ptr == NULL)
    {
        return NULL;
    }
    std::memmove(ptr, oldp, mmd->size);
    sfree(oldp);
    return ptr;
}

size_t _num_free_blocks()
{
    return num_free_blocks;
}

size_t _num_free_bytes()
{
    return num_free_bytes;
}

size_t _num_allocated_blocks()
{
    return num_allocated_blocks;
}

size_t _num_allocated_bytes()
{
    return num_allocated_bytes;
}

size_t _num_meta_data_bytes()
{
    return num_allocated_blocks * sizeof(struct MallocMetadata);
}

size_t _size_meta_data()
{
    return sizeof(struct MallocMetadata);
}