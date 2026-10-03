#include "../../include/heap.h"
#include "regions.h"

#include <stddef.h>

extern char _sheap;
extern char _eheap;


typedef enum {FALSE = 0, TRUE = 1} boolean;

static boolean heap_initialized = FALSE;

struct heap_header {
    boolean free;
    struct heap_header* next;
};
size_t heap_size;
unsigned char* heap_tail;

void initHeap(void)
{
    char * start = &_sheap;
    char * end = &_eheap;

    heap_size = end - start;

    struct heap_header* byte8_region = (struct heap_header*)start;
    byte8_region->free = TRUE;
    byte8_region->next = NULL;

    struct heap_header* byte16_region = (struct heap_header*)(start + BYTE16_OFFSET);
    byte16_region->free = TRUE;
    byte16_region->next = NULL;

    struct heap_header* byte32_region = (struct heap_header*)(start + BYTE32_OFFSET);
    byte32_region->free = TRUE;
    byte32_region->next = NULL;
    
    heap_initialized = TRUE;
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

void * Malloc(size_t size)
{   
    if (!heap_initialized)
    {
        return NULL; 
    }

    unsigned char* current_address = &_sheap;
    struct heap_header* allocated_header = (struct heap_header*)current_address;
    size += sizeof(struct heap_header); // metadata is within fixed sized block

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
            allocated_header = (struct heap_header*)current_address;
        } else {
            return NULL;
        }

    }

    allocated_header->free = FALSE;

    current_address += sizeof(struct heap_header);
    void* allocated_address = (void*)current_address;

    current_address += (which_region - (uint8_t)sizeof(struct heap_header));

    if (block_in_region(current_address, find_region_in(current_address)))
    {
        if (allocated_header->next == NULL)
        {
            heap_tail = (unsigned char*)current_address;
        }


        if (heap_tail == current_address)
        {
            
            allocated_header->next = (struct heap_header*)heap_tail;
            struct heap_header* next = (struct heap_header*)current_address; 

            next->free = TRUE;
            next->next = NULL;
        }
    }
}

void free(void* ptr)
{
    if (!heap_initialized)
    {
        return;
    }

    struct heap_header* allocated_header = ptr - sizeof(struct heap_header);
    allocated_header->free = TRUE;
}