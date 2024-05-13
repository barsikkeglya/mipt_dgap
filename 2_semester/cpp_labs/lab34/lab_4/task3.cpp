#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <fstream>

using namespace std;

struct AVLTree{
    int key;
    unsigned char height;
    AVLTree* left;
    AVLTree* right;
    AVLTree(int k) {key = k; left = right = nullptr; height = 1;};
};

unsigned char height(AVLTree *p){
    if(p != nullptr){
        return p->height;
    }
    return 0;
}

int balance_factor(AVLTree *p){
    return (height(p->right)-height(p->left));
}

void fix_height(AVLTree *p){
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    if (hl > hr){
        p->height = hl + 1;
    }
    else{
        p->height = hr + 1;
    }
}

AVLTree *rotateright(AVLTree *p){
    AVLTree *q = p->left;
    p->left = q->right;
    q->right = p;
    fix_height(p);
    fix_height(q);
    return q;
}

AVLTree *rotateleft(AVLTree *q){
    AVLTree *p = q->right;
    q->right = p->left;
    p->left = q;
    fix_height(p);
    fix_height(q);
    return p;
}

AVLTree *update_balance(AVLTree *p){
    fix_height(p);
    if(balance_factor(p)==2){
        if(balance_factor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if(balance_factor(p)==-2){
        if(balance_factor(p->left)>0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

AVLTree *insert(AVLTree *p, int k){
    if(p == nullptr){
        return new AVLTree(k);
    }
    if (k < p->key){
        p->left = insert(p->left,k);
    }else{
        p->right = insert(p->right,k);
    }
    return update_balance(p);
}

AVLTree *search(AVLTree *p, int k){
    if(p == nullptr){
        return nullptr;
    }
    else if (p->key == k){
        return p;
    }
    else if (p->key > k){
        return search(p->left,k);
    }
    else{
        return search(p->right, k);
    }
    cout << "did not find element" << endl;
}

AVLTree *search_min(AVLTree *p){
    if(p->left != nullptr){
        return search_min(p->left);
    }
    return p;
}

AVLTree *remove_min(AVLTree *p){
    if(p->left == nullptr){
        return p->right;
    }
    p->left = remove_min(p->left);
    return update_balance(p);
}

AVLTree *remove(AVLTree *p, int k){
    if (p == nullptr){
        return nullptr;
    }
    if(k < p->key){
        p->left = remove(p->left, k);
    }
    else if(k > p-> key){
        p->right = remove(p->right,k);
    }
    else{
        AVLTree *q = p->left;
        AVLTree *r = p->right;
        delete p;
        if(r == nullptr){
            return q;
        }
        AVLTree *min = search_min(r);
        min->right = remove_min(r);
        min->left = q;
        return update_balance(min);
    }
    return update_balance(p);
}

int main(){
    ofstream my_file("data/avl.csv");
    default_random_engine rng(666);
    my_file << "N,iTa,sTa,dTa,iTb,sTb,dTb" << endl;
    const unsigned int start_n = 1000;
    const unsigned int max_n = 10001;
    const unsigned int step = 1000;
    const unsigned int sample_size = 100;
    AVLTree *arr[sample_size];
    for(unsigned n = start_n; n < max_n; n += step){
        auto begin = chrono::steady_clock::now();
        for(unsigned i = 0; i < sample_size; i++){
            arr[i]=nullptr;
            for(unsigned j = 0; j < n; j++){
                arr[i]=insert(arr[i],j);
            }
        }
        auto end = chrono::steady_clock::now();
        auto init_timeA = (chrono::duration_cast<chrono::milliseconds>(end-begin)).count();

        begin = chrono::steady_clock::now();
        for(unsigned i = 0; i < sample_size; i++){
            for(unsigned j = 0; j < n; j++){
                search(arr[i],j);
            }
        }
        end = chrono::steady_clock::now();
        auto search_timeA = (chrono::duration_cast<chrono::milliseconds>(end-begin)).count();

        begin = chrono::steady_clock::now();
        for(unsigned i = 0; i < sample_size; i++){
            for(unsigned j = 0; j < n; j++){
                arr[i]=remove(arr[i],j);
            }
        }
        auto delete_timeA = (chrono::duration_cast<chrono::milliseconds>(end-begin)).count();

        auto requests = new (std::nothrow) int[max_n] {0};
        for(unsigned i = 0; i < n; i++){
            requests[i]=i;
        }
        shuffle(requests,requests+n,rng);

        /*------------------------------------------------------------------*/
        /* (╯°□°）╯︵ ┻━┻   */

        begin = chrono::steady_clock::now();
        for(unsigned i = 0; i < sample_size; i++){
            arr[i]=nullptr;
            for(unsigned j = 0; j < n; j++){
                arr[i]=insert(arr[i],requests[j]);
            }
        }
        end = chrono::steady_clock::now();
        auto init_timeB = (chrono::duration_cast<chrono::milliseconds>(end-begin)).count();

        begin = chrono::steady_clock::now();
        for(unsigned i = 0; i < sample_size; i++){
            for(unsigned j = 0; j < n; j++){
                search(arr[i],requests[j]);
            }
        }
        end = chrono::steady_clock::now();
        auto search_timeB = (chrono::duration_cast<chrono::milliseconds>(end-begin)).count();

        begin = chrono::steady_clock::now();
        for(unsigned i = 0; i < sample_size; i++){
            for(unsigned j = 0; j < n; j++){
                arr[i]=remove(arr[i],requests[j]);
            }
        }
        end = chrono::steady_clock::now();
        auto delete_timeB = (chrono::duration_cast<chrono::milliseconds>(end-begin)).count();

        my_file << n << "," << init_timeA << "," << search_timeA << "," << delete_timeA << "," << init_timeB << "," << search_timeB << "," << delete_timeB << endl;

        delete[] requests;
    }
    cout << "success" << endl;
    return 0;
}   