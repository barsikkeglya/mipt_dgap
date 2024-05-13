#include <iostream>
#include <chrono>
#include <algorithm>
#include <fstream>

using namespace std;

union Hash_int
{
    int i;
    unsigned u;
};

struct ListPair{
    ListPair *tail;
    int p;
};
struct Table{
    ListPair **table;
    float load_factor;
    unsigned size;
};

unsigned get_hash(int a){
    Hash_int d;
    d.i = a;
    return d.u;
}
void delete_after(ListPair *head){
    if (head != nullptr){
        ListPair *tail = head->tail;
        head->tail = head->tail->tail;
        delete tail;
    }
}
void erase_list(ListPair *head){
    if(head != nullptr){
        while(head->tail != nullptr){
            ListPair *tail = head -> tail;
            delete head;
            head = tail;
        }
        delete head;
    }
}
ListPair *add_before_list(ListPair *head, int p){
    return new ListPair{head,p};
}
Table new_table(unsigned size){
    ListPair **table = new ListPair *[size];
    for(unsigned i = 0; i < size; i++){
        table[i]=nullptr;
    }
    return Table(table,0.f,size);
}

bool contains(Table *t, int p){
    unsigned index = get_hash(p) % t -> size;
    ListPair *head = t->table[index];
    bool flag = false;
    while(nullptr != head && !flag){
        flag = head -> p == p;
        head = head -> tail;
    }
    return flag;
}

void remove(Table *t, int p){
    unsigned index = get_hash(p) % t -> size;
    ListPair *head = t -> table[index];
    if (head != nullptr){
        if(head->p == p){
            delete head;
            t->table[index] = nullptr;
        }
        else{
            bool flag = false;
            while(head->tail != nullptr && !flag){
                flag = head->tail->p==p;
                head = head->tail;
            }
            if (flag){
                delete_after(head);
            }
        }
    }
}

void erase_table (Table *t){
    for(unsigned i = 0; i < t->size; i++){
        erase_list((t->table)[i]);
    }
    delete[] t->table;
}

void add_element(Table *t, int p){
    unsigned index = get_hash(p) % t->size;
    ListPair *head = t->table[index];
    bool flag = false;
    while(head != nullptr && !flag){
        flag = head->p == p;
        head = head->tail;
    }
    if(!flag){
        t->table[index]=add_before_list(t->table[index],p);
        t->load_factor += 1.f / t->size;
    }
}

void expand_table(Table *t, unsigned new_size){
    Table new_t = new_table(new_size);
    for(unsigned i = 0; i < t->size; i++){
        ListPair *head = t->table[i];
        while (nullptr != head){
            add_element(&new_t,head->p);
            head = head->tail;
        }
    }
    erase_table(t);
    *t=new_t;
}

void add(Table *t, int p){
    add_element(t,p);
    if(t->load_factor>1){
        expand_table(t,t->size*2);
    }
}

void hash_table(){
    const unsigned int min_n = 1000;
    const unsigned int max_n = 100000;
    const unsigned int step = 10000;
    const unsigned int sample_size = 100;
    const unsigned int default_size = 1000;
    Table arr[sample_size];
    ofstream output_file("data/hash.csv");
    output_file << "N" << "," << "iT" << "," << "sT" << "," << "dT" << std::endl;
    for(unsigned int n = min_n; n <= max_n; n+=step){
        for(unsigned int j = 0; j < sample_size; j++){
            arr[j] = new_table(default_size);
        }
        auto begin = chrono::steady_clock::now();
        for(unsigned int j = 0; j < sample_size; j++){
            for(unsigned int i = 0; i < n; i++){
                add(&arr[j],i);
            }
        }
        auto end = chrono::steady_clock::now();
        auto init_time = (chrono::duration_cast<chrono::milliseconds>(end-begin)).count();

        begin = chrono::steady_clock::now();
        for(unsigned int j = 0; j <sample_size; j++){
            for(unsigned int i = 0; i < n; i++){
                contains(&arr[j],i);
            }
        }
        end = chrono::steady_clock::now();
        auto search_time = (chrono::duration_cast<chrono::milliseconds>(end-begin)).count();

        begin = chrono::steady_clock::now();
        for(unsigned int j = 0; j < sample_size; j++){
            for(unsigned int i = 0; i < n; i++){
                remove(&arr[j],i);
            }
        }
        end = chrono::steady_clock::now();
        auto delete_time = (chrono::duration_cast<chrono::milliseconds>(end-begin)).count();
        for(unsigned int j = 0; j < sample_size; j++){
            erase_table(&arr[j]);
        }
        output_file << n << "," << init_time << "," << search_time << "," << delete_time << std::endl;
    }
}
int main(){
    hash_table();
    return 0;
}