/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 背包问题
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e6+1;
const int X=5001;

int x, n, a[N], v[N];
long f[X][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> x;
    for (int i=0; i<n; ++i) {
        cin >> a[i] >> v[i];
    }

    f[0][1] = 1;
    for (int i=0; i<n; ++i) {
        for (int j=x; j>=v[i]; --j) {
            if (f[j-v[i]][1]) {
                f[j][0] = max(f[j][0], f[j-v[i]][0]+a[i]);
                f[j][1] = 1;
            }
        }
    }

    if (f[x][1]) {
        cout << f[x][0] << "\n";
    } else {
        cout << "Got caught!\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
