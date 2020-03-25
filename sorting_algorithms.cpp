#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include "algorithms.h"

typedef void (*Sorting_algorithms) (int* arr, int left, int right);

int main() {
    std::ofstream ofile;

    const double MAX_TIME = 1000000000;
    const int NUMBER_OF_ARRAYS = 100;
    const int NUMBER_OF_SORTS = 3;
    const int SIZES[5] = { 10000, 50000, 100000, 500000, 1000000 };
    const double SORTED_PERCENT[8] = { 0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997, 1 };

    const std::string FILE_NAMES[NUMBER_OF_SORTS] = {
        "merge_sort.txt",
        "quick_sort.txt",
        "intro_sort.txt"
    };
    Sorting_algorithms sorts[NUMBER_OF_SORTS] = {
        merge_sort,
        quick_sort,
        intro_sort
    };

    srand((int)time(NULL));

    for (int i = 0; i < NUMBER_OF_SORTS; i++) {
        ofile.open(FILE_NAMES[i], std::ios::out);

        for (const int& size : SIZES) {
            ofile << "Size: " << size << std::endl;

            for (const double& sorted : SORTED_PERCENT) {
                double avg = 0;
                double worst = 0;
                double best = MAX_TIME;

                if(sorted != 1)
                    ofile << "Sorted " << sorted * 100 << "%" << std::endl;
                else
                    ofile << "Sorted in descending order" << std::endl;

                for (int j = 0; j < NUMBER_OF_ARRAYS; j++) {
                    int* arr = new int[size];
                    fill_array(arr, size);

                    if (sorted != 0) {
                        if (sorted != 1)
                            std::partial_sort(arr, arr + (int)(size * sorted), arr + size);
                        else
                            std::sort(arr, arr + size, std::greater<>());
                    }

                    auto start = std::chrono::high_resolution_clock::now();
                    sorts[i](arr, 0, size - 1);
                    auto end = std::chrono::high_resolution_clock::now();
                    double time = std::chrono::duration<double, std::milli>(end - start).count();

                    if (worst < time)
                        worst = time;
                    if (best > time)
                        best = time;
                    avg += time;
                    
                    delete[] arr;
                }
                avg /= NUMBER_OF_ARRAYS;

                ofile << "Average time: " << avg << std::endl;
                ofile << "Worst time: " << worst << std::endl;
                ofile << "Best time: " << best << std::endl << std::endl;
            }
        }
        ofile.close();
    }
    return 0;
}