#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <cstdlib>



const int maxlen = 100000;
static int a[maxlen];


void swap(int *x, int *y){
    int buffer = *x;
    *x = *y;
    *y = buffer;
}

void fill(int a[], int maxv, bool ascending){
    //fills the array with positive integers. if ascenting == true, array valueas are guarenteed to be ascending, opposite otherwise.
    int seed = std::time(nullptr);
    int random_value = std::rand();
    a[0]=random_value % maxv;
    std::srand(seed);
    if (ascending){
        
        for (int i = 1; i < maxlen; i++){

            int random_value = std::rand();
            a[i]=a[i-1]+(random_value % maxv);
        }
    } else {
        // use current time as seed for random generator
        for (int i = 1; i < maxlen; i++){
            
            int random_value = std::rand();
            a[i] = random_value % maxv;
        }
    }
    
}

std::default_random_engine generator;
std::binomial_distribution<int> distribution(100,0.5);
static int check[100] = {0};

int generate_needed(int start, int end, bool average, bool binomial){
    //generates needed value, bool average is flag to create -1 value that is guaranteed not to be in the array
    int seed = std::time(nullptr)*6743267427;
    std::srand(seed);
    int random_value = std::rand();

    if (binomial){
    int binomial_v = distribution(generator);
    check[binomial_v] += 1;
    return binomial_v;}
    if (average){return a[random_value % end];}
    else {return -1;}
}

void print_arr(int a[],int size){
    for (int i = 0; i < size; i++)
        std::cout << "(" << i << "," << a[i] << ")";
    std::cout << "\n\n";
}

unsigned timing(bool (*search)(int a[], int size, int needed), int sample_size, int check_size, bool average, bool binomial){
    /*
    sample size - amount of runs per array length
    check size  - array length
    bool average - if true search is given number that is guaranteed to be in the array, if false -- search is given -1 as needed value, which is not in the array 
    in short: with true/false checks average/worst time complexity
    */
    auto begin = std::chrono::steady_clock::now();
    for (int iteration = 0; iteration < sample_size; iteration++){
        int needed = generate_needed(0,1000,average,binomial);
        //std::cout << needed << "\n";
        search(a,check_size,needed);
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    return time_span.count();
}

void run_auto(bool (*search)(int a[], int size, int needed), int runs, int default_size, int sample_size, bool average, bool binomial){
    for (int run = 0; run < runs; run++){
        std::cout << "run no " << run << "\n\n";
        for (int n = default_size; n <= maxlen;  n += 1000){
            std::cout << "(" << n << ","
            << timing(search, sample_size, n, average, binomial) << ")";
        }
        std::cout << "\n\n\n\n";
    }
}

bool linear_search_A(int a[], int size, int needed){
    //linear search algorithm
    for (int i = 0; i < size; i++){
        if (a[i] == needed){
            //std::cout << "found " << needed << "\n"; //debug line
            //swap(&a[0],&a[i]);
            return true;
        }
    }
    return false;
}

bool linear_search_B(int a[], int size, int needed){
    //linear search algorithm
    for (int i = 0; i < size; i++){
        if (a[i] == needed){
            //std::cout << "found " << needed << "\n"; //debug line
            if (i != 0)
                swap(&a[i],&a[i-1]);
            return true;
        }
    }
    return false;
}


int main(){
    int default_size = 100; //start array length
    int sample_size = 10000; //amount of runs per one array length
    int runs = 2; // amount of runs to be done (first one may have bad results due to OS task handler)
    bool average = false;
    bool binomial = true;
    fill(a,1000,false);
    print_arr(a,100);
    run_auto(linear_search_A, runs, default_size, sample_size, average, binomial); //end of run output
    print_arr(check,100);
    return 0;
}