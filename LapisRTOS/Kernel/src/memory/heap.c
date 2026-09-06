#include "../../include/heap.h"
#include "regions.h"

#include <stddef.h>

extern char _sheap;
extern char _eheap;

typedef enum {FALSE = 0, TRUE = 1} boolean;
typedef struct heap_header{
    uint8_t size;
    boolean free;
    struct heap_header* next;
} heap_header;

typedef struct fixed_heap_header {
    boolean free;
    struct fixed_heap_header* next;
} fixed_heap_header;

size_t heap_size;
unsigned char* heap_tail;

void heap_init(void)
{
    char * start = &_sheap;
    char * end = &_eheap;

    heap_size = end - start;

    heap_header* s = (void*)start;
    s->free = TRUE;
    s->size = 0;
    s->next = NULL;
}

void fixed_heap_init(void)
{
    char * start = &_sheap;
    char * end = &_eheap;

    heap_size = end - start;

    fixed_heap_header* byte8_region = (fixed_heap_header*)start;
    byte8_region->free = TRUE;
    byte8_region->next = NULL;

    fixed_heap_header* byte16_region = (fixed_heap_header*)(start + BYTE16_OFFSET);
    byte16_region->free = TRUE;
    byte16_region->next = NULL;

    fixed_heap_header* byte32_region = (fixed_heap_header*)(start + BYTE32_OFFSET);
    byte32_region->free = TRUE;
    byte32_region->next = NULL;
    
}

uint8_t find_region_in(unsigned char* current_address)
{
    unsigned char* sheap = (unsigned char*)&_sheap;
    if (current_address < sheap + BYTE16_OFFSET)
    {
        return 8;
    } else if (current_address >= sheap + BYTE16_OFFSET && current_address < sheap + BYTE32_OFFSET)
    {
        return 16;
    } else if (current_address >= sheap + BYTE32_OFFSET)
    {
        return 32;
    } else if (current_address >= sheap + REGION_END)
    {
        return 0;
    }
}

boolean block_in_region(unsigned char* current_address, uint8_t size)
{
    uint8_t current_region = find_region_in(current_address);
    if (current_region)
    {
        unsigned char* end_address = current_address + current_region;
        if (find_region_in(end_address) == current_region)
        {
            return TRUE;
        }
    } 
    return FALSE;
}

void * fixedMalloc(size_t size)
{   
    unsigned char* current_address = &_sheap;
    fixed_heap_header* allocated_header = (fixed_heap_header*)current_address;
    size += sizeof(fixed_heap_header); // metadata is within fixed sized block

    if (size > 15 && size < 32)
    {
        current_address += BYTE16_OFFSET;
    } else if (size >= 32)
    {
        current_address += BYTE32_OFFSET;
    }

    uint8_t which_region = find_region_in(current_address);
    boolean within_region = block_in_region(current_address, size);

    while (TRUE)
    {
        if (allocated_header->free) // First case: Block is Free
        {
            if (which_region < size && within_region)
            {
                break;
            }
        } 

        if (!within_region) {return NULL;}

        if (allocated_header->next != NULL)
        {
            current_address = (unsigned char*)allocated_header->next;
            allocated_header = (fixed_heap_header*)current_address;
        } else {
            return NULL;
        }

    }

    allocated_header->free = FALSE;

    current_address += sizeof(fixed_heap_header);
    void* allocated_address = (void*)current_address;

    current_address += (which_region - (uint8_t)sizeof(fixed_heap_header));

    if (block_in_region(current_address, find_region_in(current_address)))
    {
        if (allocated_header->next == NULL)
        {
            heap_tail = (unsigned char*)current_address;
        }


        if (heap_tail == current_address)
        {
            
            allocated_header->next = (fixed_heap_header*)heap_tail;
            fixed_heap_header* next = (fixed_heap_header*)current_address; 

            next->free = TRUE;
            next->next = NULL;
        }
    }
}

void * malloc(size_t size)
{   
    unsigned char* current_address = &_sheap;
    heap_header * allocated_header = (heap_header*)current_address;

    while (TRUE)
    {
        if (allocated_header->free)
        {
            if (allocated_header->size >= size)
            {
                break;
            } else if (allocated_header->size == 0 && sizeof(heap_header) + size <= (unsigned char*)&_eheap - current_address)
            {
                break;
            }
        }

        if (sizeof(heap_header) + size > (unsigned char*)&_eheap - current_address) {return NULL;}

        if (allocated_header->next != NULL)
        {
            current_address = (unsigned char*)allocated_header->next;
            allocated_header = (heap_header*)current_address;
        } else {
            return NULL;
        }

    }

    allocated_header->size = (uint8_t)size;
    allocated_header->free = FALSE;

    current_address += sizeof(heap_header);
    void* allocated_address = (void*)current_address;

    current_address += size;

    if ((unsigned char*)&_eheap - current_address >= sizeof(heap_header) + 1)
    {

        if (allocated_header->next == NULL)
        {
            heap_tail = (unsigned char*)current_address;
        } 

        if (heap_tail == current_address)
        {
            
            allocated_header->next = (heap_header*)heap_tail;
            heap_header* next = (heap_header*)current_address; 

            next->free = TRUE;
            next->size = 0;
            next->next = NULL;
        }
    }


    return allocated_address;
}

void free(void* ptr)
{
    heap_header* allocated_header = ptr - sizeof(heap_header);

    allocated_header->free = TRUE;
}