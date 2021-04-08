#include <cassert>
#include "matrix.hpp"

int main(int argc, char* argv[])
{
	try{
        const size_t rows = 5;
        const size_t cols = 3;
        Matrix m(rows, cols);
        assert(m.getRow() == 5);
        assert(m.getCol() == 3);
        m[1][2] = 5; // строка 1, колонка 2
        double x = m[4][1];
        m *= 3; // умножение на число
        Matrix m1(rows, cols);
        if (m1 == m){
        }
        m1 += m;
        std::cout << m1 << std::endl;
    }
    catch(std::out_of_range&){
        std::cout<<"Out of range\n";
    }
    catch(const char* s){
        std::cout<<s<<std::endl;
    }
	return 0;
}