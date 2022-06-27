#include <unistd.h>
#include <cstring>
#include <cmath>
#include <sys/mman.h>
#include <stdio.h>

#define MIN4SPLIT 128
#define MIN4MMAP 128 * 1024

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
    bool is_mmap;
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
        list_by_size = tail_by_size = ptr;
        return;
    }

    while(itr != NULL)
    {
        if(itr->size == size)
        {
            if(!(itr->next_by_size && itr->next_by_size->size == size))
            {
                if(ptr < itr)
                {
                    struct MallocMetadata* temp = itr->prev_by_size;
                    itr->prev_by_size = ptr;
                    ptr->next_by_size = itr;
                    ptr->prev_by_size = temp;
                    if(temp)
                    {
                        temp->next_by_size = ptr;
                    }
                    if(itr == list_by_size)
                    {
                        list_by_memory = ptr;
                    }
                }
                else
                {
                    struct MallocMetadata* temp = itr->next_by_size;
                    itr->next_by_size = ptr;
                    ptr->prev_by_size = itr;
                    ptr->next_by_size = temp;
                    if(temp)
                    {
                        temp->prev_by_size = ptr;
                    }
                }
                
                return;
            }
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
            if(list_by_size == itr)
            {
                list_by_size = ptr;
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
    ptr->next_by_size = NULL;
    tail_by_size = ptr;
}

void combineBlocksAUX(struct MallocMetadata* current, struct MallocMetadata* next, bool prev_combine, bool next_freed)
{
    current->size += next->size + sizeof(struct MallocMetadata);
    if(next_freed)
    {
        num_free_blocks--;
        num_free_bytes += sizeof(struct MallocMetadata);
    }
    num_allocated_blocks--;
    num_allocated_bytes += sizeof(struct MallocMetadata);
    if(next == tail_by_memory)
    {
        tail_by_memory = current;
    }
    if(next == tail_by_size)
    {
        tail_by_size = tail_by_size->prev_by_size;
    }
    if(current == tail_by_size)
    {
        tail_by_size = tail_by_size->prev_by_size;
    }

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
    if((tail_by_size != next) && next_size)
    {
        next_size->prev_by_size = prev_size;
    }
    if(current == list_by_size || next == list_by_size)
    {
        list_by_size = next_size;
    }
    next->prev_by_size = NULL;
    next->next_by_size = NULL;
    if(prev_combine == false)
    {
        prev_size = current->prev_by_size;
        next_size = current->next_by_size;
        if((list_by_size != current) && prev_size)
        {
            prev_size->next_by_size = next_size;
        }
        if(next_size)
        {
            next_size->prev_by_size = prev_size;
        }

        current->prev_by_size = NULL;
        current->next_by_size = NULL;
    }
}

void combineBlocks(struct MallocMetadata* ptr)
{
    struct MallocMetadata* prev = ptr->prev_by_memory, *next = ptr->next_by_memory;
    bool combined = false;
    if(prev && prev->is_free)
    {
        combineBlocksAUX(prev, ptr, combined, true);
        combined = true;
        ptr = prev;
    }
    if(next && next->is_free)
    {
        combineBlocksAUX(ptr, next, combined, true);
        combined = true;
    }
    if(combined)
    {
        insertBySize(ptr, ptr->size);
    }
}

void splitBlock(struct MallocMetadata* ptr, size_t size)
{
    if((size + sizeof(struct MallocMetadata)) > ptr->size) return;
    struct MallocMetadata* backup = ptr;
    size_t split_size = ptr->size - size - sizeof(struct MallocMetadata);
    if(split_size >= MIN4SPLIT)
    {
        ptr->size = size;
        ptr++;
        void* temp = static_cast<void*>(ptr);
        char* p = static_cast<char*>(temp);
        p += backup->size;
        temp = static_cast<void*>(p);
        ptr = static_cast<struct MallocMetadata*>(temp);
        ptr->is_free = true;
        ptr->size = split_size;
        struct MallocMetadata* next = backup->next_by_memory;
        if(next)
        {
            next->prev_by_memory = ptr;    
        }
        ptr->next_by_memory = next;
        ptr->prev_by_memory = backup;
        backup->next_by_memory = ptr;
        if(tail_by_memory == backup)
        {
            ptr->next_by_memory = NULL;
            tail_by_memory = ptr;
        }

        struct MallocMetadata* next_size = backup->next_by_size, *prev_size = backup->prev_by_size;
        if(next_size)
        {
            next_size->prev_by_size = prev_size;
        }
        if(prev_size)
        {
            prev_size->next_by_size = next_size;
        }
        if(backup == tail_by_size)
        {
            tail_by_size = prev_size;
        }
        backup->next_by_size = NULL;
        backup->prev_by_size = NULL;
        if(backup == list_by_size)
        {
            list_by_size = NULL;
        }

        insertBySize(backup, backup->size);
        insertBySize(ptr, ptr->size);
        num_allocated_blocks++;
        num_allocated_bytes -= sizeof(struct MallocMetadata);
        num_free_blocks++;
        num_free_bytes += ptr->size;
        if(ptr->next_by_memory && ptr->next_by_memory->is_free)
        {
            combineBlocksAUX(ptr, ptr->next_by_memory, false, true);
            insertBySize(ptr, ptr->size);
        }
    }
}

struct MallocMetadata* enlargeTail(size_t size)
{
    if(sbrk((intptr_t)(size - tail_by_memory->size)) == (void*)(-1))
    {
        return NULL;
    }
    num_allocated_bytes += (size - tail_by_memory->size);
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
    return tail_by_memory;
}

void* smalloc(size_t size)
{
    if(size % 8 != 0) 
    {
        size += (8 - (size % 8)); // aligned to 8
    }
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
        if(size >= MIN4MMAP)
        {
            void* ptr = mmap(NULL, size + sizeof(struct MallocMetadata), PROT_READ | PROT_WRITE, 
                                MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
            if(ptr == MAP_FAILED)
            {
                return NULL;
            }
            num_allocated_blocks++;
            num_allocated_bytes += size;
            itr = static_cast<struct MallocMetadata*>(ptr);
            itr->is_mmap = true;
            itr->size = size;
            itr->next_by_memory = itr->next_by_size = 
                itr->prev_by_memory = itr->prev_by_size = NULL;
        }
        else if(tail_by_memory && tail_by_memory->is_free)
        {
            size_t tail_size = tail_by_memory->size;
            itr = enlargeTail(size);
            if(itr == NULL)
            {
                return NULL;
            }
            num_free_blocks--;
            num_free_bytes -= tail_size;
        }
        else
        {
            void* base = sbrk(0);
            if((size_t)base % 8 != 0)
            {
                base = sbrk((intptr_t)(8 - ((size_t)base % 8)));
                if(base == (void*)(-1))
                {
                    return NULL;
                }
            }
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
            itr->is_mmap = false;
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
    if(itr->size != size)
    {
        splitBlock(itr, size);
    }
    itr += 1;
    void* p = static_cast<void *>(itr);
    return p;
}

void* scalloc(size_t num, size_t size)
{
    size_t new_size = num * size;

    void* ptr = smalloc(new_size);
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
    if(mmd->is_mmap)
    {
        size_t size = mmd->size;
        if(munmap(mmd, sizeof(struct MallocMetadata) + mmd->size) < 0)
            exit(1);
        num_allocated_blocks--;
        num_allocated_bytes -= size;
        return;
    }
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
    void* ptr;
    mmd--;
    size_t oldsize = mmd->size;
    if(mmd->is_mmap)
    {
        if(mmd->size == size)
        {
            mmd->is_free = false;
            return oldp;
        }
    }
    else if(mmd->size >= size)
    { 
        splitBlock(mmd, size);
        mmd->is_free = false;
        return oldp;
    }
    else if(mmd->prev_by_memory && mmd->prev_by_memory->is_free && 
            (((mmd->prev_by_memory->size + sizeof(struct MallocMetadata) + mmd->size) >= size) || (mmd == tail_by_memory)))
    {
        bool enlarge_flag = false;
        if(mmd == tail_by_memory && !((mmd->prev_by_memory->size + sizeof(struct MallocMetadata) + mmd->size) >= size))
        {
            enlarge_flag = true;
        }
        num_free_blocks--;
        num_free_bytes -= mmd->prev_by_memory->size;
        combineBlocksAUX(mmd->prev_by_memory, mmd, false, false);
        mmd = mmd->prev_by_memory;
        if(enlarge_flag)
        {
            mmd = enlargeTail(size);
            if(mmd == NULL)
            {
                return NULL;
            }
            mmd->is_free = false;
        }
        insertBySize(mmd, mmd->size);
        splitBlock(mmd, size);
        mmd->is_free = false;
        mmd++;
        ptr = static_cast<void*>(mmd);
        std::memmove(ptr, oldp, oldsize);
        return ptr;
        
    }
    else if(mmd == tail_by_memory)
    {
        size_t enhance = (size - tail_by_memory->size);
        mmd = enlargeTail(size);
        if(mmd == NULL)
        {
            return NULL;
        }
        if(mmd->is_free)
        {
            num_free_blocks--;
            num_free_bytes -= (size - enhance);
        }
        splitBlock(mmd, size); // maybe not needed
        mmd->is_free = false;
        return oldp;
    }
    else if(mmd->next_by_memory && mmd->next_by_memory->is_free &&
             ((mmd->next_by_memory->size + sizeof(struct MallocMetadata) + mmd->size) >= size))
    {
        num_free_blocks--;
        num_free_bytes -= mmd->next_by_memory->size;
        combineBlocksAUX(mmd, mmd->next_by_memory, false, false);
        insertBySize(mmd, mmd->size);
        splitBlock(mmd, size);
        mmd->is_free = false;
        return oldp;
    }
    else if(mmd->prev_by_memory && mmd->next_by_memory && 
            mmd->prev_by_memory->is_free && mmd->next_by_memory->is_free &&
            ((mmd->prev_by_memory->size + 2*sizeof(struct MallocMetadata) + mmd->size + mmd->next_by_memory->size) >= size))
    {
        num_free_blocks -= 2;
        num_free_bytes -= (mmd->prev_by_memory->size + mmd->next_by_memory->size);
        combineBlocksAUX(mmd->prev_by_memory, mmd, false, false);
        mmd = mmd->prev_by_memory;
        combineBlocksAUX(mmd, mmd->next_by_memory, true, false);
        insertBySize(mmd, mmd->size);
        splitBlock(mmd, size);
        mmd->is_free = false;
        mmd++;
        ptr = static_cast<void*>(mmd);
        std::memmove(ptr, oldp, oldsize);
        return ptr;
    }
    else if(mmd->next_by_memory && mmd->next_by_memory->is_free && (mmd->next_by_memory == tail_by_memory))
    {
        if(mmd->prev_by_memory && mmd->prev_by_memory->is_free) // needs to combine and enlarge
        {
            num_free_blocks -= 2;
            num_free_bytes -= (mmd->prev_by_memory->size + mmd->next_by_memory->size);
            combineBlocksAUX(mmd->prev_by_memory, mmd, false, false);
            mmd = mmd->prev_by_memory;
            combineBlocksAUX(mmd, mmd->next_by_memory, true, false);
        }
        else
        {
            num_free_blocks--;
            num_free_bytes -= mmd->next_by_memory->size;
            combineBlocksAUX(mmd, mmd->next_by_memory, false, false);
        }

        tail_by_memory = mmd;
        mmd = enlargeTail(size);
        if(mmd == NULL)
        {
            return NULL;
        }
        insertBySize(mmd, size);
        mmd->is_free = false;
        mmd++;
        ptr = static_cast<void*>(mmd);
        std::memmove(ptr, oldp, oldsize);
        return ptr;
    }

    ptr = smalloc(size);
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