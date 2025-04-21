
#ifndef CAKE_H_
#define CAKE_H_

#include <stdlib.h>
#include <assert.h>

#define CAKE_DA_INIT_CAPACITY 256 
#define cake_da_reserve(da, size)                                       \
    do {                                                                \
        if ((da)->capacity == 0) {                                      \
            (da)->capacity = CAKE_DA_INIT_CAPACITY;                     \
        }                                                               \
        while (size >= (da)->capacity) {                                \
            (da)->capacity = (da)->capacity*2;                          \
        }                                                               \
        (da)->es = realloc((da)->es, (da)->capacity*sizeof(*(da)->es)); \
        assert((da)->es != NULL && "Buy more RAM");                     \
    } while (0)

#define cake_da_append_many(cmd, items_count, items)                                \
    do {                                                                            \
        cake_da_reserve((cmd), (cmd)->size + (items_count));                        \
        memcpy((cmd)->es + (cmd)->size, (items), (items_count)*sizeof(*(cmd)->es)); \
        (cmd)->size += (items_count);                                               \
    } while (0)

#define cake_da_appned(cmd, ...) \
    cake_da_append_many(cmd, (sizeof((const char*[]){__VA_ARGS__})/sizeof(const char*)), ((const char*[]){__VA_ARGS__}))

#define TEMP_ALLOC_CAPACITY 8*1024*1024
static size_t temp_alloc_idx = 0;
static char temp_alloc[TEMP_ALLOC_CAPACITY] = {0};

void* cake_temp_alloc(size_t size);

#ifdef CAKE_IMPLEMENTATION

void* cake_temp_alloc(size_t size)
{
    assert(temp_alloc_idx+size < TEMP_ALLOC_CAPACITY && "temporary allocator overflow");
    void* space = &temp_alloc[temp_alloc_idx];
    temp_alloc_idx+=size;
    return space;
}

#endif // CAKE_IMPLEMENTATION

#ifdef CAKE_EXT_CMD
#define CAKE_CMD_IMPLEMENTATION
#include "./extensions/cake_cmd.h"
#endif // CAKE_EXR_CMD

#ifdef CAKE_EXT_HEAP
#define CAKE_HEAP_IMPLEMENTATION
#include "./extensions/cake_heap.h"
#endif // CAKE_EXR_HEAP

#endif // CAKE_H_
