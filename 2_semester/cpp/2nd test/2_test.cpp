#include <iostream>
void reverse_array (int input_array[], unsigned size){
    for (unsigned i = 0; i <= (size-1)/2; i++){
        auto buffer = input_array[i];
        input_array[i] = input_array[size-i-1];
        input_array[size-i-1] = buffer;
    }
}

int main(){
    auto size = 10;
    int input_array[size] = {1,2,3,4,5,6,7,8,9,10};
    reverse_array(input_array,size);
    for (int i = 0; i < size; i++){
        std::cout << input_array[i] << " ";
    }
    return 0;
}