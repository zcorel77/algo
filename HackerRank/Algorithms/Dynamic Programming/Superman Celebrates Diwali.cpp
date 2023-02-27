/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 前I层, 各个楼各层累计计数
 * 之后, 上一层累计计数与上I层整层最大值比较, 取较大值累计到本层
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1901;
const int H=1901;

int n, h, k, u, v, p[H][N], ma[H];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    memset(ma, 0, sizeof(ma));
    memset(p, 0, sizeof(p));

    cin >> n >> h >> k;
    for (int i=0; i<n; ++i) {
        cin >> u;
        for (int j=0; j<u; ++j) {
            cin >> v; --v;
            ++p[v][i];
        }
    }

    for (int i=h-1; i>=h-k; --i) {
        for (int j=0; j<n; ++j) {
            p[i][j]+=p[i+1][j];
            ma[i]=max(ma[i], p[i][j]);
        }
    }

    for (int i=h-k-1; i>=0; --i) {
        for (int j=0; j<n; ++j) {
            p[i][j]+=max(p[i+1][j], ma[i+k]);
            ma[i]=max(ma[i], p[i][j]);
        }
    }

    cout << ma[0] << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
