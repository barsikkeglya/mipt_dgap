#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <cstdlib>
#define maxlength 1000000

/*
search functions must have same signature.
*/

static int a[maxlength];
static int count[maxlength];

std::default_random_engine generator;

std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator

//const int MAXIMUM_VALUE = 100000;

const int maxlen = maxlength;


bool linear_sum_search(int a[], int size, int needed){
    //linear sum search algorithm
    for (int i = 0; i < size-1; i++){
        for (int j = i+1; j < size; j++){
            if (i != j){
                if (a[i] + a[j] == needed)
                    return true;
            }
        }
    }
    return false;
}

bool smart_sum_search(int a[], int size, int needed){
    int current_sum = 0;
    int beg = 0;
    int end = size - 1;
    while (beg != end){
        current_sum = a[beg] + a[end];
        if (current_sum < needed)
            beg += 1;
        else if (current_sum > needed)
            end -= 1;
        else
            return true;
    }
    return false;

}

void fill(int a[], int maxv, bool ascending){
    //fills the array with positive integers. if ascenting == true, array valueas are guarenteed to be ascending, opposite otherwise.
    int seed = std::time(nullptr);
    int random_value = std::rand();
    a[0]=random_value % maxv;
    if (ascending){
        for (int i = 1; i < maxlen; i++){
            std::srand(a[i-1]);
            int random_value = std::rand();
            a[i]=a[i-1]+(random_value % maxv);
        }
    } else {
        for (int i = 1; i < maxlen; i++){
            std::srand(a[i-1]); // use current time as seed for random generator
            int random_value = std::rand();
            a[i] = random_value % maxv;
        }
    }
}

int generate_needed(int start, int end, bool average){
    //generates needed value, bool average is flag to create -1 value that is guaranteed not to be in the array
    std::uniform_int_distribution<> distr(start, end);
    if (not average)
        return -1;
    return a[distr(gen)]+a[distr(gen)];
}

void print_arr(int a[]){
    //prints whole array
    for (int i = 0; i < maxlen; i++){
        std::cout << i << " " << a[i] << "\n";
    }
}

unsigned timing(bool (*search)(int a[], int size, int needed), int sample_size, int check_size, bool average){
    /*
    sample size - amount of runs per array length
    check size  - array length
    bool average - if true search is given number that is guaranteed to be in the array, if false -- search is given -1 as needed value, which is not in the array 
    in short: with true/false checks average/worst time complexity
    */
    auto begin = std::chrono::steady_clock::now();
    for (int iteration = 0; iteration < sample_size; iteration++){
        int needed = generate_needed(0,check_size,average);
        //std::cout << needed << "\n";
        search(a,check_size,needed);
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    return time_span.count();
}

void run_auto(bool (*search)(int a[], int size, int needed), int runs, int default_size, int sample_size, bool average){
    for (int run = 0; run < runs; run++){
        std::cout << "run no " << run << "\n\n";
        for (int n = default_size; n <= maxlen;  n = floor(n*1.5)){
            std::cout << "(" << n << ","
            << timing(search, sample_size, n, average) << ")";
        }
        std::cout << "\n\n\n\n";
    }
}

int main(){
    int default_size = 100; //start array length
    int sample_size = 1000; //amount of runs per one array length
    int runs = 2; // amount of runs to be done (first one may have bad results due to OS task handler)
    bool average = false;
    fill(a,10,true); //fills array with random integers (sorted ascending)
    //print_arr(a); //prints the array, debug purposes
    std::cout << "done fill\n"; //debug line, gives info about end of fill (and print_arr function)

    run_auto(smart_sum_search, runs, default_size, sample_size, average); //end of run output


    return 0;
}