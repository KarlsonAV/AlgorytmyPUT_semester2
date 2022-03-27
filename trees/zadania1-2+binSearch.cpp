#include <bits/stdc++.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

vector <int> a;
vector <int> b;

    int Search_Binary ( int left, int right, int key){
 int midd = 0;
 while (1)
 {
 midd = (left + right) / 2;
 
 if (key < b[midd])       
 right = midd - 1;     
 else if (key > b[midd]) 
 left = midd + 1;    
 else                       
 return midd;          
 
 if (left > right)         
 return -1;
 }
}



void sorting(int l, int r) {
    int i = l, j = r, mid = (l+r)/2, x;
    x = b[mid];

    while ( i <= j) {
        while (b[i]<x) {
            i++;
        }
        while (b[j]>x) {
                j--;
        }
        if (i<=j) {
            swap(b[i], b[j]);
            i++;
            j--;
        }
    }

    if (i<r){
        sorting(i, r);
    }

    if (j>l){
        sorting(l, j);
    }
}

int main() {
    /* измерение времени
    struct timespec start, stop, duration;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

    //Код, время выполнения которого нужно измерить

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);

    if ((stop.tv_nsec - start.tv_nsec) < 0) {
        duration.tv_sec = stop.tv_sec - start.tv_sec - 1;
        duration.tv_nsec = NS_IN_S + stop.tv_nsec - start.tv_nsec;
    } else {
        duration.tv_sec = stop.tv_sec - start.tv_sec;
        duration.tv_nsec = stop.tv_nsec - start.tv_nsec;
    }
    double result = duration.tv_sec + duration.tv_nsec / NS_IN_S;
    */
    



int n;
   //н - от 1000 до 10000
for (n = 1000; n<=20000; n+=1000){
    ///czesc 1
    a.resize(n);
            int prev = 0;
        for (int i = 0; i < n; i++) {

            int number;

            do {

                number = rand() % 100000;

            } while (number == prev);

            prev = number;
            a[i] = number;

        }

    ///czesc 2
    b.resize(n);

    
    b=a;
    sorting(0, n-1);
    
    
    
     
      for (int j=0; j<n; j++){ 
    for (int i=0; i<n; i++){
     
            if (a[i]==b[j]){
                break;
            }
        }
    }
    
    //clock_t tStart = clock();
    for (int i=0; i<n; i++){
        Search_Binary(0,n-1, a[i]);
    }
    //printf("%.3lf\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);
}


  return 0;
}
