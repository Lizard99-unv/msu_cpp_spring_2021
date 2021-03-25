#include <iostream>

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
            std::cout<<"Error";
            return nullptr;
        }
        if (max < (offset + size)){
            std::cout<<"Error";
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

int main(){
    Allocator A;
    A.makeAllocator(5);
    A.makeAllocator(7);
    A.alloc(7);
    return 0;
}