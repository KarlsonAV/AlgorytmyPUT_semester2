#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdlib.h>
#include <time.h> 

using namespace std;

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

void CS(vector<int> &arr, int n) {

    int k = arr[0];
    
    for (int i = 0; i < n; i++) {
        if (arr[i] > k) {
            k = arr[i];
        }
    }
    vector<int> store(k+1);
    for (int i = 0; i < k+1; i++) {
        store[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        store[arr[i]]++; 
    }
 
    for (int i = 1; i < k+1; i++) {
      
        store[i] += store[i-1];
    }
    vector<int> final(n);
    for (int i = 0; i < n; i++) {
        final[i] = 0; 
    }

    for (int i = 0; i < n; i++) {
        final[store[arr[i]]-1] = arr[i];
        store[arr[i]]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = final[i];
    }

}

int main() {
    for (int i = 1000; i < 10001; i+=1000) {
        vector<int> arr;
        for (int j = 0; j < (i*0.01)+1; j++) {
            int val = rand() % 10000 + 1;
            arr.push_back(val);
        }
    clock_t tStart = clock();
    CS(arr, i*0.01);
    printf("%.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);
    }
}