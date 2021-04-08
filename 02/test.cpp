#include <cassert>
#include "parser.hpp"

using namespace std;

string StartFunc(){
    return "Start ";
}

string FinishFunc(){
    return "finish";
}

string StringFunc(string a){
    return "String: "+a+" ";
}

string IntFunc(uint64_t a){
    return "Number: "+to_string(a)+" ";
}

void DefaultTest()
{
    TokenParser parser;
    parser.SetStartCallback(&StartFunc);
    parser.SetEndCallback(&FinishFunc);
    parser.SetStringTokenCallback(&StringFunc);
    parser.SetDigitTokenCallback(&IntFunc);
    string str = "abcdf5fas\t  515\t fasf\t\t\n\n18446744073709551615\n18446744073709551616\n\n\n";
    assert(parser.parse(str) == "Start String: abcdf5fas Number: 515 String: fasf Number: 18446744073709551615 String: 18446744073709551616 finish");
}

void EmptyStringAndSpacesTest()
{
    TokenParser parser;
    parser.SetStartCallback(&StartFunc);
    parser.SetEndCallback(&FinishFunc);
    parser.SetStringTokenCallback(&StringFunc);
    parser.SetDigitTokenCallback(&IntFunc);
    string str = "";
    string str2 = "                     ";
    assert(parser.parse(str) == "Start finish");
    assert(parser.parse(str2) == "Start finish");
}

void EmptyTest()
{
    TokenParser parser;
    string str = "abcdf5fas\t  515\t fasf\t\t\n\n\n\n\n\n";
    assert(parser.parse(str) == "");
}

void IntTest()
{
    TokenParser parser;
    parser.SetDigitTokenCallback(&IntFunc);
    string str = "abcdf5fas\t  515\t fasf\t\t\n5\n\n3\n\n\n";
    assert(parser.parse(str) == "Number: 515 Number: 5 Number: 3 ");
}

void StringTest()
{
    TokenParser parser;
    parser.SetStringTokenCallback(&StringFunc);
    string str = "abcdf5fas\t  515\t fasf\t 5\t\n\na\n\n\n b\n";
    assert(parser.parse(str) == "String: abcdf5fas String: fasf String: a String: b ");
}

void StartFinishTest()
{
    TokenParser parser;
    parser.SetStartCallback(&StartFunc);
    parser.SetEndCallback(&FinishFunc);
    string str = "abcdf5fas\t  515\t fasf\t\t\n\n\n\n\n\n";
    assert(parser.parse(str) == "Start finish");
}

int main(int argc, char* argv[])
{
    DefaultTest();
    EmptyStringAndSpacesTest();
    EmptyTest();
    IntTest();
    StringTest();
    StartFinishTest();
    cout << "Success!" << endl;
    return 0;
}