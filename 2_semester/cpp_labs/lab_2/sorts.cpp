#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define maxlength 50000
#define default_size 100
#define maxvalue 10000

const bool supress = true;

static int etalon[maxlength];
static int a[maxlength];
static int chg[maxlength];

const int maxlen = maxlength;
const int def_s = default_size;
const int max_value = maxvalue;


//binomial distribution generator

std::default_random_engine generator;

std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator

void shuffle_array(int a[], int begin_idx, int end_idx){
    //shuffles array from begin_idx to end_idx
    shuffle(&a[begin_idx],&a[end_idx],rd);
}

void swap(int *x, int *y){
    //swaps two array entries
    int buffer = *x;
    *x = *y;
    *y = buffer;
}

bool check_sorted(int a[], int begin_idx, int end_idx){
    // checks if array is sorted from begin_idx to end_idx
    for (int i = begin_idx; i < end_idx; i++){
        if (a[i+1] < a[i])
            return false;
    }
    return true;
}


void fill(int a[], int size, int max_value){
    //fills array with uniform distributed between 0 and max_value integers.
    std::uniform_int_distribution<> distr(0,max_value);
    for (int i = 0; i < size; i++){
        a[i] = distr(gen);
    }
}

void print_arr(int a[],int size){
    //prints first SIZE elements of an array in form of (x,y), where x === index, y === value
    for (int i = 0; i < size; i++)
        std::cout << "(" << i << "," << a[i] << ")";
    std::cout << "\n\n";
}

unsigned timing(int (*sort)(int a[], int start, int end), int begin_idx, int end_idx, int sample_size, bool changes, bool err){
    /*
    sort --- current sort function
    begin_idx --- begin index
    end_idx --- end index
    sample_size --- sample size
    changes --- function returns amount of changes if true
    */
    int errors = 0;
    int rolling_chg = 0;
    auto begin = std::chrono::steady_clock::now();
    for (int iteration = 0; iteration < sample_size; iteration++){
        shuffle_array(a,0,end_idx-1);
        int curr_chg = sort(a,begin_idx,end_idx);
        rolling_chg += curr_chg;
        if (!check_sorted(a,0,end_idx-1))
            errors++;
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    //fill(a,maxlen,max_value);
    if (err) 
        return floor(((float)errors/(float)sample_size)*100);
    if (changes)
        return (rolling_chg /= sample_size);
    return time_span.count();
}

void run_auto(int (*sort)(int a[], int start, int end), int begin_idx, int end_idx, int runs, int sample_size, bool changes, bool errors){
    /*
    auto run function, does RUNS amount of runs. outputs to console times (or changes depending on CHANGES boolean) in form of (x,y), where x === size of array, y === time (or changes)
    */
    for (int run = 0; run < runs; run++){
        std::cout << "run no " << run << "\n\n";
        for (int n = def_s; n <= maxlen;  n += 5000){
            std::cout << "(" << n << ","
            << timing(sort, 0, n-1, sample_size, changes, errors) << ")";
        }
        std::cout << "\n\n\n\n";
    }
}

int forward_step(int a[],int begin_idx, int end_idx){
    int m = end_idx - begin_idx + 1;
    int i = begin_idx;
    int changes = 0;
    for(int j = 0; j < m-1; j++){
        if(a[j] > a[j+1]){
            swap(&a[j],&a[j+1]);
            changes++;
        }
    }
    return changes;
}

int backward_step(int a[],int begin_idx, int end_idx){
    int m = end_idx - begin_idx + 1;
    int i = begin_idx;
    int changes = 0;
    for (int k = m-1; k > -1; k--){
        if(a[k] > a[k+1]){
            swap(&a[k],&a[k+1]);
            changes++;
        }
    }
    return changes;
}

int shaker_sort(int a[], int begin_idx, int end_idx){
    //shaker sort function
    int m = end_idx - begin_idx + 1;
    int changes = 0;
    for (int i = 0; i < m;){
        auto x = forward_step(a,i,i+m-1);
        m--;
        auto y = backward_step(a,begin_idx,end_idx);
        i++;
        changes += x;
        changes += y;
    }
    return changes;
}

int full_forward(int a[], int begin_idx, int end_idx){
    //full forward bubble sort, uses forward step
    int size = end_idx - begin_idx + 1;
    int changes = 0;
    for (int i = 0; i < size - 1; i++){
        auto x = forward_step(a,i,size);
        changes += x;
    }
    return (changes);
}

int full_backward(int a[], int begin_idx, int end_idx){
    //full backward bubble sort, uses backward step.
    int size = end_idx - begin_idx + 1;
    int changes = 0;
    for (int i = size-1; i > 0; i--){
        auto x = backward_step(a,i,size);
        changes += x;
    }
    return (changes);
}

/*int step_full_forward(int a[], int begin_idx, int end_idx, int step){
    for (int i = begin_idx; i + step < end_idx; i = i + step){
        for (int j = 0; j < i; j = j+step)
            if(a[j] > a[j+step]){
                swap(&a[j],&a[j+step]);
                changes++;
            }
    }
}*/

int comb_sort(int a[], int begin_idx, int end_idx){
    //comb sort function
    int size = end_idx - begin_idx + 1;
    int step = end_idx - begin_idx;
    double shrink_factor = 2;
    int changes = 0;
    
	while (step >= 1){   
		for (int i = 0; i + step < size; i++){
			if (a[i] > a[i + step])
			{
                swap(&a[i],&a[i+step]);
                changes++;
			}
		}
		step /= shrink_factor;
	}
    //auto x = full_forward(a,begin_idx,end_idx);
    return changes;
}

int calculate_next_gap(int curr_gap, int mode){
    if (mode == 1)
        return curr_gap/=2;
    if (mode == 2){
        int n = curr_gap;
        int i = floor(std::log(n)/std::log(2));
        return (int)(std::pow(2,i)-1);
    }
    if (mode == 3){
        double root5 = std::pow(5,0.5);
        double phi = (1 + root5)/2;
        int n = trunc((std::log((curr_gap-1)*root5))/std::log(phi));
        return round(std::pow(phi,n)/root5);
    }
    return -1;
}

int shell_sort(int a[], int begin_idx, int end_idx){
    int n = end_idx-begin_idx+1;
    int changes = 0;
    int d;
    for (int gap = n; gap > 0;)
    {
        for (int i = gap; i < n; i += 1)
        {
            int temp = a[i];
            int j;            
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap){
                a[j] = a[j - gap];
                changes++;
            }
            a[j] = temp;
        }
        gap=calculate_next_gap(gap,3);
    }
    return changes;
}

int main(){

    int amount_of_runs = 1;
    int sample_size = 1000;
    bool changes = true;
    bool errors = false;

    fill(a,maxlen,max_value);
    run_auto(shell_sort,0,maxlen,amount_of_runs,sample_size, changes, errors);
    run_auto(shell_sort,0,maxlen,amount_of_runs,sample_size,false,!errors);
    /*
    print_arr(a,100);
    auto x = shell_sort(a,0,100);
    print_arr(a,100);
    std::cout << "\n" << check_sorted(a,0,100);
    */
    return 0;
}