#include <iostream>
using namespace std;

bool is_powerof2(uint64_t a) {
    if (a == 1)
        return true;
    while ((a != 0) and (a != 1)){
        if (a % 2 != 0)
            return false;
        a = a / 2;
    }
    return true;
}

int main(){
    uint64_t a = 2;
    cout << is_powerof2(a);
    return 0;
}