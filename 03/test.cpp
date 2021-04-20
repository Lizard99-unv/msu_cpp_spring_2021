#include <cassert>
#include "matrix.hpp"

void AllFunctionsTest(){
    Matrix m(5, 3);
    assert(m.getRow() == 5);
    assert(m.getCol() == 3);
    m[1][2] = 7;
    assert(m[1][2] == 7);
    double x = m[4][1];
    std::cout << "Before multiplication: " << std::endl << m << std::endl;
    m *= 3;
    std::cout << "After: " << std::endl << m << std::endl;
    Matrix m2(2, 2);
    Matrix m3(2, 2);
    std::cout << "Second matrix: " << std::endl << m2 << std::endl;
    std::cout << "Third matrix: " << std::endl << m3 << std::endl;
    if (m2 == m3){
        std::cout << "Matrix two and three are equal." << std::endl;
    }
    if (m2 != m){
        std::cout << "Matrix one and two are not equal." << std::endl;
    }
    m2 += m3;
    std::cout << "Sum of matrix two and three is: " << std::endl << m2 << std::endl;
}

void OneElementTest(){
    Matrix m(1, 1);
    Matrix m2(1, 1);
    assert(m.getRow() == 1);
    assert(m.getCol() == 1);
    m[0][0] = 7;
    assert(m[0][0] == 7);
    m *= 3;
    assert(m[0][0] == 21);
    m += m2;
    assert(m[0][0] == 22);
    std::cout<< "One element matrix:  "<< m << std::endl;
}

void OutOfRangeTest1(){
    Matrix m(3, 3);
    Matrix m2(5, 3);
    m += m2;
    //double x = m[5][2];
}

void OutOfRangeTest2(){
    Matrix m(3, 3);
    double x = m[5][2];
}

int main(int argc, char* argv[])
{
	try{
        AllFunctionsTest();
        OneElementTest();
        OutOfRangeTest1();
    }
    catch(const char* s){
        std::cout<<s<<std::endl;
        try{
            OutOfRangeTest2();
        }
        catch(std::out_of_range&){
            std::cout << "Out of range!\n";
        }
    }
    std::cout << "Success!\n";
	return 0;
}