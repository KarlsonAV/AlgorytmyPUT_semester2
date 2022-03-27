#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>  

using namespace std;

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void printArray(int array[], int size) {
  int i;
  for (i = 0; i < size; i++)
    cout << array[i] << " ";
  cout << endl;
}

int partition(int array[], int low, int high) {
    
  int pivot = array[high];
  int i = (low - 1);
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {

      i++;
      swap(&array[i], &array[j]);
    }
  }
  swap(&array[i + 1], &array[high]);
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, high);
  }
}

void Cb() {

    for (int n = 1000; n <= 20000; n += 1000) {
        int A[n];
        int prev = 0;
        for (int i = 0; i < n; i++) {
            
            int number;
            
            do {

                number = rand() % 100000;

            } while (number == prev);
            
            prev = number;
            A[i] = number;
           
        }
        
        clock_t tStart = clock();

        int B[n];
        for (int i = 0; i < n; i++) {
            B[i] = A[i];
        }

        
        quickSort(B, 0, n-1);
    
        printf("%.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);
    }
}

void Sa() {

    for (int n = 1000; n <= 20000; n += 1000) {
        int A[n];
        int prev = 0;
        for (int i = 0; i < n; i++) {
            
            int number;
            
            do {

                number = rand() % 100000;

            } while (number == prev);
            
            prev = number;
            A[i] = number;
           
        }

        int B[n];
        for (int i = 0; i < n; i++) {
            B[i] = A[i];
        }

        
        quickSort(B, 0, n-1);
    
        clock_t tStart = clock();
    
        int check = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (B[i] == A[j]) {
                    check++;
                    break;
                }
            }
        }

        printf("%.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);
    }
}

void Sb() {

       for (int n = 1000; n <= 20000; n += 1000) {
        int A[n];
        int prev = 0;
        for (int i = 0; i < n; i++) {
            
            int number;
            
            do {

                number = rand() % 100000;

            } while (number == prev);
            
            prev = number;
            A[i] = number;
           
        }

        int B[n];
        for (int i = 0; i < n; i++) {
            B[i] = A[i];
        }

        quickSort(B, 0, n-1);
        clock_t tStart = clock();

        for (int i = 0; i < n; i++) {
            int left = 0;
            int right = n-1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (B[mid] == A[i]) {
                    break;
                }

                else if (B[mid] < A[i]) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
        }
        printf("%.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);
    }
}

struct BstNode {
    int data;
    BstNode* left;
    BstNode* right;
    BstNode(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

BstNode* Insert(BstNode* root, int data) {

    if (root == NULL) {
        return new BstNode(data);
    }

    else if (data <= root->data) {
        root->left = Insert(root->left, data);
    }
    else {
        root->right = Insert(root->right, data);
    }
    return root;
}

BstNode* arrayToBST(int arr[], int n) {
    BstNode* root = NULL;
    for (int i = 0; i < n; i++) {
        root = Insert(root, arr[i]);
    }
    return root;
}

BstNode* sortedArraytoBST(int arr[], int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    BstNode* root = new BstNode(arr[mid]);
    root->left = sortedArraytoBST(arr, start, mid-1);
    root->right = sortedArraytoBST(arr, mid+1, end);
    return root;
}

void PreorderPrint(BstNode* root) {
    if (root == NULL) return;

    cout << root->data << " ";
    PreorderPrint(root->left);
    PreorderPrint(root->right);
}

bool Search(BstNode* root, int data) {
    if (root == NULL) return false;
    else if (root->data == data) return true;
    else if (data <= root->data) return Search(root->left, data);
    else return Search(root->right, data);
}

int FindHeight(BstNode* root) {

    if (root == NULL) return -1;
    int left_hight = FindHeight(root->left);
    int right_hight = FindHeight(root->right);

    return max(left_hight, right_hight) + 1;
}

void Cta() {

       for (int n = 1000; n <= 20000; n += 1000) {
        int A[n];
        int prev = 0;
        for (int i = 0; i < n; i++) {
            
            int number;
            
            do {

                number = rand() % 100000;

            } while (number == prev);
            
            prev = number;
            A[i] = number;
           
        }

        clock_t tStart = clock();
        BstNode* root = arrayToBST(A, n);
        printf("%.3f",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);
        cout << ", wysokość - " << FindHeight(root);

        tStart = clock();

        for (int i = 0; i < n; i++) {
            Search(root, A[i]);
        }

        printf(", czas wyszukiwania kolejnych elementow - %.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);

    }
}

void Ctb() {

       for (int n = 1000; n <= 20000; n += 1000) {
        int A[n];
        int prev = 0;
        for (int i = 0; i < n; i++) {
            
            int number;
            
            do {

                number = rand() % 100000;

            } while (number == prev);
            
            prev = number;
            A[i] = number;
           
        }

        int B[n];
        for (int i = 0; i < n; i++) {
            B[i] = A[i];
        }

        quickSort(B, 0, n-1);
        clock_t tStart = clock();
        BstNode* root = sortedArraytoBST(B, 0, n);
        printf("%.3f",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);

        cout << ", wysokość - " << FindHeight(root);

        tStart = clock();

        for (int i = 0; i < n; i++) {
            Search(root, A[i]);
        }

        printf(", czas wyszukiwania kolejnych elementow - %.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);

    }
}

int main() 
{
    cout << "-----\n-----" << endl;
    cout << "Cb - Tworzenie kopii i sortowania" << endl;
    Cb();
    cout << "-----\n-----" << endl;
    cout << "Sa - Czas wyszukiwania kolejnych elementow tablicy A" << endl;
    Sa();
    cout << "-----\n-----" << endl;
    cout << "Sb - Czas wyszukiwania kolejnych elementów tablicy A w tablicy B na zasadzie dzielenia połówkowego" << endl;
    Sb();
    cout << "-----\n-----" << endl;
    cout << "Cta - Czas tworzenia drzewa TA, oraz Sta" << endl;
    Cta();
    cout << "-----\n-----" << endl;
    cout << "Ctb - Czas tworzenia drzewa TB, oraz Stb" << endl;
    Ctb();
    cout << "-----\n-----" << endl;

}

    


