#include <iostream>
using namespace std;
#include <chrono>
#include <random>
#include <numeric>
#include <array>
#include <iterator>
#include <algorithm>
#include <malloc.h>
#include <memory.h>

long const maxlen = 100000;
static std::array <long, maxlen> a;


bool linSearch(int size, int needed) {
    for (long long i = 0; i < maxlen; i++) {
        if (a[i] == needed) {
            //cout << "found " << needed << " at " << i << "\n";
            return true;
        }
    }
    cout << "couldnt find " << needed << "\n";
    return false;
}
bool binarySearch(int size, int x) {
    int beg = 0;
    int end = size - 1;
    //int size = end - beg + 1;
    while (end >= beg) {
        size = end - beg + 1;
        int mid = beg + size / 2;
        if (a[mid] == x) {
            return true;
        }
        else if (a[mid] > x) {
            end = mid - 1;
        }
        else {
            beg = mid + 1;
        }
    }
    return false;
}

int rand(int size) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<long> uni(1, size); // Guaranteed unbiased
    auto random_integer = uni(rng);
    return random_integer;
}

int timing(int size, int sample) {
    //begin timing
    auto begin = chrono::steady_clock::now();
    for (int i = 0; i < sample; i++) {
        auto random_integer = rand(size);
        binarySearch(size, rand(a[size-1]));
        //cout << "done " << i << " " << size << "\n";
    }
    auto end = chrono::steady_clock::now();
    //end timing
    auto time_span = chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    return time_span.count();
}
int main() {
    auto repeats = 2; //repeat runs?
    auto samples = 10000; //amount of samples per array length
    auto max_dstr = 1000;
    a[0] = 1;
    for (long long i = 1; i < maxlen; i++) {
        a[i] = (a[i - 1] + rand(max_dstr));
    }
    
    for (int r = 1; r <= repeats; r++) {
        for (int n = 100; n <= maxlen; n *= 2) {
            cout << timing(n, 1000000) << " " << n << "\n";
        }
        cout << "\n" << "\n";
    }
    
    return 0;
}