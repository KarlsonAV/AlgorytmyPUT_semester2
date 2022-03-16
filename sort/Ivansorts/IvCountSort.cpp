#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector <int> vec(2000001);

int main(){
    int n, x; cin >>  n;
    for (int i=0; i<n; i++){
        cin >> x;
        vec[x+1000000]++;
    }
    
    for (int i=0; i<2000001; i++){
        for (int j=0; j<vec[i]; j++){
            cout << i-1000000 << " ";
        }
    }

       return 0;
}
