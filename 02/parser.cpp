#include "parser.hpp"

using namespace std;

bool CheckLimit(string token){
    bool flag = true;
    string max = "18446744073709551615";
    if (token.length()>20) return false;
    else{
        while((token.length()>0) && (max.length()>0)){
            if (token.back()>max.back()) flag = false;
            token.pop_back();
            max.pop_back();
        }
        if (token.length()>0) return false;
        else if (max.length()>0) return true;
        else return flag;
    }
}

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
                    if (!CheckLimit(token)) {
                        if (strCall != nullptr){
                        result.append(strCall(token));
                        }
                    }
                    else {
                        if (intCall != nullptr){
                            result.append(intCall(stoull(token)));
                            }
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
