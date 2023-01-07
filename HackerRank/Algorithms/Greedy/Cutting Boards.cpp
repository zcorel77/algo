/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 贪心法, 每次裁剪最大的边
 * 纵边排序, 横边排序, 挑出最大纵边与最大横边中的大者进行裁剪,
 * 裁剪次数为另外一方向已经裁剪的边数+1
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e6+1;
const int MOD=1e9+7;

int q, m, n, cost_y[N], cost_x[N];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int i_x, i_y;
    long ans;

    cin >> q;
    while (q--) {
        cin >> m >> n;
        for (int i=1; i<m; ++i) {
            cin >> cost_y[i];
        }
        for (int i=1; i<n; ++i) {
            cin >> cost_x[i];
        }

        sort(cost_x+1, cost_x+n, greater<int>());
        sort(cost_y+1, cost_y+m, greater<int>());

        i_x=1, i_y=1, ans=0L;
        while (i_x<n && i_y<m) {
            if (cost_x[i_x]<cost_y[i_y]) {
                (ans+=cost_y[i_y++]*1L*i_x)%=MOD;
            } else {
                (ans+=cost_x[i_x++]*1L*i_y)%=MOD;
            }
        }
        while (i_x<n) (ans+=cost_x[i_x++]*1L*m)%=MOD;
        while (i_y<m) (ans+=cost_y[i_y++]*1L*n)%=MOD;
        
        cout << ans << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
