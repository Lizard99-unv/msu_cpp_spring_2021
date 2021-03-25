#include <iostream>
#include <cassert>

class Allocator
{
private:
    char* ptr = nullptr;
    int offset = 0;
    int max;
public:
    void makeAllocator(size_t maxSize){
        if (ptr != nullptr){
            delete[] ptr;
            offset = 0;
        }
        max = maxSize;
        ptr = new char [maxSize];
    }
    char* alloc(size_t size){
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
    void reset(){
        offset = 0;
    }
    ~Allocator(){
        if (ptr != nullptr ){
            delete[] ptr;
        }
    }
};

void DefaultWorkTest()
{
    Allocator A;
    A.makeAllocator(5);
    char *testPtr = A.alloc(3);
    assert(testPtr != nullptr);
}

void LimitTest()
{
    Allocator A;
    A.makeAllocator(5);
    A.alloc(3);
    char *testPtr = A.alloc(3);
    assert(testPtr == nullptr);
}

void RestartTest()
{
    Allocator A;
    A.makeAllocator(5);
    A.makeAllocator(8);
    char *testPtr = A.alloc(6);
    assert(testPtr != nullptr);
}

void BeforeTest()
{
    Allocator A;
    char *testPtr = A.alloc(6);
    A.makeAllocator(5);
    assert(testPtr == nullptr);
}

void ResetTest()
{
    Allocator A;
    A.makeAllocator(5);
    A.alloc(3);
    A.reset();
    char *testPtr = A.alloc(3);
    assert(testPtr != nullptr);
}

int main()
{
    DefaultWorkTest();
    LimitTest();
    RestartTest();
    BeforeTest();
    ResetTest();

    std::cout << "Success!\n";

    return 0;
}
