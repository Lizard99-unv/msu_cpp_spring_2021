#include <cassert>
#include "BigInt.hpp"

void DefaultTest(){
    BigInt a = "1";
    BigInt b("123456789012345678901234567890");
    BigInt c = a * b + 2;
    BigInt d;
    d = std::move(c);
    a = d + b;
    d = "246913578024691357802469135782";
    assert(a.cut() == d.cut()); // cut удаляет незначащие нули. Число при этом не изменяется
}

void AllFunctionsTest(){
    BigInt a = "10";
    BigInt b = "15";
    BigInt c = "25";
    a = a + b;
    assert(a.cut() == c.cut());
    a = "10";
    b = c - b;
    assert(a.cut() == b.cut());
    c = "30";
    a = a * 3;
    std::cout << a << std::endl;
    assert(a.cut() == c.cut());
    assert(b.cut() != c.cut());
    assert(b < a);
    assert(a > b);
    c = "-28";
    c = c - 2;
    -a;
    assert(a.cut() == c.cut());
}

void BorderTest(){
    BigInt a = "1";
    BigInt b("9999");
    a = a + b;
    std::cout<<a<<std::endl;
    b = b + 2;
    b = b - 1;
    std::cout<<b<<std::endl;
    BigInt c("0");
    b = b*c + c;
    assert(b.cut() == c.cut());
    b = a;
    b = b - a;
    assert(b.cut() == c.cut());
}

int main(int argc, char* argv[]){
	DefaultTest();
    AllFunctionsTest();
    BorderTest();
    std::cout << "Success!" <<std::endl;
    return 0; 
}