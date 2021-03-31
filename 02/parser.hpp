#pragma once
#include <iostream>

using namespace std;

using CallbackStr = string(*)(string);
using CallbackInt = string(*)(int);
using Callback = string(*)();

class TokenParser
{
private:
    Callback start = nullptr;
    Callback end = nullptr;
    CallbackStr strCall = nullptr;
    CallbackInt intCall = nullptr;
public:
	void SetStartCallback(const Callback & function);
    void SetEndCallback(const Callback & function);
    void SetDigitTokenCallback(const CallbackInt & function);
    void SetStringTokenCallback(const CallbackStr & function);
	string parse (string & text);
};