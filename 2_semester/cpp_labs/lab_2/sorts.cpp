#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <cstdlib>

#define maxlength 10000
#define default_size 100
#define maxvalue 10000;

static int a[maxlength];
static int chg[maxlength];

const int maxlen = maxlength;
const int def_s = default_size;
const int max_value = maxvalue;


//binomial distribution generator

std::default_random_engine generator;

std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator

void swap(int *x, int *y){
    //swaps two array entries
    int buffer = *x;
    *x = *y;
    *y = buffer;
}

int generate_needed(){

}

void fill(int a[], int size, int max_value){
    //fills array with uniform distributed between 0 and max_value integers.
    std::uniform_int_distribution<> distr(0,max_value);
    for (int i = 0; i < size; i++){
        a[i] = distr(gen);
    }
}

void print_arr(int a[],int size){
    for (int i = 0; i < size; i++)
        std::cout << "(" << i << "," << a[i] << ")";
    std::cout << "\n\n";
}

unsigned timing(int (*sort)(int a[], int start, int end), int begin_idx, int end_idx, int sample_size){
    /*
    sample size - amount of runs per array length
    check size  - array length
    bool average - if true search is given number that is guaranteed to be in the array, if false -- search is given -1 as needed value, which is not in the array 
    in short: with true/false checks average/worst time complexity
    */
    auto begin = std::chrono::steady_clock::now();
    for (int iteration = 0; iteration < sample_size; iteration++){
        auto curr_chg = sort(a,begin_idx,end_idx);
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    fill(a,maxlen,max_value);
    return time_span.count();
}

void run_auto(int (*sort)(int a[], int start, int end), int begin_idx, int end_idx, int runs, int sample_size){
    for (int run = 0; run < runs; run++){
        std::cout << "run no " << run << "\n\n";
        for (int n = def_s; n <= maxlen;  n += 1000){
            std::cout << "(" << n << ","
            << timing(sort, 0, n-1, sample_size) << ")";
        }
        std::cout << "\n\n\n\n";
    }
}

void forward_step(int a[],int begin_idx, int end_idx){
    int m = end_idx - begin_idx + 1;
    int i = begin_idx;
    for(int j = i+1; j < m; j++){
        if(a[j] < a[j-1])
            swap(&a[j],&a[j-1]);
    }
}

void backward_step(int a[],int begin_idx, int end_idx){
    int m = end_idx - begin_idx + 1;
    int i = begin_idx;
    for (int k = m-1; k > i; k--){
            if(a[k] < a[k-1])
                swap(&a[k],&a[k-1]);
    }
}

int shaker_sort(int a[], int begin_idx, int end_idx){
    int m = end_idx - begin_idx + 1;
    for (int i = 0; i < m;){
        forward_step(a,i,i+m-1);
        m--;
        backward_step(a,begin_idx,end_idx);
        i++;
    }
    return 0;
}

/*bool step_check(int a[], int step, int begin_idx, int end_idx){
    int cts = 0;
    for (int i = begin_idx; i < (end_idx-step); i += step){
        if (a[i+step] < a[i])
            swap(&a[i+step],&a[i]);
            cts++;
    }
    if (cts > 0)
        return true;
    else
        return false;
}*/

int comb_sort(int a[], int begin_idx, int end_idx){ 
    int size = end_idx - begin_idx + 1;
    int count = 0; //число перестановок
    int step = size - 1; //шаг
    bool flag = true; //swapped flag
    
    while ((flag) || (step > 1)){
        flag = false;
        for (int i = 0; i + step < size; i++){
            if (a[i] > a[i+step]){
                swap(&a[i],&a[i+step]);
                flag = true;
                count++;
            }
        }
        if (step != 1){
            step /= 2;
        }
    }
    return count;
}

int main(){

    int amount_of_runs = 1;
    int sample_size = 100;

    fill(a,maxlen,max_value);
    print_arr(a,100);
    std::cout << "\n\n" << "done fill" << "\n\n";
    //run_auto(comb_sort,0,maxlen,amount_of_runs,sample_size);
    comb_sort(a,0,99);
    std::cout << "\n\n";
    print_arr(a,100);
    return 0;
}