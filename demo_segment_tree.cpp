#include <bits/stdc++.h>

using namespace std;

#define ll long long

//problem: https://codeforces.com/gym/458672/problem/B

const int MAXN = 200005;
int arr[MAXN];
ll t[4 * MAXN];

void build(int id, int left, int right)
{
    if (left == right)
    {
        t[id] = arr[left];
        return;
    }
    int mid = (left + right) / 2;
    build(id * 2, left, mid);
    build(id * 2 + 1, mid + 1, right);

    //id has 2 children which are id * 2 and id * 2 + 1
    t[id] = t[id * 2] + t[id * 2 + 1]; 
}

ll get(int id, int left, int right, int u, int v)
{
    //if left-right and u-v do not intersect    
    if (u > right || v < left)  return 0;

    //if u-v contains left-right
    if (u <= left && v >= right)  return t[id];

    int mid = (left + right) / 2;
    return get(id * 2, left, mid, u, v) + get(id * 2 + 1, mid + 1, right, u, v);
}

void update(int id, int left, int right, int pos, int value)
{
    //if left-right do not contain pos
    if (pos < left || pos > right) return;

    //base case
    if (left == right)
    {
        t[id] = value;
        arr[pos] = value;
        return;
    }
    int mid = (left + right) / 2;
    update(id * 2, left, mid, pos, value);
    update(id * 2 + 1, mid + 1, right, pos, value);

    //update
    t[id] = t[id * 2] + t[id * 2 + 1];
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++){
        cin >> arr[i];
        update(1, 1, n, i, arr[i]);
    }
    // build(1, 1, n);
    while(q--){
        int tmp; cin >> tmp;
        if (tmp == 1){
            int i, x;
            cin >> i >> x;
            update(1, 1, n, i, x);
        }
        else{
            int left, right;
            cin >> left >> right;
            cout << get(1, 1, n, left, right) << '\n';
        }
    }
    return 0;
}