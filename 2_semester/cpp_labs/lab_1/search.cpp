#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <experimental/random>

const int maxlen=100000;
const int default_size = 3000;

static int a[maxlen];


bool linear_search(int a[], int size, int needed){
    for (int i = 0; i < size; i++){
        if (a[i] == needed){
            //std::cout << "found " << needed << "\n";
            return true;
        }
    }
    return false;
}

void fill(int a[]){
    unsigned seed = time(NULL);
    std::default_random_engine rng(seed);
    for (int i = 0; i < maxlen; i++){
        std::uniform_int_distribution<unsigned> dstr(0,10000);
        a[i]=dstr(rng);
    }
}

int generate_needed(){
    int random_number = std::experimental::randint(0,10000);
    return random_number;
}

void printarr(int a[]){
    for (int i = 0; i < maxlen; i++){
        std::cout << a[i] << " ";
    }
}

unsigned timing(int sample_size, int check_size){
    //time
    auto begin = std::chrono::steady_clock::now();
    for (int iteration = 0; iteration < sample_size; iteration++){
        linear_search(a,check_size,generate_needed());
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    return time_span.count();
    //end time
}


int main(){
    int size = default_size;
    int sample_size = 50000;
    int runs = 2;
    fill(a);
    for (int run = 0; run < runs; run++){
        for (int n = default_size; n <= maxlen; n += 3000){
            std::cout << n << " " << timing(sample_size, n) << "\n";
        }
        std::cout << "\n\n";
    }
    
    

    return 0;
}