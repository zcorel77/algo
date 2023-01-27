/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 树上跑出dfs序, 然后在dfs序上dp,
 * dp[i][j], i, dfs序号, k 剪枝次数,
 * 每个节点, 剪与不剪两个状态推进,
 * 不剪的话, 前节点dp状态加上当前节点值,
 * 剪的话, 前节点dp状态更新到当前节点子树结束的位置
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+1;
const int K=201;
const long INF=0x3f3f3f3f3f3f3f3f;

typedef vector<int> vi;
vi G[N];

int n, k, w[N], idx[N], rev[N], out[N], tot=0;
long dp[N][K];

void dfs(int u, int p) {
    idx[u]=++tot;
    rev[idx[u]]=u;
    for (auto &v : G[u]) {
        if (v==p) continue;
        dfs(v, u);
    }
    out[u]=tot;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    for (int i=1; i<=n; ++i) {
        cin >> w[i];
    }

    int u, v;
    for (int i=1; i<n; ++i) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1, 0);

    fill_n((long*)dp, N*K, -INF);

    dp[0][0]=0;
    for (int i=1; i<=n; ++i) {
        for (int j=0; j<=k; ++j) {
            dp[i][j]=max(dp[i][j], dp[i-1][j]+w[rev[i]]);
            if (j<k) {
                dp[out[rev[i]]][j+1]=max(dp[out[rev[i]]][j+1], dp[i-1][j]);
            }
        }
    }

    for (int j=0; j<k; ++j) {
        dp[n][k]=max(dp[n][k], dp[n][j]);
    }

    cout << dp[n][k] << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
