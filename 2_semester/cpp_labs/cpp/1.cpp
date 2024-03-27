#include <iostream>
#include <cstring>

int main(){
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    std::cout << &a[9] - &a[0] << "\n"; 
    return 0;
}