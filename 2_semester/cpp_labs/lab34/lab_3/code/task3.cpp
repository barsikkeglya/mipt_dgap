#include <iostream>
#include <chrono>
#include <fstream>

struct DynamicArray {
    int *elements = nullptr;
    unsigned capacity = 0, size = 0;
};

DynamicArray new_array(unsigned size, int init_val = 0){
    int* array = new int[size];
    for (unsigned i = 0; i < size; i++){
        *(array+i) = init_val;
    }
    return DynamicArray{array,size,size};
}

void erase(DynamicArray &da){
    delete[] da.elements;
    da.size = 0;
    da.capacity = 0;
}

DynamicArray& reserve(DynamicArray &da, unsigned capacity){
    if (da.capacity >= capacity){
        return da;
    }

    int* array = new int[capacity];
    for(unsigned i = 0; i < da.size; i++){
        *(array+i) = *(da.elements+i);
    }
    if (da.capacity > 0){
        delete[] da.elements;
    }
    da = DynamicArray{array,capacity,da.size};
    return da;
}

DynamicArray clone(DynamicArray &da){
    int* array = new int[da.size];
    for (unsigned i = 0; i < da.size; i++){
        *(array+i) = *(da.elements + i);
    }
    return DynamicArray{array, da.size, da.capacity};
}

DynamicArray& assign(DynamicArray const &src, DynamicArray &dst){
    if(dst.capacity < src.size){
        reserve(dst,src.size);
    }
    for (unsigned i = 0; i < src.size; i++){
        *(dst.elements + i) = *(src.elements + i);
    }
    dst.size = src.size;
    return dst;
}

DynamicArray& push_back1(DynamicArray &da, int val){
    if (da.size >= da.capacity){
        reserve(da,da.capacity+1);
    }
    *(da.elements+da.size) = val;
    da.size++;
    return da;
}

DynamicArray& push_back2(DynamicArray &da, int val){
    if (da.size >= da.capacity){
        reserve(da,da.capacity+1000);
    }
    *(da.elements+da.size) = val;
    da.size++;
    return da;
}
DynamicArray& push_back3(DynamicArray &da, int val){
    if (da.size >= da.capacity){
        reserve(da,da.capacity*2);
    }
    *(da.elements+da.size) = val;
    da.size++;
    return da;
}

unsigned timing(DynamicArray& (*push_back) (DynamicArray &da, int val), DynamicArray &da, long long sample_size, long long add_size){
    
    auto begin = std::chrono::steady_clock::now();

    for (int i = 0; i < sample_size; i++){
        while (da.size < add_size){
            push_back(da,1);
        }
        erase(da);
        da = new_array(1);
    }

    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    return static_cast<unsigned>(time_span.count());
}

int main(){
    
    int max_size = 100000;
    int sample_size = 100;

    auto da = new_array(1);
    std::ofstream myfile;
    myfile.open("../data/task3_3.csv");
    myfile << "n,t\n";

    for (int n = 1000; n <= max_size; n += 3000){
        myfile << n << "," << timing(push_back3,da,sample_size, n) << "\n"; 
    }
    erase(da);
    return 0;
}