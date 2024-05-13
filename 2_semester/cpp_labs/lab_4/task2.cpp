#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <fstream>

using namespace std;

struct BinaryTree{
    BinaryTree *left;
    BinaryTree *right;
    int key;
    int value;
};

BinaryTree *find(BinaryTree *head, int key){
    if(head == nullptr)
        return nullptr;
    else if(head->key == key)
        return head;
    else if(head->key > key)
        return find(head->right,key);
    else
        return find(head->left,key);
    cout << "Error finding" << endl;
    return nullptr;
}

BinaryTree *insert(BinaryTree *head, int key, int value = 0){
    if(head == nullptr)
        return new BinaryTree{nullptr,nullptr,key,value};
    else if(head->key == key)
        head->key = value;
    else if(head->key > key)
        head->right = insert(head->right,key,value);
    else
        head->left = insert(head->left,key,value);
    return head;
}

BinaryTree *remove(BinaryTree *head, int key){
    if(head == nullptr)
        return nullptr;
    else if(head->key > key)
        head->right = remove(head->right,key);
    else if(head->key < key)
        head->left = remove(head->left,key);
    else{
        if(head->left == nullptr and head->right == nullptr){
            delete head;
            return nullptr;
        }
        else if(head->right == nullptr){
            BinaryTree *left = head -> left;
            delete head;
            return left;
        }
        else if(head->left == nullptr){
            BinaryTree *right = head->right;
            delete head;
            return right;
        }
        else{
            if(head->right->left == nullptr){
                head->value = head->right->value;
                head->key = head->right->key;
                BinaryTree *right = head->right;
                head->right = head->right->right;
                delete right;
            }
            else{
                BinaryTree *node = head->right;
                while(node->left->left != nullptr){
                    node = node->left;
                }
                head->value = node->left->value;
                head->key = node->left->key;
                node->left = remove(node->left,node->left->key);
            }
        }
    }
    return head;
}

int main(){
    ofstream my_file("data/bin_tree.csv");
    my_file << "n,iTa,sTa,dTa,iTb,sTb,dTb" << endl;
    default_random_engine rng(666);
    const unsigned int start_n = 1000;
    const unsigned int max_n = 10001;
    const unsigned int step = 1000;
    const unsigned int sample_size = 100;
    BinaryTree *arr[sample_size];
    for(unsigned int n = start_n; n < max_n; n+=step){
        auto begin = chrono::steady_clock::now();
        for(unsigned j = 0; j < sample_size; j++){
            arr[j]=nullptr;
            for(unsigned i = 0; i < n; i++){
                arr[j]=insert(arr[j],i);
            }
        }
        auto end = chrono::steady_clock::now();
        auto init_timeA = (chrono::duration_cast<chrono::milliseconds>(end-begin)).count();

        begin = chrono::steady_clock::now();
        for(unsigned j = 0; j < sample_size; j++){
            for(unsigned i = 0; i < n; i++){
                find(arr[j],i);
            }
        }
        end = chrono::steady_clock::now();
        auto search_timeA = (chrono::duration_cast<chrono::milliseconds>(end-begin)).count();

        begin = chrono::steady_clock::now();
        for(unsigned j = 0; j < sample_size; j++){
            for(unsigned i = 0; i < n; i++){
                arr[j]=remove(arr[j],i);
            }
        }
        end = chrono::steady_clock::now();
        auto delete_timeA = (chrono::duration_cast<chrono::milliseconds>(end-begin)).count();

        auto requests = new (std::nothrow) int[max_n] {0};
        for(unsigned i = 0; i < max_n; i++){
            requests[i]=i;
        }
        std::shuffle(requests,requests+n,rng);

        begin = chrono::steady_clock::now();
        for(unsigned j = 0; j < sample_size; j++){
            arr[j]=nullptr;
            for(unsigned i = 0; i < n; i++){
                arr[j]=insert(arr[j],requests[i]);
            }
        }
        end = chrono::steady_clock::now();
        auto init_timeB = (chrono::duration_cast<chrono::milliseconds>(end-begin)).count();

        begin = chrono::steady_clock::now();
        for(unsigned j = 0; j < sample_size; j++){
            for(unsigned i = 0; i < n; i++){
                find(arr[j],requests[i]);
            }
        }
        end = chrono::steady_clock::now();
        auto search_timeB = (chrono::duration_cast<chrono::milliseconds>(end-begin)).count();

        begin = chrono::steady_clock::now();
        for(unsigned j = 0; j < sample_size; j++){
            for(unsigned i = 0; i < n; i++){
                arr[j]=remove(arr[j],requests[i]);
            }
        }
        end = chrono::steady_clock::now();
        auto delete_timeB = (chrono::duration_cast<chrono::milliseconds>(end-begin)).count();

        delete[] requests;

        my_file << n << "," << init_timeA << "," << search_timeA << "," << delete_timeA << "," << init_timeB << "," << search_timeB << "," << delete_timeB << endl;
    }
    cout << endl << "success" << endl;
    return 0;

}