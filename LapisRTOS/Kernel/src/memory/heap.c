#include "../../include/heap.h"

#include <stddef.h>

extern char _sheap;
extern char _eheap;

typedef enum {FALSE = 0, TRUE = 1} boolean;
typedef struct heap_header{
    uint8_t size;
    boolean free;
    struct heap_header* next;
} heap_header;

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