#pragma once

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Algorytmy sortowania: Merge Sort, Quick Sort, Intro Sort. *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * Helpful functions * * * */
template <typename T>
void display_array(T* arr, int n) {     // displays full array in one line
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

template <typename T>
void swap_values(T* x, T* y) {          // swaps two values
    T tmp = *x;
    *x = *y;
    *y = tmp;
}

template <typename T>
void fill_array(T* arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = ((std::rand() / 10 + 1) * (std::rand() / 10) + 1) % 1000000;
}

/* * * * Merge Sort * * * */
template <typename T>
void merge(T* arr, int left, int middle, int right) {   // merges two subarrays into one sorted array
    int nL = middle - left + 1;                         // find number of elements in the first subarray
    int nR = right - middle;                            // find number of elements in the second subarray
    int i, j, k;
    T* Lhalf;                                           // make new temporary subarrays
    T* Rhalf;
    Lhalf = new T[nL];
    Rhalf = new T[nR];

    for (i = 0; i < nL; i++)                            // copy elements from given array to subarrays
        Lhalf[i] = arr[left + i];
    for (i = 0; i < nR; i++)
        Rhalf[i] = arr[middle + 1 + i];

    i = j = 0;
    k = left;

    while (i < nL && j < nR) {                          // as long as there are elements in subarrays
        if (Lhalf[i] <= Rhalf[j]) {                     // sort their elements
            arr[k] = Lhalf[i];
            i++;
        }
        else {
            arr[k] = Rhalf[j];
            j++;
        }
        k++;
    }
    while (i < nL) {                                    // if there is leftover element in either of subarrays
        arr[k] = Lhalf[i];                              // just add them to the right side of the array
        i++;
        k++;
    }
    while (j < nR) {
        arr[k] = Rhalf[j];
        j++;
        k++;
    }
    delete[] Lhalf;                                     // clean up 
    delete[] Rhalf;
}

template <typename T>
void merge_sort(T* arr, int left, int right) {
    if (left >= right)
        return;
    int mid = (left + right - 1) / 2;               // calculate midpoint of the given array

    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

/* * * * Quick Sort * * * */
template <typename T>
int quickS_part(T* arr, int left, int right) {          // splits array into two parts which are then sorted                           // in relation to 'pivot'
    int position = left;
    int p_index = left + rand() % (right - left);
    T pivot = arr[p_index];
    swap_values(&arr[p_index], &arr[right]);
    for (int i = left; i < right; i++) {            // put values smaller than pivot on left side of the array
        if (arr[i] <= pivot) {
            swap_values(&arr[i], &arr[position]);
            position++;
        }
    }

    swap_values(&arr[position], &arr[right]);           // put pivot after all values smaller than him are on his left

    return position;                                    // return the index of the pivot
}

template <typename T>
void quick_sort(T* arr, int left, int right) {
    if (left < right) {
        int pivot = quickS_part(arr, left, right);
        
        quick_sort(arr, left, pivot - 1);
        quick_sort(arr, pivot + 1, right);
    }
}

/* * * * Heap Sort * * * */
template <typename T>
void heapify(T* arr, int size, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size && arr[left] > arr[largest])
        largest = left;
    if (right < size && arr[right] > arr[largest])
        largest = right;

    if (largest != root) {
        swap_values(&arr[root], &arr[largest]);
        heapify(arr, size, largest);
    }
}

template <typename T>
void heap_sort(T* arr, int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);

    for (int i = size - 1; i >= 0; i--) {
        swap_values(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

template <typename T>
void partial_heap_sort(T* arr, int start, int end) {
    int size = end - start + 1;
    T* tmp = new T[size];
    std::copy(arr + start, arr + end+1, tmp);
    heap_sort(tmp, size);

    for (int i = start; i <= end; i++) {
        arr[i] = tmp[i - start];
    }
}

/* * * * Insertion Sort * * * */
template <typename T>
void insertion_sort(T* arr, int left, int size) {
    for (int i = left; i < size; i++) {
        T k = arr[i];
        int j = i - 1;
        while (k < arr[j] && j >= left) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = k;
    }
}

/* * * * Introspective Sort * * * */
template <typename T>
void introS(T* arr, int left, int right, int maxdepth) {
    if ((right - left) < 16)
        insertion_sort(arr, left, right + 1);
    else if (maxdepth == 0)
        partial_heap_sort(arr, left, right);
    else {
        int pivot = quickS_part(arr, left, right);

        introS(arr, left, pivot - 1, maxdepth - 1);
        introS(arr, pivot + 1, right, maxdepth - 1);
    }
}

template <typename T>
void intro_sort(T* arr, int left, int right) {
    int md = (int)2 * floor(log(right + 1));
    introS(arr, left, right, md);
}