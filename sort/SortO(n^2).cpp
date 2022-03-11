#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main()
{
     int n, INF = -1000000000; cin >> n;
    vector <int> vec(1+n);
    vec[0] = INF;
    for (int i=1; i<=n; i++){
        cin >> vec[i];
    }
    
    // sortowanie przez  proste wstawianie O(n^2)
    for (int i=1; i<=n; i++){
        int k=i;
        while(vec[k]<vec[k-1]){
            swap(vec[k],vec[k-1]);
            k--;
        }

    }
    
    
    // sortowamie przez proste wybieranie O(n^2)
    for (int i=1; i<n;i++){
    int x = vec[i], xi = i;
        for (int j=i+1; j<=n; j++){
            if (x > vec[j]){
                x = vec[j]; xi = j;
            }
        }
    swap(vec[i], vec[xi]);
    }
    

    //sortowanie bąbelkowe O(n^2)
    for (int i=1; i<n; i++){
        for (int j=i+1; j<n+1; j++){
            if (vec[i] >vec[j]){
                swap(vec[i],vec[j]);
            }
        }
    }



    for (int i=1; i<=n; i++){
        cout <<" " << vec[i];
    }
    return 0;
}
