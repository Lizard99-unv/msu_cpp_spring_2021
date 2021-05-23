#include "BigInt.hpp"


using namespace std;

BigInt::BigInt(){
    number = new int32_t [2];
    num_size = 2;
    number[0] = 0;
    number [1] = 0;
}
BigInt::BigInt(const char* b){
    string a(b);
    if (a[0] == '-'){
        a = a.substr(1, a.length());
        sign ^= 1;
    }
    int size = (a.length() / 4) + 1;
    num_size = size;
    number = new int32_t [size];
    for (int i = 1; i <= size; i++){
        int c = a.length() - i*4;
        int b;
        if (c >= 0) b = 4;
        if (c < 0) {
            b = c + 4;
            c = 0;
        }
        string k = a.substr(c, b);
        if (k.length() != 0)
            number[i-1] = stoi(k);
        else
            num_size--;
    }
}
BigInt::BigInt(const BigInt& a){
    num_size = a.num_size;
    number = new int32_t [num_size];
    for (int i = 0; i < num_size; i++){
        number[i] = a.number[i];
    }
}
BigInt::BigInt(BigInt&& other): number(nullptr)
   , num_size(0){
    number = other.number;
    num_size = other.num_size;
    sign = other.sign;
    other.sign = 0;
    other.number = nullptr;
}
BigInt::BigInt(int a){
    num_size = a;
    number = new int32_t [a];
    for (int i = 0; i < a; i++){
        number[i] = 0;
    }
}
BigInt::BigInt(string a){
    if (a[0] == '-'){
        a = a.substr(1, a.length());
        sign ^= 1;
    }
    int size = (a.length() / 4) + 1;
    num_size = size;
    number = new int32_t [size];
    for (int i = 1; i <= size; i++){
        int c = a.length() - i*4;
        int b;
        if (c >= 0) b = 4;
        if (c < 0) {
            b = c + 4;
            c = 0;
        }
        string k = a.substr(c, b);
        if (k.length() != 0)
            number[i-1] = stoi(k);
        else
            num_size--;
    }
}
string BigInt::post(int a){
    string res = "";
    while(a>0){
        //int curr = to_string(number[a]).length();
        int next = to_string(number[a-1]).length();
        unsigned div_ = 4 - next;
        //div_ = 3 - div_;
        res += to_string(number[a]);
        for (unsigned i = 0; i < div_ ; i++){
            res += '0';
        }
        a--;
    }
    res += to_string(number[0]);
    return res;
}
BigInt& BigInt::cut(){
    int num = num_size - 1;
    int safe = sign;
    while ((number[num] == 0) && (num > 0)) num--;
    if (num != num_size - 1){
        BigInt tmp(post(num));
        *this = tmp;
        sign = safe;
    }
    return *this;
}
BigInt& BigInt::operator- (){
    sign ^= 1;
    return *this;
}
BigInt BigInt::operator+ (int32_t num) const{
    BigInt c = to_string(num);
    BigInt b = *this;
    if (sign){
        c = c - b;
    }
    else c = *this + c;
    return c;
}
BigInt BigInt::operator- (int32_t num) const{
    BigInt c = to_string(num);
    if (sign){
        c = *this + c;
        c.sign = 1;
    }
    else c = *this - c;
    return c;
}
BigInt BigInt::operator* (int32_t num) const{
    BigInt c = to_string(num);
    c = *this * c;
    return c;
}
BigInt BigInt::operator+ (BigInt& a) const{
    int size = min(a.num_size, num_size);
    int32_t overflow = 0;
    BigInt c(max(num_size, a.num_size)+1);
    for (int i = 0; i < min(a.num_size, num_size); i++ ){
        c.number[i] += a.number[i] + overflow +number[i];
        if (c.number[i]>=10000){
            c.number[i] %= 10000;
            overflow = 1;
        }
        else overflow = 0;
    }
    if (a.num_size > num_size){
        for (int i = num_size; i < a.num_size; i++){
            c.number[i] += a.number[i] + overflow;
            if (c.number[i]>=10000){
                c.number[i] %= 10000;
                overflow = 1;
            }
            else overflow = 0;
        }
        c.number[a.num_size] += overflow;
    }
    else if (a.num_size <= num_size){
        for (int i = a.num_size; i < num_size; i++){
            c.number[i] += number[i] + overflow;
            if (c.number[i]>=10000){
                c.number[i] %= 10000;
                overflow = 1;
            }
            else overflow = 0;
        }
        c.number[num_size] += overflow;
    }
    return c; 
}
BigInt BigInt::operator- (BigInt& a) const{
    int size = min(a.num_size, num_size);
    int32_t overflow = 0;
    BigInt c(max(num_size, a.num_size)+1);
    if (a.num_size >  num_size) c.sign^=1;
    else if (a.num_size == num_size)
        if (a.number[0] > number[0]) c.sign^=1;
    for (int i = 0; i < min(a.num_size, num_size); i++ ){
        c.number[i] = -a.number[i] - overflow +number[i];
        if (c.number[i] < 0){
            if (num_size > a.num_size)
                c.number[i] += 10000;
            else 
                c.number[i] *= -1;
            overflow = 1;
        }
        else overflow = 0;
    }
    if (a.num_size > num_size){
        number[num_size]-=overflow;
        for (int i = num_size; i < a.num_size; i++){
            c.number[i] += a.number[i];
        }     
    }
    else if (a.num_size <= num_size){
        number[a.num_size]-=overflow;
        for (int i = a.num_size; i < num_size; i++){
            c.number[i] += number[i];
        }
    }
    return c; 
}
BigInt BigInt::operator* (BigInt& a) const{
    int size = min(a.num_size, num_size);
    int32_t overflow = 0;
    BigInt c(num_size*a.num_size+1);
    if (sign == 1) c.sign^=1;
    if (a.sign == 1) c.sign^=1;
    for (int i = 0; i < num_size; i++ ){
        for (int j = 0; j < a.num_size; j++){
            c.number[j+i] += number[i] * a.number[j] + overflow;
            overflow = c.number[i+j] / 10000;
            c.number[i+j] %= 10000;
        }
        c.number[i+a.num_size]+=overflow;
        overflow = 0;
    }
    return c; 
}
bool BigInt::operator== (BigInt& a) const{
    if (sign != a.sign) return false;
    else if (num_size != a.num_size) return false;
        else for (int i = 0; i < num_size; i++){
            if (number[i] != a.number[i]) return false;
        }
    return true;
}
bool BigInt::operator!= (BigInt& a) const{
    bool flag = true;
    if (sign == a.sign)
        if (num_size == a.num_size)
            for (int i = 0; i < num_size; i++){
            if (number[i] != a.number[i]) flag = false;
        }
    if (flag) return false;
    return true;
}
bool BigInt::operator> (BigInt& a) const{
    if (*this == a) return false;
    if (sign){
        if (!a.sign) return false;
    }
    else {
        if (a.sign) return true;
    }
    if (num_size > a.num_size) return true;
    if (num_size < a.num_size) return false;
    if (number[0] > a.number[0]) return true;
    else return false;
}
bool BigInt::operator< (BigInt& a) const{
    if (*this == a) return false;
    if (sign){
        if (!a.sign) return true;
    }
    else {
        if (a.sign) return false;
    }
    if (num_size > a.num_size) return false;
    if (num_size < a.num_size) return true;
    if (number[0] > a.number[0]) return false;
    else return true;
}
void BigInt::print() const{
    for (int i = 0; i < num_size; i++){
        cout<<number[i]<<' ';
    }
    cout<<endl;
}
BigInt& BigInt::operator= (BigInt& a){
    if (this != &a){
        delete[] number;
        num_size = a.num_size;
        sign = a.sign;
        number = new int32_t [a.num_size];
        for (int i = 0; i < a.num_size; i++){
            number[i] = a.number[i];
        }
    }
    return *this;
}
BigInt& BigInt::operator=(BigInt&& other){
    if (this != &other){
        delete[] number;
        number = other.number;
        num_size = other.num_size;
        sign = other.sign;
        other.sign = 0;
        other.number = nullptr;
    }
    return *this;
}
BigInt::~BigInt(){
    delete[] number;
}
/*
ostream& operator<< (std::ostream &out, const BigInt &num){
    unsigned size = num.num_size;
    if (num.sign) out<<'-';
    int k = size - 1;
    while ((num.number[k] == 0) && (k > 0)) k--;
    if (k > 0){
        out<<num.number[k];
        k--;
    }
    for (int i = k; i > 0; i--){
        int a = 4 - to_string(num.number[i]).length();
        for (int j = 0; j < a; j++)
            out<<0;
        if ((i != 0) || (num.number[0] !=0))
            out<<num.number[i];
    }
    if (size > 2){
        int a = 4 - to_string(num.number[0]).length();
        for (int j = 0; j < a; j++)
            out<<0;
        out<<num.number[0];    
    }
    else out<<num.number[0];
    return out;
}*/
ostream& operator<< (std::ostream &out, const BigInt &num){
    BigInt b = num;
    b.cut();
    unsigned size = b.num_size;
    if (b.sign) out<<'-';
    int k = size - 1;
    while(k > 0){
        //int curr = to_string(b.number[k]).length();
        int next = to_string(b.number[k-1]).length();
        unsigned div_ = 4 - next;
        //div_ = 3 - div_;
        out<<b.number[k];
        for (unsigned i = 0; i < div_ ; i++){
            out<<0;
        }
       k--;
    }
    out<<num.number[0];
    return out;
}