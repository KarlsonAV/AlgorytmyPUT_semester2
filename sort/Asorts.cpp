#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void SS(vector<int> &arr, int n);
void IS(vector<int> &arr, int n);
void BS(vector<int> &arr, int n);
void MSa(vector<int> &arr, int n);
void QS(vector<int> &arr, int left, int right);
vector<int> MS(vector<int> arr, int n);
void HS(vector<int> &arr, int n);
void Heapify(vector<int> &arr, int r, int n);
void BuildHeap(vector<int> &arr, int n);
void CS(vector<int> &arr, int n);

int main() {
    cout << "This program takes as input some numbers and returns sorted list" << endl;
    int n;
    cout << "Enter amount of numbers that you would like to sort: ";
    cin >> n;
    cout << endl;
    if (!cin) {
        cout << "Some error occured" << endl;
        return 1;
    }
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter element of array: ";
        cin >> arr[i];
        cout << endl;
        if (!cin) {
            cout << "Some error occured" << endl;
            return 1;
        }
    }

    cout << "Choose sort method: 1 - SS, 2 - IS, 3 - BS, 4 - HS, 5 - MS, 6 - QS, 7 - CS: ";
    int act;
    cin >> act;

    switch(act) {
        case 1:
            SS(arr,n);
            break;
        case 2:
            IS(arr,n);
            break;
        case 3:
            BS(arr,n);
            break;
        case 4:
            HS(arr,n);
            break;
        case 5:
            arr = MS(arr,n);
            break;
        case 6:
            QS(arr,0,n-1);
            break;
        case 7:
            CS(arr,n);
        default:
            break;
    }
    for (int i = 0; i < n; i++) {
        cout << " " << arr[i] << " ";
    }
    cout << endl;
}

void SS(vector<int> &arr, int n) {
    
    for (int i = 0; i < n - 1; i++) {
        int min = arr[i];
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < min) {
                min = arr[j];
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
    return;
}

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

void BS(vector<int> &arr, int n) {

    for (int i = 0; i < n; i++){
        for (int j = n - 1; j > i; j--) {
            if (arr[j] < arr[j-1]) {
                swap(arr[j], arr[j-1]);
            }
        }
    }
    return;
}

void MSa(vector<int> &arr, int n) {
    for (int d = n / 2; d > 0; d /= 2) {
        for (int i = d; i < n; i++) {
            for(int j = i - d; j >= 0; j -= d) {
                if (arr[j+d] < arr[j]) {
                    swap(arr[j+d], arr[j]);
                }
            }
        }
    }            
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

vector<int> MS(vector<int> arr, int n) {

    if (n == 2) {
        if (arr[0] > arr[1]) {
            swap(arr[0],arr[1]);
        }
    }

    if (n == 1) {
        return arr;
    }

    vector<int> arr_l;
    vector<int> arr_r;

    arr_l = vector<int>(arr.begin(), arr.begin()+((n-1)/2)+1);
    arr_r = vector<int>(arr.begin()+((n-1)/2)+1,arr.end());

    vector<int> left = MS(arr_l, arr_l.size());
    vector<int> right = MS(arr_r, arr_r.size());
    vector<int> merge;

    int left_size = left.size();
    int right_size = right.size();

    while (left_size > 0 && right_size> 0) {
        if (left[0] <= right[0]) {
            merge.push_back(left[0]);
            left.erase(left.begin());
            left_size--;
        }
        else {
            merge.push_back(right[0]);
            right.erase(right.begin());
            right_size--;
        }
    }
    if (left_size < 1) {
        merge.insert(merge.end(),right.begin(),right.end());
    }
    else if (right_size < 1) {
        merge.insert(merge.end(),left.begin(),left.end());
    }

    return merge;
}

void Heapify(vector<int> &arr, int r, int n) {
    int largest = r;
    int left = r * 2 + 1;
    int right = r * 2 + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != r) {
        swap(arr[r], arr[largest]);
        Heapify(arr, largest, n);
    }
} 

void BuildHeap(vector<int> &arr, int n) {

    for (int i = n / 2 - 1; i >= 0; i--) {
        Heapify(arr,i, n);
    }
}

void HS(vector<int> &arr, int n) {

    BuildHeap(arr,n);
    for (int i = n-1; i > 0; i--) {
        swap(arr[0], arr[i]);
        Heapify(arr,0,i);
    }
    return;
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