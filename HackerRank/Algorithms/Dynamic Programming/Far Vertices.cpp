/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 利用Floyd算法解出所有点对距离
 * 对于k为偶数, 遍历所有节点, 计数所有到该节点距离小等于k/2的节点数,
 *   最后取最大值, 然后算需要抹去多少点
 * 对于k为奇数, 便利所有边, 计数所有到该边任意端节点距离小等于k/2的节点数,
 *   最后取最大值, 然后算需要抹去多少点
 */

#include <bits/stdc++.h>

using namespace std;

const int N=101;

int n, k, m, d[N][N], e[N][2];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    memset(d, 0x3f, sizeof(d));

    cin >> n >> k;
    for (int i=1; i<=n; ++i) d[i][i]=0;
    for (int i=1; i<n; ++i) {
        int &u=e[i][0], &v=e[i][1];
        cin >> u >> v;
        d[u][v]=d[v][u]=1;
    }

    // Floyd
    for (int k=1; k<=n; ++k)
        for (int i=1; i<=n; ++i)
            for (int j=1; j<=n; ++j)
                d[i][j] = min(d[i][j], d[i][k]+d[k][j]);

    int ans=n;
    if (k&1) {
        for (int i=1; i<n; ++i) {
            const int &u=e[i][0], &v=e[i][1];

            m=0;
            for (int j=1; j<=n; ++j)
                if (d[u][j]<=k/2 || d[v][j]<=k/2) ++m;
            ans=min(ans, n-m);
        }
    } else {
        for (int i=1; i<=n; ++i) {
            m=0;
            for (int j=1; j<=n; ++j)
                if (d[i][j]<=k/2) ++m;
            ans=min(ans, n-m);
        }
    }
    cout << ans << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
