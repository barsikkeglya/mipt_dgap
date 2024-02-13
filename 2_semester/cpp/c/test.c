#include <stdio.h>
#include <math.h>

void swap(int *x, int *y){
    int buffer = *x;
    *x = *y;
    *y = buffer;
}

void sort1(int arr[], int size){
    int min_index = 0;
    for (int i = 0; i < size-1; i++){ 
        min_index = i; 
        for (int j = i + 1; j < size; j++){
          if (arr[j] < arr[min_index]) 
            min_index = j;
        }
        if(min_index != i){
            swap(&arr[min_index], &arr[i]); 
        }
    } 
} 
int main(){
    int arr[] = {5,4,3,2,1};
    int size = sizeof(arr)/sizeof(arr[0]);
    sort1(arr,size);
    for (int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
}