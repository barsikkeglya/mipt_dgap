#include <iostream>
using namespace std;
int main(){
    double num = 5;
    double *ptr = &num;
    void *ptr2 = &num;
    cout << ptr << " " << ptr2;
}