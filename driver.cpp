#include <iostream>
#include <ctime>
#include "algorithms.h"

int main()
{
    static int n = 24;
    int* arr = new int[n];
    int* tmp = new int[n];

    srand(time(NULL));

    fill_array(arr, n);
    std::copy(arr, arr + n, tmp);

    std::cout << "Driver pokazujacy dzialanie sortowan" << std::endl;
    std::cout << "Sortowania beda wykonane na tablicy o rozmiarze 24 i nastepujacych losowych elementach:" << std::endl;
    display_array(arr, n);
    std::cout << std::endl;

    merge_sort(tmp, 0, n - 1);
    std::cout << "Tablica po sortowaniu przez scalanie:" << std::endl;
    display_array(tmp, n);
    std::cout << std::endl;

    std::copy(arr, arr + n, tmp);

    quick_sort(tmp, 0, n - 1);
    std::cout << "Tablica po sortowaniu szybkim:" << std::endl;
    display_array(tmp, n);
    std::cout << std::endl;

    std::copy(arr, arr + n, tmp);

    intro_sort(tmp, 0, n - 1);
    std::cout << "Tablica po sortowaniu introspektywnym:" << std::endl;
    display_array(tmp, n);
    std::cout << std::endl;

    std::cout << "Koniec dzialania programu" << std::endl;

    delete[] arr;
    delete[] tmp;

    return 0;
}