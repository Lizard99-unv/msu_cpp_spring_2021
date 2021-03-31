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
    return a+" ";
}

string IntFunc(int a){
    return to_string(a)+" ";
}

void DefaultTest()
{
	TokenParser parser;
    parser.SetStartCallback(&StartFunc);
    parser.SetEndCallback(&FinishFunc);
    parser.SetStringTokenCallback(&StringFunc);
    parser.SetDigitTokenCallback(&IntFunc);
    string str = "abcdf5fas\t  515\t fasf\t\t\n\n\n\n\n\n";
    assert(parser.parse(str) == "Start abcdf5fas 515 fasf finish");
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
    string str = "abcdf5fas\t  515\t fasf\t\t\n\n\n\n\n\n";
    assert(parser.parse(str) == "515 ");
}

void StringTest()
{
	TokenParser parser;
    parser.SetStringTokenCallback(&StringFunc);
    string str = "abcdf5fas\t  515\t fasf\t\t\n\n\n\n\n\n";
    assert(parser.parse(str) == "abcdf5fas fasf ");
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
    EmptyTest();
    IntTest();
    StringTest();
    StartFinishTest();
	cout << "Success!" << endl;
	return 0;
}