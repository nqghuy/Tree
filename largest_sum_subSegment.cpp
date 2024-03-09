#include <bits/stdc++.h>
 
using namespace std;
 
#define ll long long
 
//problem: https://codeforces.com/gym/458672/problem/D

const int MAXN = 200005;
 
int arr[MAXN];

//sum of id
ll ST[MAXN * 4];

//suffix sum of id
ll suffixST[MAXN * 4];

//prefix sum of id
ll prefixST[MAXN * 4];

//max sum of id
ll res[MAXN * 4];
 
void update (int id, int left, int right, int pos, ll value){
     if (pos < left || pos > right)     return;

     //base case
     if (left == right){
          ST[id] = value;
          suffixST[id] = value;
          prefixST[id] = value;
          res[id] = value;
          return;
     }
     //recursion in two sides
     int mid = (left + right) / 2;
     update(id * 2, left, mid, pos, value);
     update(id * 2 + 1, mid + 1, right, pos, value);
     
     //update 
     ST[id] = ST[id * 2] + ST[id * 2 + 1];

     //draw to know more
     prefixST[id] = max(prefixST[id * 2], ST[id * 2] + prefixST[id * 2 + 1]);
     suffixST[id] = max(suffixST[id * 2 + 1], suffixST[id * 2] + ST[id * 2 + 1]);
     res[id] = max({res[id * 2], res[id * 2 + 1], prefixST[id * 2 + 1] + suffixST[id * 2]});
}
 
int main(){
     ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
     int n, m;
     cin >> n >> m;
     for (int i = 1; i <= n; i++){
          cin >> arr[i];
          update(1, 1, n, i, arr[i]);
     }
     while (m--){
          int pos;
          ll value;
          cin >> pos >> value;
          update(1, 1, n, pos, value);
          cout << max(res[1], 1ll *0) << '\n';
     }
     return 0;
}