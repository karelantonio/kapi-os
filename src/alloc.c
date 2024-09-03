#include<alloc.h>

struct Allocator GLOBAL;

struct Allocator* global_allocator(){
    return &GLOBAL;
}

void allocator_setup(){
    GLOBAL.setup(GLOBAL.metap);
}

void* alloc(long size){
    return GLOBAL.alloc(GLOBAL.metap, size);
}

void free(void* ptr) {
    GLOBAL.free(GLOBAL.metap, ptr);
}

void allocator_destroy(){
    GLOBAL.destroy(GLOBAL.metap);
}
