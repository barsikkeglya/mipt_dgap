#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <cstdlib>
#define maxlength 1000000

static int a[maxlength];
static int count[maxlength];

const int MAXIMUM_VALUE = 100000;

const int maxlen = maxlength;

//binomial distribution

std::default_random_engine generator;

std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator

static int check[maxlen] = {0};



void swap(int *x, int *y){
    //swaps two array entries
    int buffer = *x;
    *x = *y;
    *y = buffer;
}

int generate_needed(int start, int end, bool average, bool binomial, bool filling){
    //generates needed value, bool average is flag to create -1 value that is guaranteed not to be in the array
    if (binomial){
        std::binomial_distribution<int> distribution(end,0.5);
        //std::cout << distribution(generator) << " ";
        check[distribution(generator)]++;
        return distribution(generator);
    }
    std::uniform_int_distribution<> distr(start, end); // define the range
    if (filling){
        return distr(gen);
    }
    //std::cout << distr(gen) << " ";
    //std::cout << a[distr(gen)] << " ";
    return distr(gen);
}

void fill(int a[], int maxv, bool ascending, int size){
    //fills the array with positive integers. if ascenting == true, array valueas are guarenteed to be ascending, opposite otherwise., maxv = maximum needed value
    if (ascending){
        for (int i = 0; i < size; i ++){
            a[i]=i+1;
        }
    }else{
        for (int i = 0; i < size; i++){
            a[i] = generate_needed(0,maxv,true,false,true);
        }
    }
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
    for (int i = 0; i < maxlen; i ++){
        count[i] = 0;
    }
    auto begin = std::chrono::steady_clock::now();
    for (int iteration = 0; iteration < sample_size; iteration++){
        int needed = generate_needed(0,check_size,average,binomial, false);
        search(a,check_size,needed);
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    fill(a,100000,true,maxlen);
    return time_span.count();
}

void run_auto(bool (*search)(int a[], int size, int needed), int runs, int default_size, int sample_size, bool average, bool binomial){
    for (int run = 0; run < runs; run++){
        std::cout << "run no " << run << "\n\n";
        for (int n = default_size; n <= maxlen;  n += 10000){
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
            swap(&a[0],&a[i]);
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

bool linear_search_C(int a[], int size, int needed){
    //linear search algorithm
    for (int i = 0; i < size; i++){
        if (a[i] == needed){
            //std::cout << "found " << needed << "\n"; //debug line
            
            count[i]++;
            int j = i;
            while ((j >= 1) and (count[j-1] < count[j])){
                swap(&count[j],&count[j-1]);
                swap(&a[j],&a[j-1]);
                j--;
            }
            return true;
            
        }
    }
    return false;
}

bool linear_search_default(int a[], int size, int needed){
    //linear search algorithm
    for (int i = 0; i < size; i++){
        if (a[i] == needed){
            //std::cout << "found at " << i << "\n";
            return true; 
        }

    }
    return false;
}

int main(){
    int default_size = 100; //start array length
    int sample_size = 5000; //amount of runs per one array length
    int runs = 2; // amount of runs to be done (first one may have bad results due to OS task handler)
    bool average = true;
    bool binomial = false;
    fill(a,MAXIMUM_VALUE,true,maxlen );
    print_arr(a,100);
    run_auto(linear_search_B, runs, default_size, sample_size, average, binomial); //end of run output
    //print_arr(check,100);
    //print_arr(a,100);
    //print_arr(count,100);
    return 0;
}