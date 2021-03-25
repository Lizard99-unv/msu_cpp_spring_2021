#include "allocator.hpp"
#include <cassert>

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
