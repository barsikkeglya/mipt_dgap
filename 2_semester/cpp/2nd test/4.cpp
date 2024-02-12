#include <iostream>
unsigned long long redux(unsigned long long a) {
    unsigned long long n = 1;
    unsigned long long s = 0;
    while (a > 9) {
        while (a / n != 0) {
            s = s + a / n  - (a / (n*10)) * 10;
            n = n * 10;
        }
        a =s;
        s = 0;
        n = 1;
    }
    return a;
}

int main(){
    unsigned long long a = 18446744073709551614;
    std::cout << redux(a);
}