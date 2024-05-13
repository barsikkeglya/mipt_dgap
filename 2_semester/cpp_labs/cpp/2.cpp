#include <iostream>

int main(){
    int n = 0;
    std::cin >> n;
    auto data = new(std::nothrow) int[100][100];
    auto c1 = new (std::nothrow) int[100][100][3];
    auto process = new (std::nothrow) int[100][100][3];
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            std::cin >> data[i][j];
        }
    }
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            auto count_2 = 0;
            auto count_5 = 0;
            auto copy_2 = data[i][j];
            auto copy_5 = data[i][j];
            while (copy_2 % 2 == 0){
                count_2++;
                copy_2 /= 2;
            }
            while (copy_5 % 5 == 0){
                count_5++;
                copy_5 /= 2;
            }
            c1[i][j][2] = 0;
            while (count_2 > 0 and count_5 > 0){
                count_2--;
                count_5--;
                c1[i][j][2]++;
            }
            c1[i][j][0]=count_2;
            c1[i][j][1]=count_5;
        }
    }
    process[0][0][0]=c1[0][0][0];
    process[0][0][1]=c1[0][0][1];
    process[0][0][2]=c1[0][0][2];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if ((i == 0 or j == 0) and (i+j != 0)){
                process[i][j][0]=process[i-1][j][0]+c1[i][j][0];
                process[i][j][1]=process[i-1][j][1]+c1[i][j][1];
                process[i][j][2]=process[i-1][j][2]+c1[i][j][2];
                auto count_2 = process[i][j][0];
                auto count_5 = process[i][j][1];
                while (count_2 > 0 and count_5 > 0){
                        count_2--;
                        count_5--;
                        process[i][j][2]++;
                    }
                process[i][j][0]=count_2;
                process[i][j][1]=count_5;
            }
            
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            std::cout << process[i][j][1] << " ";
        }
        std::cout << std::endl;
    }
    delete[] c1;
    delete[] data;
    delete[] process;
    return 0;
}