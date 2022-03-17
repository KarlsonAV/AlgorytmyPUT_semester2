#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

void IS(vector<int> &arr, int n) {

    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j-1]) {
                swap(arr[j],arr[j-1]);
            }
        }
    }
    return;
}

void QS(vector<int> &arr,int left, int right) {

    if (left >= right) {
        return;
    }

    int l = left;
    int r = right;
    int piv_idx = (left + right) / 2;
    double pivot = arr[piv_idx];
    swap(arr[piv_idx], arr[right]);
    piv_idx = right;
    right--;

    while (right >= left) {

       if (arr[left] >= pivot) {
            if (arr[right] <= pivot) {
                swap(arr[left],arr[right]);
                left++;
                right--;
            }
            else {
                right--;
            }
        }
        else if (arr[right] <= pivot) {
            left++;
        }
        else {
            left++;
            right--;
        }
    }

    swap(arr[left],arr[piv_idx]);
    QS(arr,l,right);
    QS(arr,left+1,r);
    
}


int main() {

    cout << "------------------\n------------------" << endl;
    cout << "IS czas dla układu losowego " << endl;

    for (int i = 1000; i < 10001; i+=1000) {
        vector<int> arr;
        for (int j = 0; j < i; j++) {
            arr.push_back(rand() % 1000 + 1);
        }

    clock_t tStart = clock();
    IS(arr,i);
    printf("%.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);
    }

    cout << "------------------\n------------------" << endl;
    cout << "IS czas dla układu rosnącego" << endl;

    for (int i = 1000; i < 10001; i+=1000) {
        vector<int> arr;
        int sum = 0;
        for (int j = 0; j < i; j++) {
            arr.push_back(sum);
            sum += 2;
        }
    
    clock_t tStart = clock();
    IS(arr,i);
    printf("%.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);
    }

    cout << "------------------\n------------------" << endl;
    cout << "QS(Średni) czas dla układu losowego " << endl;

    for (int i = 1000; i < 10001; i+=1000) {
        vector<int> arr;
        for (int j = 0; j < i; j++) {
            arr.push_back(rand() % 1000 + 1);
        }

    clock_t tStart = clock();
    QS(arr, 0, i-1);
    printf("%.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);
    }

    cout << "------------------\n------------------" << endl;
    cout << "QS(Średni) czas dla układu rosnącego" << endl;

    for (int i = 1000; i < 10001; i+=1000) {
        vector<int> arr;
        int sum = 0;
        for (int j = 0; j < i; j++) {
            arr.push_back(sum);
            sum += 2;
        }

    clock_t tStart = clock();
    QS(arr, 0, i-1);
    printf("%.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);
    }

} 