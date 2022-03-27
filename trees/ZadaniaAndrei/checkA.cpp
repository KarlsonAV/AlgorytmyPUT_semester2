#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>  
#include <chrono>
#include <thread>

using namespace std;

int ctc;

void funcSleep()
{
    std::this_thread::sleep_for(std::chrono::seconds (3));
}

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

int binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l) {
        int mid = (l+r)>>1;
 
        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return mid;
 
        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
 
        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, x);
    }
 
    // We reach here when element is not
    // present in array
    return -1;
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

int itct = 0;
void Copy_Table(BstNode* root, int arr[]) {
    if (root == NULL) return;

    arr[itct++] = root->data;
    Copy_Table(root->left, arr);
    Copy_Table(root->right, arr);
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

int main() {
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

             BstNode* root = arrayToBST(A, n);
             ctc = 0;


    auto start = std::chrono::high_resolution_clock::now();

            for (int i = 0; i < n; i++) {
                Search(root, A[i]);
            }

             auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::milli> float_ms = end - start;
            cout << "For " << n << " elements BST rand: " << float_ms.count() << endl;

            ctc = 0;
            
            start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < n; i++) {
                binarySearch(B, 0, n-1, A[i]);
            }
            end = std::chrono::high_resolution_clock::now();

            float_ms = end - start;


            cout << "For " << n << " elements Binary searcћh: " << float_ms.count() << endl;

     }
}
