#include <bits/stdc++.h>

using namespace std;

#define ll long long

//problem: https://www.youtube.com/watch?v=KChpxPuKqoI&t=1468s 27:09

const int MAXN = 10005;

//a sequence of integer numbers
ll arr[MAXN] = {};

//Binary indexed trees: BIT[i] = the value of the interval ending at i 
//10: 0001010 => index of the far right 1 is 2 so BIT[10] = arr[10] + arr[9];
ll BIT[MAXN] = {};

//linear complexity
void make(int n)
{
    copy(arr, arr + n + 1, BIT);
    for (int i = 1; i <= n; i++){
        int next = i + (i & (-i));
        if (next <= n){
            BIT[next] = BIT[next] + BIT[i];
        }
    }
}


void update(int index, int value, int n)
{
    arr[index] = value;
    while (index <= n){
        BIT[index] += value;
        index += index & (-index);
    }
}

int get_sum(int index)
{
    int sum = 0;
    while (index > 0){
        sum += BIT[index];
        index -= index & (-index);
    }
    return sum;
}

int main(){
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++){
        cin >> arr[i];
    }

    //populate the finding tree
    make(n);


    while (q--){
        int t; cin >> t;
        if (t == 1){
            int x, v;
            cin >> x >> v;
            
            //update BIT
            update(x, v - arr[x], n);
        }
        else if (t == 2)
        {
            int x; cin >> x;
            cout << get_sum(x) << endl;
        }
    } 

    return 0;
}