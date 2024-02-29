#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define int long long 

const int MAXN = 10005;
ll arr[MAXN];
ll BIT[15][MAXN];
int n, m;

int Mod(ll value)
{
    if (value >= 0){
        return value % m;
    }
    else return (m - (abs(value) % m)) % m;
}

void update(int x, ll value)
{
    int index = abs(value) % m;
    while (x <= n){
        BIT[index][x] += value;
        x += x & (-x);
    }
}

ll get(int x, int mod){
    ll res = 0;
    while (x > 0){
        res += BIT[mod][x];
        x -= x & (-x);
    }
    return res;
}


main(){
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        cin >> arr[i];
        update(i ,arr[i]);
    }
    int q; cin >> q;
    while (q--){
        char c; cin >> c;
        if (c == 's'){
            int left, right, mod;
            cin >> left >> right >> mod;
            cout << get(right, mod) - get(left - 1, mod) << endl;
        }
        else if (c == '+'){
            int p, r;
            cin >> p >> r;
            update(p, -arr[p]);
            arr[p] += r;
            cout << arr[p] << endl;
            update(p, arr[p]);
        }
        else {
            int p, r;
            cin >> p >> r;
            if (arr[p] < r) {
                cout << arr[p] << endl;
                continue;
            }
            update(p, -arr[p]);
            arr[p] -= r;
            cout << arr[p] << endl;
            update(p, arr[p]);
        }
    }
    return 0;
}