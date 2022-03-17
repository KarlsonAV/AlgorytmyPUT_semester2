#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;


int partition(vector<int> &array, int low, int high) {

  int pivot = array[high];
  int i = (low - 1);
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;
      swap(array[i], array[j]);
    }
  }
  swap(array[i + 1], array[high]);
  return (i + 1);
}

void quickSort(vector<int> &array, int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, high);
  }
}


int main() {
  
  cout << "------------------\n------------------" << endl;
  cout << "QS(Skrajny) czas dla układu rosnącego " << endl;
  for (int i = 1000; i < 10001; i += 1000) {
      vector<int> data;
      int sum = 0;
      for (int j = 0; j < i; j++) {
          data.push_back(sum);
          sum +=2;
      }
  clock_t tStart = clock();
  quickSort(data, 0, i - 1);
  printf("%.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);

  }

  cout << "------------------\n------------------" << endl;
  cout << "QS(Skrajny) czas dla układu losowego " << endl;

  for (int i = 1000; i < 10001; i += 1000) {

      vector<int> data;

      for (int j = 0; j < i; j++) {
          data.push_back(rand() % 1000 + 1);
      }
  clock_t tStart = clock();
  quickSort(data, 0, i - 1);
  printf("%.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);

  }
  cout << "------------------\n------------------" << endl;
}