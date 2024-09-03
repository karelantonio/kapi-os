#include<alloc.h>

void allocator_setup(){
    Allocator.setup(Allocator.metap);
}

void* alloc(long size){
    return Allocator.alloc(Allocator.metap, size);
}

void free(void* ptr) {
    Allocator.free(Allocator.metap, ptr);
}

void allocator_destroy(){
    Allocator.destroy(Allocator.metap);
}
