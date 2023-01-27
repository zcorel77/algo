/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 如下构造
 * 第一列 自然序列, 0~2n/3 
 *       0, 1, 2, 3, 4, 5, 6, 7, 8
 * 第二列 错开n/3, 比如n=12, 错开4, 然后shift补齐
 *       4, 5, 6, 7, 8, 0, 1, 2, 3
 * 第三列 n-前两列
 *       8, 6, 4, 2, 0, 7, 5, 3, 1
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, k, m, l;
    cin >> n;

    k=2*n/3;
    cout << k+1 << "\n";

    // 偏移量
    m=2*k-n;
    // 增量
    l=n-2*m;
    // 第二列上界
    m=n-m+1;
    for (int i=0, j; i<=k; ++i) {
        j=(i+l)%m;
        cout << i << " " << j << " " << n-i-j << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
