#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main(){
    int j,k,m,x;
    int n; cin >> n;
    vector <int> vec(1+n);
    for (int i=1 ; i<n+1; i++){
        cin >> vec[i];
    }

    for (int i=2; i<=n; i++){
       j=i; k = j/2;
       x = vec[j];
       while (k>0 && vec[k]<x){
        vec[j] = vec[k];
        j=k; k=j/2;
       }
       vec[j] = x;
    }

    for (int i = n; i>=1; i--){
        swap(vec[1], vec[i]);
        j=1; k=2;
        while (k<i){
            m=k;
            if (k+1<i && vec[k+1]>vec[k]){
                m++;
            }
            if (vec[m] <= vec[j]){
                break;
            }
            swap(vec[j], vec[m]);;
            j=m; k = 2*m;
        }
    }

    for (int i = 1 ; i<=n; i++){
        cout << vec[i] << " ";
    }
return 0;
}
