#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int MAXN = 200005;
int arr[MAXN];
ll ST[MAXN * 4];

void update(int id, int left, int right, int x, int v){
     if (right < x || x < left)    return;
     if (left == right){
          ST[id] = v;
          return;
     }
     int mid = (left + right) / 2;
     update(id * 2, left, mid, x, v);
     update(id * 2 + 1, mid + 1, right, x, v);
     ST[id] = ST[id * 2] + ST[id * 2 + 1];
}

ll get(int id, int left, int right, int u, int v)
{
     if (right < u || v < left)    return 0;
     if (u <= left && right <= v)  return ST[id];
     int mid = (left + right) / 2;
     return get(id * 2, left, mid, u, v) + get(id * 2 + 1, mid + 1, right, u, v);
}

int main(){
     ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
     int n, q;
     cin >> n >> q;
     for (int i = 1; i <= n; i++){
          cin >> arr[i];
          update(1, 1, n, i, arr[i]);
     }
     while(q--){
          int t; cin >> t;
          if (t == 1){
               int x, v;
               cin >> x >> v;
               update(1, 1, n, x, v);
          }
          else{
               int x; cin >> x;
               cout << get(1, 1, n, 1, x) << endl;
          }
     }
     return 0;
}