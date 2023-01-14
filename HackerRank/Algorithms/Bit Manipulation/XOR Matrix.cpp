/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 利用杨辉三角直接计算每个数
 * 问题转化为求解杨辉三角中每个数的奇偶性
 * 注意到杨辉三角第2^i行奇偶性仅头尾两个数为奇数
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+1;

int n, a[N], b[N];
long m, k;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m; --m;
    for (int i=0; i<n; ++i) cin >> a[i];

    for (long k=(1L<<62); k>0; k>>=1) {
        if (!(m&k)) continue;
        for (int i=0; i<n; ++i) {
            b[i]=a[i]^a[(i+k)%n];
        }
        swap(a, b);
    }

    for (int i=0; i<n; ++i) {
        cout << a[i] << (i==n-1?"\n":" ");
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
