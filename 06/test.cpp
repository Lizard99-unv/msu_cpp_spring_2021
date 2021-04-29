#include "format.hpp"
#include <cassert>
#include <iostream>

void DefaultTest(){
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
}

void CharStringIntDoubleTest(){
    auto text = format ("{0} is char, {1} is string, {2} is int, {3} is double!", 'a', "test", 2, 3.14);
    std::cout<<text<<std::endl;
    assert(text == "a is char, test is string, 2 is int, 3.14 is double!");
}

void ParenthesisErrorTest(){
    try{
        auto text = format ("{1", 3);
    }
    catch(ParenthesisError&){;}
}

void WrongArgumentErrorTest(){
    try{
        auto text = format ("{abc}", 3);
    }
    catch(WrongArgumentError&){;}
}

void CountArgumentErrorTest(){
    try{
        auto text = format ("{18} is error", 123);
    }
    catch(CountArgumentError&){;}
}

int main()
{
    DefaultTest();
    CharStringIntDoubleTest();
    ParenthesisErrorTest();
    WrongArgumentErrorTest();
    CountArgumentErrorTest();
	std::cout<<"Success!"<<std::endl;
    return 0;
}