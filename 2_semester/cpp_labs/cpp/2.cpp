#include <iostream>
#include <stdlib.h>
#include <stdio.h>

int main(){
    long long x0 = 0;
    long long y0 = 0;
    std::cin >> x0;
    std::cin >> y0;
    long long n;
    std::cin >> n;
    long long dx[10000];
    long long dy[10000];
    for(int i = 0; i < n; i++){
        std::cin >> dx[i];
        std::cin >> dy[i];
    }
    long long curr_x = x0;
    long long curr_y = y0;
    long long max_length = abs(y0-x0);
    for(int i = 0; i < n; i++){
        curr_x = curr_x+dx[i];
        curr_y = curr_y+dy[i];
        long long current_length = abs(curr_y-curr_x);
        if (current_length > max_length){
            max_length=current_length;
        }
    }
    std::cout << max_length;
}