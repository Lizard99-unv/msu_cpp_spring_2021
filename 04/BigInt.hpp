#pragma once
#include <iostream>

using namespace std;

class BigInt{
    int32_t* number;
    int32_t base = 10000;
    int32_t num_size;
    bool sign = 0;
public:
    BigInt();
    BigInt(const char* b);
    BigInt(const BigInt& a);
    BigInt(int a);
    BigInt(BigInt && other);
    BigInt(string a);
    BigInt& operator- ();
    BigInt operator+ (int32_t num) const;
    BigInt operator- (int32_t num) const;
    BigInt operator* (int32_t num) const;
    BigInt operator+ (BigInt& a) const;
    BigInt operator- (BigInt& a) const;
    BigInt operator* (BigInt& a) const;
    bool operator== (BigInt& a) const;
    bool operator!= (BigInt& a) const;
    bool operator> (BigInt& a) const;
    bool operator< (BigInt& a) const;
    void print() const ;
    string post(int a);
    BigInt& cut();
    BigInt& operator= (BigInt& a);
    BigInt& operator=(BigInt&& other);
    friend ostream& operator<< (ostream &out, const BigInt &num);
    ~BigInt();
};


ostream& operator<< (std::ostream &out, const BigInt &num);

