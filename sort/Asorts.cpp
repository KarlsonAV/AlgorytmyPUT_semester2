#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void SS(vector<int> &arr, int n);
void IS(vector<int> &arr, int n);
void BS(vector<int> &arr, int n);
void MS(vector<int> &arr, int n);

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
    vector<int> arr(n+1);
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
            break;
        case 5:
            MS(arr,n);
            break;

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

void MS(vector<int> &arr, int n) {
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
