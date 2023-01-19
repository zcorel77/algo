/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * A: 0, B: 1, C: 2, D: 3
 * 突变就是异或(x,y)->x^y
 * 每轮突变就是杨辉三角参数往下一层
 * 第2^i轮参数x[i]=x[i]^x[(i+2^i)%n]
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e6+1;

int n, k, a[N], b[N];
string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    cin >> s;
    for (int i=0; i<n; ++i) {
        a[i]=s[i]-'A';
    }

    for (int m=(1<<30); m>0; m>>=1) {
        if (!(k&m)) continue;
        for (int i=0; i<n; ++i) {
            b[i]=a[i]^a[(i+m)%n];
        }
        swap(a, b);
    }

    for (int i=0; i<n; ++i) {
        cout << (char)(a[i]+'A');
    }
    cout << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
