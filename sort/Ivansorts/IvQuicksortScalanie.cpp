#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdlib.h>
#include <time.h> 

using namespace std;

int n,k;
vector <int> vec;

void sorting(int l, int r){
    if (r-l == 1){
        if (vec[l] > vec[r]){
            swap(vec[l],vec[r]);
            return ;
        }
    }
    if (r-l == 0){
        return ;
    }

    int mid = (r+l)/2;
        sorting(l, mid);
        sorting(mid+1, r);
    int x,y;
    vector <int> mas;
    x = l;
    y = mid+1;

    while (x<=mid || y<=r){
        if (x>mid){
            mas.push_back(vec[y]);
            y++;
        } else if (y>r){
            mas.push_back(vec[x]);
            x++;
        } else if(vec[x] >= vec[y]){
            mas.push_back(vec[y]);
            y++;
        } else {
            mas.push_back(vec[x]);
            x++;
        }
   }

   int j=0;
   for (int i=l; i<=r; i++){
        vec[i] = mas[j];
        j++;
   }
   return ;
}

int main(){

    for (int i = 1000; i < 10001; i+=1000) {
        vector<int> arr;
        for (int j = 0; j < i+1; j++) {
            int val = rand() % 10000 + 1;
            arr.push_back(val);
        }
    clock_t tStart = clock();
    vec.resize(n);
    int l = 0;
    int r = i - 1;
    sorting(l, i-1);
    printf("%.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);
    }


return 0;
}
