#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <experimental/random>

/*
search functions must have same signature.
*/

const int maxlen=50000; //maximum array length constant

static int a[maxlen]; //static array


bool linear_sum_search(int a[], int size, int needed){
    //linear sum search algorithm
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
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

void fill(int a[]){
    //fills the array with positive integers. guaranteed to be (strictly) ascending.
    unsigned seed = time(NULL);
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> distribution(2,1000);
    a[0]=distribution(rng);
    for (int i = 1; i < maxlen; i++){
        std::uniform_int_distribution<unsigned> distribution(1,100);
        a[i]=a[i-1]+distribution(rng);
    }
}

int generate_needed(int start, int end, bool average){
    //generates needed value, bool average is flag to create -1 value that is guaranteed not to be in the array
    int random_number = std::experimental::randint(start,end);
    if (not average)
        return a[random_number]-1;
    return a[random_number];
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
        for (int n = default_size; n <= maxlen;  n+=9000){
            std::cout << timing(search, sample_size, n, average) << "," << "\n";
        }
        std::cout << "\n\n\n\n";
    }
}

int main(){
    int default_size = 100; //start array length
    int sample_size = 5000; //amount of runs per one array length
    int runs = 2; // amount of runs to be done (first one may have bad results due to OS task handler)
    bool average = false;
    fill(a); //fills array with random integers (sorted ascending)
    //print_arr(a); //prints the array, debug purposes
    std::cout << "done fill\n"; //debug line, gives info about end of fill (and print_arr function)

    run_auto(linear_sum_search, runs, default_size, sample_size, average); //end of run output

    std::cout << "N_ARRAY_VALUES" << "\n\n";
    for (int n = default_size; n <= maxlen; n+=9000){
        std::cout << n << "," << "\n";
    } //separate output for array length values

    
    

    return 0;
}