#include <iostream>
#include <chrono>
#include <random>


int mass[1000000] = {};


void rand_mass_lin(int size) { // заполняет первые size элементов mass числами от 0 до size-1
    std::default_random_engine rng((int)time(0));
    std::uniform_int_distribution<unsigned>dstr(0, size - 1);
    
    for (int counter = 0; counter < size; ++counter) {
        mass[counter] = dstr(rng);
    }
}

bool poisk_lin(int beg, int end, int x){ // осуществляет поиск числа x в первых size элементах mass простым перебором
    int size = end - beg + 1;
    for (int i = 0; i < size; ++i) {
        if (mass[i] == x) {
            return true;
        }
    }
    return false;
}




void rand_mass_bin(int size) { // заполняет первые size элементов mass случайными отсортированными во возрастанию числами
    std::default_random_engine rng((int)time(0));
    std::uniform_int_distribution<unsigned>dstr(0, 10);
    
    for (int counter = 0; counter < size; ++counter) {
        if (counter == 0) {
            mass[counter] = dstr(rng);
        }
        else{
            mass[counter] = mass[counter - 1] + dstr(rng);
        }
    }
}

bool poisk_bin(int beg, int end, int x){ // бинарный поиск x в части массива от beg до end
    int size = end - beg + 1;
    while (end >= beg) {
        size = end - beg + 1;
        int mid = beg + size/2;
        if (mass[mid] == x) {
            return true;
        }
        else if (mass[mid] > x){
            end = mid - 1;
        }
        else {
            beg = mid + 1;
        }
    }
    return false;
}




float poisk_time(bool(*poisk)(int beg, int end, int x), int size, int x) {
    // считает сколько времени выполняется функция poisk_lin и выводит это время вместе с size
    long long repeat = 5000;
    auto begin = std::chrono::steady_clock::now();
    
    for (int j = 0; j < repeat; ++j) {
        poisk(0, size - 1, x);
    }
        
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    return ((time_span.count() + 0.0)/repeat);
}




void data_max(void(*rand_mass)(int size), bool(*poisk)(int beg, int end, int x)){ // запускает poisk для 100 длин массива от 100 до 1000000 для числа, которого точно нет в массиве
    std::cout << "max data for lineral search\n";
    for (int size = 100; size <= 1000000; size+=9999) {
        rand_mass(size);
        std::cout << size << ' ' << poisk_time(poisk, size, -1) << '\n';
    }
    std::cout << '\n';
}

void data_average(void(*rand_mass)(int size), bool(*poisk)(int beg, int end, int x)){
    /*
     Для длин массивов от 100 до 1000000 er раз заполняет массив случайными числами, а потом ищет в массиве случайное число и
     выводит время выполнения поиска и соотвествующий размер массива
     */
    std::cout << "average data for lineral search\n";
    srand((int)time(0));
    int er = 30;
    for (int size = 100; size <= 1000000; size+=9999) {
        float s = 0;
        for (int u = 0; u < er; ++u) {
            int r = rand() % size;
            rand_mass(size);
            s += poisk_time(poisk, size, r);
        }
        std::cout << size << ' ' << s/(er + 0.0) << '\n';
    }
        
}
        



int main() {
    //data_max(rand_mass_lin, poisk_lin); // выводит данные для макс времени линейного поиска
    //data_average(rand_mass_lin, poisk_lin); // выводит даннеы для среднего времени линейного поиска
    //data_max(rand_mass_bin, poisk_bin); // выводит данные для макс времени бинарного поиска
    data_average(rand_mass_bin, poisk_bin); // выводит данные для среднего времени бинарного поиска

    return 0;
}
