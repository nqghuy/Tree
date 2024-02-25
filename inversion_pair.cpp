#include <bits/stdc++.h>

using namespace std;

#define ll long long

//problem: https://oj.vnoi.info/problem/NKINV

const int MAXN = 60005;
ll BIT[MAXN], arr[MAXN];

//các chỉ số quản lí x tăng 1
void update(int x, int value){
    while (x > 0){
        BIT[x] += value;
        x -= x & (-x);
    }
}

//số các số >= x đã xuất hiện
ll get(int x, int n){
    ll res = 0;
    while (x <= n){
        res += BIT[x];
        x += x & (-x);
    }
    return res;
}

int main(){
    int n; cin >> n;
    memset(BIT, 0, sizeof(BIT));

    //final answer
    ll res = 0;

    //số lớn nhất từng xuất hiện
    ll maxNum = INT_MIN;
    for (int i = 1; i <= n; i++){
        cin >> arr[i];
        maxNum = max(maxNum, arr[i]);
        update(arr[i], 1);
        res += get(arr[i] + 1, maxNum);
    }
    cout << res;
    return 0;
}