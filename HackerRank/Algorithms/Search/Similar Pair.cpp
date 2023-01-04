/*
 * author: Corel
 *  email: zcorel@hotmail.com
 *
 * dfs搜索树, 启发式和并子树节点集合
 * splay维护子树节点集合, 子树u节点集合中查询[u-k, u+k]节点个数
 * 累加其个数即为答案
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+1;

typedef vector<int> vi;
vi G[N];

int n, k, pa[N];
long ans = 0L;

struct Splay {
    int rt[N], pa[N], ch[N][2], cnt[N];
    void init(int n) {
        iota(rt, rt+n+1, 0);
        fill_n(cnt+1, n, 1);
    }
    void maintain(int u) {
        cnt[u]=cnt[ch[u][0]]+cnt[ch[u][1]]+1;
    }
    void rotate(int u) {
        int p = pa[u];
        int d = ch[p][0]!=u;
        if (pa[p]) ch[pa[p]][ch[pa[p]][0]!=p] = u; pa[u] = pa[pa[u]];
        if (ch[u][!d]) pa[ch[u][!d]] = p; ch[p][d] = ch[u][!d];
        pa[p] = u; ch[u][!d] = p;
        maintain(p); maintain(u);
    }
    void splay(int &r, int u) {
        while (pa[u]) {
            int p = pa[u];
            if (pa[p]) {
                int pp = pa[p];
                if ((ch[p][0]==u)==(ch[pp][0]==p)) rotate(p);
                else rotate(u);
            }
            rotate(u);
        }
        r = u;
    }
    void insert(int &u, int v) {
        int x = u, p = 0;
        while (x) {
            p = x; x = ch[x][v>x];
        }
        
        if (p) ch[p][v>p] = v;
        pa[v] = p;

        splay(u, v);
    }
    void merge(int &u, int v) {
        if (ch[v][0]) merge(u, ch[v][0]);
        if (ch[v][1]) merge(u, ch[v][1]);
        ch[v][0] = ch[v][1] = 0; cnt[v] = 1;
        insert(u, v);
    }
    int find(int u, int v) {
        int x = u, p = 0, pr = 0;
        while (x) {
            p = x; x = ch[x][v>=x];
        }
        if (v>=p) return p;
        while (pa[p] && ch[pa[p]][0]==p) p=pa[p];
        return pa[p];
    }
    int query(int &u, int x) {
        int v = find(u, x);
        if (!v) return 0;

        splay(u, v);
        return cnt[ch[u][0]]+1;
    }
    int query(int &u, int x, int y) {
        return query(u, y)-query(u, x-1);
    }
} tr;

int findpa(int x) {
    return (pa[x]==x)?x:(pa[x]=findpa(pa[x]));
}

void dfs(int u) {
    for (auto &v : G[u]) {
        dfs(v);

        // merge node
        if (tr.cnt[tr.rt[u]]<tr.cnt[tr.rt[v]]) swap(tr.rt[u], tr.rt[v]);
        tr.merge(tr.rt[u], tr.rt[v]);
    }

    ans += tr.query(tr.rt[u], u-k, u+k)-1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    iota(pa, pa+n+1, 0);

    int u, v;
    for (int i=1; i<n; ++i) {
        cin >> u >> v;
        G[u].push_back(v);
        pa[v]=u;
    }

    int rt = findpa(1);
    tr.init(n);
    dfs(rt);

    cout << ans << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
