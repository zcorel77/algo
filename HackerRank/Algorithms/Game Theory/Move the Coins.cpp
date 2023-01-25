/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * Staircase Nim
 * 原始树的求解
 * 偶数层的石子不必考虑, 因为对手移动某个偶数层的任意颗石子到下一层,
 * 自己可以将这些石子再移动下一层, 仍然是在偶数层, 不改变胜态.
 * 所以从奇数层移动石头到偶数层就相当与移到地板了,
 * 因此,每个奇数层的石头堆的gr为该堆石头数, 
 * 所以最终解为所有奇数层的石头堆的石头数的异或和.
 * 
 * 然后, 再考虑改变父节点的情况, u连到v,
 * 如果u的层的奇偶性不变的话, 不改变最终结果,
 * 若改变的话, 则取出以u为根的子树内所有节点的层的奇偶性改变
 * 预先算好以每个节点的为根的子树偶数层异或和和奇数层异或和
 */

#include <bits/stdc++.h>

using namespace std;

const int N=5e4+1;

typedef vector<int> vi;
vi G[N];

int n, q, a[N], idx[N], out[N], dep[N], gr[N][2], tot;

void dfs(int u, int d, int p) {
    idx[u]=++tot;
    dep[u]=d;
    gr[u][d]=a[u];

    for (auto &v : G[u]) {
        if (v==p) continue;
        dfs(v, d^1, u);
        gr[u][d]^=gr[v][d];
        gr[u][d^1]^=gr[v][d^1];
    }

    out[u]=tot;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i=1; i<=n; ++i) {
        cin >> a[i];
    }

    int u, v, w, x, y;
    for (int i=1; i<n; ++i) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1, 0, 0);

    cin >> q;
    while (q--) {
        cin >> u >> v;
        if (idx[v]>idx[u] && idx[v]<=out[u]) {
            cout << "INVALID\n";
            continue;
        }

        // u移动后层数的奇偶性不变的话, 不改变最终结果,
        // 如果层数的奇偶性改变的话, 最终结果异或u节点在奇数层的gr,再异或u节点在偶数层的gr
        cout << (gr[1][1]^(dep[u]^dep[v]?0:gr[u][0]^gr[u][1])?"YES":"NO") << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
