#include <unistd.h>
#include <cstring>
#include <cmath>

#define MIN4SPLIT 128

struct MallocMetadata;

static size_t num_free_blocks = 0; 
static size_t num_free_bytes = 0; 
static size_t num_allocated_blocks = 0; 
static size_t num_allocated_bytes = 0;
static struct MallocMetadata* list_by_memory = NULL;
static struct MallocMetadata* tail_by_memory = NULL;
static struct MallocMetadata* list_by_size = NULL;
static struct MallocMetadata* tail_by_size = NULL;

struct MallocMetadata
{
    size_t size;
    bool is_free;
    struct MallocMetadata* next_by_memory;
    struct MallocMetadata* prev_by_memory;
    struct MallocMetadata* next_by_size;
    struct MallocMetadata* prev_by_size;
};

void insertBySize(struct MallocMetadata* ptr, size_t size)
{
    struct MallocMetadata* itr = list_by_size;

    if(list_by_size == NULL)
    {
        list_by_size = ptr;
        return;
    }

    while(itr != NULL)
    {
        if(itr->size == size)
        {
            struct MallocMetadata* temp = itr->next_by_size;
            itr->next_by_size = ptr;
            ptr->prev_by_size = itr;
            ptr->next_by_size = temp;
            if(temp)
            {
                temp->prev_by_size = ptr;
            }
            return;
        }
        else if(itr->size > size) 
        {
            struct MallocMetadata* temp = itr->prev_by_size;
            itr->prev_by_size = ptr;
            ptr->prev_by_size = temp;
            ptr->next_by_size = itr;
            if(temp)
            {
                temp->next_by_size = ptr;
            }
            return;
        }
        itr = itr->next_by_size;
    }
    // ptr is the biggest -> needs to be the tail of list_by_size -> tail_by_size
    if(tail_by_size)
    {
        tail_by_size->next_by_size = ptr;
    }
    ptr->prev_by_size = tail_by_size;
    tail_by_size = ptr;
}

void combineBlocksAUX(struct MallocMetadata* current, struct MallocMetadata* next, bool prev_combine)
{
    current->size += next->size + sizeof(struct MallocMetadata);
    num_free_blocks--;
    num_allocated_blocks--;
    num_free_bytes += sizeof(struct MallocMetadata);
    num_allocated_bytes += sizeof(struct MallocMetadata);

    struct MallocMetadata* prev_size = next->prev_by_size, *next_size = next->next_by_size;
    struct MallocMetadata* next_memory = next->next_by_memory;
    if(next_memory)
    {
        next_memory->prev_by_memory = current;
    }
    current->next_by_memory = next_memory;
    if(prev_size)
    {
        prev_size->next_by_size = next_size;
    }
    if(next_size)
    {
        next_size->prev_by_size = prev_size;
    }

    if(prev_combine == false)
    {
        prev_size = current->prev_by_size;
        next_size = current->next_by_size;
        if(prev_size)
        {
            prev_size->next_by_size = next_size;
        }
        if(next_size)
        {
            next_size->prev_by_size = prev_size;
        }
    }
}

void combineBlocks(struct MallocMetadata* ptr)
{
    struct MallocMetadata* prev = ptr->prev_by_memory, *next = ptr->next_by_memory;
    bool combined = false;
    if(prev && prev->is_free)
    {
        combineBlocksAUX(prev, ptr, combined);
        combined = true;
        ptr = prev;
    }
    if(next && next->is_free)
    {
        combineBlocksAUX(ptr, next, combined);
        combined = true;
    }
    if(combined)
    {
        insertBySize(ptr, ptr->size);
    }
}

void splitBlock(struct MallocMetadata* ptr, size_t size)
{
    struct MallocMetadata* backup = ptr;
    size_t split_size = ptr->size - size;
    if(split_size >= MIN4SPLIT && split_size > sizeof(struct MallocMetadata))
    {
        ptr->size = size;
        ptr++;
        void* temp = static_cast<void*>(ptr);
        char* p = static_cast<char*>(temp);
        p += size;
        temp = static_cast<void*>(p);
        ptr = static_cast<struct MallocMetadata*>(temp);
        ptr->is_free = true;
        ptr->size = split_size - sizeof(struct MallocMetadata);
        struct MallocMetadata* next = backup->next_by_memory;
        if(next)
        {
            next->prev_by_memory = ptr;
            ptr->next_by_memory = next;
        }
        ptr->prev_by_memory = backup;
        backup->next_by_memory = ptr;

        insertBySize(ptr, ptr->size);
        num_allocated_blocks++;
        num_allocated_bytes -= sizeof(struct MallocMetadata);
    }
}

void* smalloc(size_t size)
{
    if(size == 0 || size > (size_t)pow(10,8))
    {
        return NULL;
    }

    struct MallocMetadata* itr = list_by_size;

    while(itr != NULL)
    {
        if(itr->size >= size && itr->is_free) 
        {
            break;
        }
        itr = itr->next_by_size;
    }

    if(itr == NULL)
    {
        if(tail_by_memory && tail_by_memory->is_free)
        {
            if(sbrk((intptr_t)(size - tail_by_memory->size)) == (void*)(-1))
            {
                return NULL;
            }
            tail_by_memory->size = size;
            struct MallocMetadata* prev_size = tail_by_memory->prev_by_size, *next_size = tail_by_memory->next_by_size;
            if(prev_size)
            {
                prev_size->next_by_size = next_size;
            }
            if(next_size)
            {
                next_size->prev_by_size = prev_size;
            }
            insertBySize(tail_by_memory, size);
        }
        else
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
            itr->prev_by_memory = tail_by_memory;

            if(tail_by_memory != NULL)
            {
                tail_by_memory->next_by_memory = itr;
            }

            tail_by_memory = itr;
            insertBySize(tail_by_memory, size);
        }
    }
    else
    {
        num_free_blocks--;
        num_free_bytes -= itr->size;
    }

    itr->is_free = false;
    struct MallocMetadata* p = static_cast<struct MallocMetadata*>(itr);
    splitBlock(p, size);
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
    combineBlocks(mmd);
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