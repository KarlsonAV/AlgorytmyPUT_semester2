#include <iostream>
#include <vector>
#include <cmath>

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
    int l,r;
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
