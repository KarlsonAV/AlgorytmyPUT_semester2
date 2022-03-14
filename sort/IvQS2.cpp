//quicksort from behind

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <time.h>

using namespace std;

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (vector<int> arr, int low, int high){
    int pivot = arr[high]; 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++){
        if (arr[j] < pivot){
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(vector<int> arr, int low, int high){
    if (low < high){
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


int main()
{
    for (int i = 1000; i < 10001; i+=1000) {
        vector<int> arr;
        for (int j = 0; j < i+1; j++) {
            arr.push_back(rand() % 10000 + 1);
        }
    clock_t tStart = clock();
    quickSort(arr, 0, i - 1);
    printf("%.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);
    }
    
    return 0;
}