#include <bits/stdc++.h>

using namespace std;

#define ll long long
const int MAXN = 100005;
ll arr[MAXN];
int t[MAXN * 4];

int Add(int i, int j){
     return (arr[i] > arr[j]) ? i : j;
}

void update(int id, int left, int right, int pos)
{
     if (pos < left || pos > right)     return;
     if (left == right){
          t[id] = pos;
          return;
     }
     int mid = (left + right) / 2;
     update(id * 2, left, mid, pos);
     update(id * 2 + 1, mid + 1, right, pos);
     t[id] = Add(t[id * 2], t[id * 2 + 1]);
}

int Get(int id, int left, int right, int u, int v){
     if (u > right || v < left || left > right)    return 0;
     if (u <= left && right <= v){
          return t[id];
     }
     int mid = (left + right) / 2;
     int index1 = Get(id * 2, left, mid, u, v);
     int index2 = Get(id * 2 + 1, mid + 1, right, u, v);
     return Add(index1, index2);
}

ll Mul(ll a, ll b, ll MOD){
     if (b == 0)    return 0;
     ll t = Mul(a, b / 2, MOD) * 2;
     if (b % 2)     t += a;
     return t % MOD;
}

int main(){
     ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
     int n; cin >> n;
     for (int i = 1; i <= n; i++){
          cin >> arr[i];
          update(1, 1, n, i);
     }
     arr[0] = 1;
     int m; cin >> m;
     while (m--){
          int t; cin >> t;
          if (t == 0){
               int x;
               ll v;
               cin >> x >> v;
               arr[x] = v;
               update(1, 1, n, x);
          }
          else{
               int l, r;
               ll MOD;
               cin >> l >> r;
               cin >> MOD;
               if (l == r){
                    cout << arr[l] % MOD << endl;
                    continue;
               }
               int index1 = Get(1, 1, n, l, r);
               int index2 = Get(1, 1, n, l, index1 - 1);
               int index3 = Get(1, 1, n, index1 + 1, r);
               int index = Add(index2, index3);
               cout << Mul(arr[index1], arr[index], MOD) << endl;
          }
     }
     return 0;
}