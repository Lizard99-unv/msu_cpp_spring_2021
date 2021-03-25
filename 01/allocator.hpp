#pragma once
#include <iostream>

class Allocator
{
private:
    char* ptr = nullptr;
    int offset = 0;
    int max;
public:
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
};
