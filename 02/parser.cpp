#include "parser.hpp"

using namespace std;

void TokenParser::SetStartCallback(const Callback & function){
    start = function;
}

void TokenParser::SetEndCallback(const Callback & function){
    end = function;
}

void TokenParser::SetDigitTokenCallback(const CallbackInt & function){
    intCall = function;
}

void TokenParser::SetStringTokenCallback(const CallbackStr & function){
    strCall = function;
}

string TokenParser::parse(string &str){
    bool flag = true;
    bool empty = true;
    string token;
    string result;
    str.append("\n");
    if (start != nullptr){
        result.append(start());
    }
    for (unsigned i = 0; i < str.size(); i++){
        if ((str[i] != ' ') && (str[i] != '\t') && (str[i] != '\n')){
            empty = false;
            if (!((str[i]>='0') && (str[i]<='9'))) flag = false;
            token.push_back(str[i]);
        }
        else {
            if (!empty){
                if (!flag){
                    if (strCall != nullptr){
                        result.append(strCall(token));
                        }
                }
                else{
                    if (intCall != nullptr){
                        result.append(intCall(stoi(token)));
                    }
                }
                token.clear();
                flag = true;
                empty = true;
            }
        }
    }
    if (end != nullptr){
        result.append(end());
    }
    return result;
}
