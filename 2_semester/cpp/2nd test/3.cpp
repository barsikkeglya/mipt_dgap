#include <iostream>
#include <iterator>

bool check_for_repeat(char const symbols[], unsigned size){
    for(unsigned i = 0; i < size; i++){
        for(unsigned j = 0; j < size; j++){
            if ((i != j) and (symbols[i] == symbols[j]))
                return true;
        }
    }
    return false;
}

unsigned max_unique_subarray_length(char const symbols[], unsigned size) {
    unsigned max_length = 0;
    char copy[90000] = {};
    for (unsigned i = 0; i < size; i++){
        if (max_length == 26)
            return 26;
        for (unsigned j = i; j < size; j++){
            unsigned length = j-i+1;
            for (unsigned pointer = 0; pointer < j-i+1; pointer++){
                copy[pointer]=symbols[pointer+i];
                //std::cout << copy[pointer] << " ";
            }
            if (not check_for_repeat(copy,length)){
                if (length > max_length){
                    max_length = length;
                }
            }
        }
    }
    return max_length;
}

int main(){
    char symbols[] = "abcbad";
    unsigned size = (sizeof(symbols)/sizeof(symbols[0]));
    std::cout << max_unique_subarray_length(symbols,size);
    //std::cout << check_for_repeat(symbols,size);
    return 0;

}
