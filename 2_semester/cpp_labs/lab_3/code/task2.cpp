#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

struct LinkedList{
    int data;
    LinkedList *next;
};

LinkedList* insert_after(LinkedList * const current){
    if (current == nullptr){
        return new LinkedList{0,nullptr};
    }  
    LinkedList* new_node = new LinkedList{0,current->next};
    current->next = new_node;
    return new_node;
}

LinkedList* remove_after(LinkedList * const current){
    if (nullptr == current or current->next == nullptr){
        return nullptr;
    }
    LinkedList* new_next = current->next->next;
    delete current->next;
    current->next = new_next;
    return current->next;
}

void kill(LinkedList * const head){
    while (head->next != nullptr){
        head->next = remove_after(head);
    }
    delete head;
}

#define length 10

int massacre (int n,int step){
    auto first = insert_after(nullptr);
    first -> data = 1;
    auto current = insert_after(first);
    current -> data = 2;
    for (int i = 3; i <= n; i++){
        current = insert_after(current);
        current -> data = i;
    }
    current -> next = first;
    current = first;
    int i = 1;
    while (current -> next != current){
        if ((i+1) % step == 0){
            remove_after(current);
        }
        else{
            current = current -> next;
        }
        i++;
    }
    int res = current -> data;
    delete current;
    return res;
}

int massacre_array(int n, int step){
    int* arr = new int [n+1];
    arr[0] = -1;
    for (int i = 1; i <= n; i++){
        arr[i] = i;
    }
    int size = n;
    int i = 1;
    int s = 1;
    while (size > 1){
        if (s % step == 0){
            for(int j = i; j <= size; j++){
                arr[j] = arr[j+1];
            }
            size--;
        }
        else{
            i++;
        }
        if(i > size){
            i = 1;
        }
        if(s == step){
            s = 1;
        }
        else{
            s++;
        }
    }
    int result = arr[1];
    delete[] arr;
    return result;
}

unsigned timing(int(*massacre_kind)(int n, int step), int n){
    long long sample_size = 10000;
    auto begin = std::chrono::steady_clock::now();

    for(int j = 1; j <= sample_size; j++){
        massacre_kind(n,3);
    }

    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
    return static_cast<unsigned>((time_span.count()));
}

int main(){
    std::ofstream myfile;
    myfile.open("../data/task2_1.csv");
    myfile << "n,t\n";
    int max_length = 10000;
    for (int i = 10; i <= max_length; i++){
        //std::cout << "(" << i << "," << timing(massacre,i) << ")";
        myfile << i << "," << timing(massacre_array,i) << "\n";
    }
    return 0;
}