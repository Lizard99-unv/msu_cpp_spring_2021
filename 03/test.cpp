#include <cassert>
#include "matrix.hpp"

void AllFunctionsTest(){
    Matrix m(5, 3);
    assert(m.getRow() == 5);
    assert(m.getCol() == 3);
    m[1][2] = 7;
    assert(m[1][2] == 7);
    double x = m[4][1];
    assert(x == 1);
    std::cout << "Before multiplication: " << std::endl << m << std::endl;
    m *= 3;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 3; j++){
            if ((i == 1) && (j == 2))
                assert(m[i][j] == 21);
            else
                assert(m[i][j] == 3);
        }
    std::cout << "After: " << std::endl << m << std::endl;
    Matrix m2(2, 2);
    Matrix m3(2, 2);
    std::cout << "Second matrix: " << std::endl << m2 << std::endl;
    std::cout << "Third matrix: " << std::endl << m3 << std::endl;
    assert(m2 == m3);
    if (m2 == m3){
        std::cout << "Matrix two and three are equal." << std::endl;
    }
    assert(m2 != m);
    if (m2 != m){
        std::cout << "Matrix one and two are not equal." << std::endl;
    }
    m2 += m3;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            assert(m2[i][j] == 2);
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

void WrongSizeSumTest(){
    Matrix m(3, 3);
    Matrix m2(5, 3);
    try{
        m += m2;
    }
    catch(const char* s){
        std::cout<<s<<std::endl;
    }
}

void OutOfRangeTest(){
    Matrix m(3, 3);
    try{
        double x = m[0][25];
    }
    catch(std::out_of_range&){
        std::cout<<"Out of range!"<<std::endl;
    }
    try{
        double x = m[25][0];
    }
    catch(std::out_of_range&){
        std::cout<<"Out of range!"<<std::endl;
    }
    try{
        double x = m[25][25];
    }
    catch(std::out_of_range&){
        std::cout<<"Out of range!"<<std::endl;
    }
}

void ChangeAllElementsTest(){
    Matrix m(3, 4);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++){
            m[i][j] = j + i;
            assert(m[i][j] == i + j);
        }
    std::cout<<'\n'<<m<<std::endl;
}

int main(int argc, char* argv[])
{
    AllFunctionsTest();
    OneElementTest();
    WrongSizeSumTest();
    OutOfRangeTest();
    ChangeAllElementsTest();
    std::cout << "Success!\n";
    return 0;
}