#ifndef ALLOC_H
#define ALLOC_H

// The global allocator VTable
struct Allocator {
    void *metap;
    void (*setup)(void*metap);
    void* (*alloc)(void*metap, long size);
    void (*free)(void*metap, void* ptr);
    void (*destroy)(void*metap);
};

// Get the global allocator
struct Allocator* global_allocator();

// Setup the memory allocator
void allocator_setup();

// Allocate some memory
void* alloc(long size);

// Free the allocated memory
void free(void* ptr);

// Destroy the underlying allocator
void allocator_destroy();

#endif
