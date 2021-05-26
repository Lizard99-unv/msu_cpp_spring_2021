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


void OverflowTest(){
    try{
        auto text = format ("{2147483156464864654864654516499} is error", 123, 12);
    }
    catch(OverflowError&){;}
}

void ManyArgsTest(){
    try{
        auto text = format ("{0} is error", 0, 2);
    }
    catch(TooManyArgsError&){;}
}

void PositiveTests(){
    auto text = format("");
    assert(text == "");
    text = format("{0}", 1);
    assert(text == "1");
    text = format("{0}{1}{2}", 1, 2, 3);
    assert(text == "123");
    text = format("{0}{1}{2}{4}{5}{6} is not equal to {7}{8}{9}{10}", 1, 2, 3, 4, 5, 6, 6, 7, 7, 7, 10);
    assert(text == "123566 is not equal to 77710");
}

void NegativeTests(){
    try{
        auto text = format ("{0}} is error", 0);
    }
    catch(ParenthesisError&){;}
    try{
        auto text = format ("{} is error", 0);
    }
    catch(CountArgumentError&){;}
    try{
        auto text = format ("{1str} is error", 0, 1);
    }
    catch(WrongArgumentError&){;}
    try{
        auto text = format ("{2} is error", 0, 1);
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
    OverflowTest();
    ManyArgsTest();
    PositiveTests();
    NegativeTests();
	std::cout<<"Success!"<<std::endl;
    return 0;
}