#include<alloc.h>
#include<alloc_arena.h>

struct ArenaMetadata {
    long head, end;
};

void arena_setup(void* meta) {
    // Not required
}

void* arena_alloc(void* meta, long size){
    struct ArenaMetadata *metap = meta;
    if( metap->head + size >= metap->end ){
        return 0;
    }
    void* ptr = (void*) metap->head;
    metap->head += size;
    return ptr;
}

void arena_free(void* meta, void* ptr) {
    // Not required
}

void arena_destroy(void* meta) {
    // Not required
}

void arena_allocator(long startaddr, long length) {
    struct Allocator* allc = global_allocator();
    allc->setup = arena_setup;
    allc->alloc = arena_alloc;
    allc->free = arena_free;
    allc->destroy = arena_destroy;
}

