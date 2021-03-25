#include "allocator.hpp"

void Allocator::makeAllocator(size_t maxSize){
    if (ptr != nullptr){
        delete[] ptr;
        offset = 0;
    }
    max = maxSize;
    ptr = new char [maxSize];
}
char* Allocator::alloc(size_t size){
    if (ptr == nullptr){
        return nullptr;
    }
    if (max < (offset + static_cast<int>(size))){
        return nullptr;
    }
    char* block = ptr;
    block += offset;
    offset += size;
    return block;
}
void Allocator::reset(){
    offset = 0;
}
Allocator::~Allocator(){
    if (ptr != nullptr ){
        delete[] ptr;
    }
}