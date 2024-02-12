#include <iostream>
using namespace std;
#include <math.h>
bool is_square(uint64_t num) {
    double r = sqrt(num);
    return ((std::ceil(r)*std::ceil(r) == num) or (std::floor(r)*std::floor(r) == num));
}
int main(){
    uint64_t a = 18446744065119617026;
    cout << a;
    return 0;
}