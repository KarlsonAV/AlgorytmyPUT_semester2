#include <iostream>
#include <vector>
#include <cmath>


using namespace std;

vector <int> vec;

void sorting(int l, int r) {
    int i = l, j = r, mid = (l+r)/2, x;
    x = vec[mid];

    while ( i <= j) {
        while (vec[i]<x) {
            i++;
        }
        while (vec[j]>x) {
                j--;
        }
        if (i<=j) {
            swap(vec[i], vec[j]);
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

int main(){
    int l,r,n;
    cin >> n;
    vec.resize(n);
    for (int i=0; i<n; i++){
        cin >> vec[i];
    }
    l=0;
    r=n-1;

    sorting(l,r);

    for (int i=0; i<n; i++){
        cout << vec[i] << " ";
    }

return 0;
}
