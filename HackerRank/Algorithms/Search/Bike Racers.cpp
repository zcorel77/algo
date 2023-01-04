/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 二分时间, 也就是距离, 查找二分图最大匹配数满足k个
 * 二分图最大匹配数, 使用匈牙利算法
 */

#include <bits/stdc++.h>

using namespace std;

const int N=251;
const int M=251;
const int X=1e7;
const long INF=0x3f3f3f3f3f3f3f3f;

int n, m, k;
long px[N], py[N], bx[M], by[M], dist[N][M];

// Hungary Algorithm
int link[M], used[M];
bool dfs(int u, long d) {
    for (int v=1; v<=m; ++v) {
        if (dist[u][v]<=d && !used[v]) {
            used[v] = 1;
            if (!link[v] || dfs(link[v], d)) {
                link[v] = u;
                return true;
            }
        }
    }
    return false;
}

int hungary(long d) {
    int ans = 0;
    fill_n(link+1, m, 0);
    for (int u=1; u<=n; ++u) {
        fill_n(used+1, m, 0);
        if (dfs(u, d)) ans++;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> k;
    for (int i=1; i<=n; ++i) {
        cin >> px[i] >> py[i];
    }
    for (int i=1; i<=m; ++i) {
        cin >> bx[i] >> by[i];
    }

    long l = INF, r = 0L, mid;
    for (int u=1; u<=n; ++u) {
        for (int v=1; v<=m; ++v) {
            dist[u][v] = (px[u]-bx[v])*(px[u]-bx[v])+(py[u]-by[v])*(py[u]-by[v]);
            l = min(l, dist[u][v]);
            r = max(r, dist[u][v]);
        }
    }

    long ans = 0L;
    while (l<=r) {
        mid = (l+r)/2;
        if (hungary(mid)>=k) { r = mid-1; ans = mid; }
        else { l = mid+1; }
    }
    cout << ans << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
