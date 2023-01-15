/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 查找最大k~(0,31), b[i] = a[i]>>k, b[i] 重复不超过n/2 
 */

#include <bits/stdc++.h>

using namespace std;

const int N=101;
const int C=32;

int n, a;
map<int, int> m, mm;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    int ma=0;
    for (int i=0; i<n; ++i) {
        cin >> a;
        ++m[a];
        ma=max(ma, m[a]);
    }

    for (int i=0; i<C; ++i) {
        if (ma > n/2) {
            cout << i-1 << "\n";
            break;
        }

        swap(m, mm);
        m.clear();

        for (auto &e: mm) {
            a=e.first>>1;
            m[a]+=e.second;
            ma=max(ma, m[a]);
        }
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
