/*
 * author: Corel
 *  email: zcorel@hotmail.com
 *
 * 使用splay维护deadline排序(d[N]), 子树时间和(amtm[N])及最大超时(dl[N])
 * 每次插入一个点, 利用子树时间和计算deadline排序时间前缀和(prem[N])及超时(prem[k]-d[k]),
 * 插入点后面的(deadline更大)点, 进行懒更新超时(q[N])
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+1;
const int INF=0x3f3f3f3f;

int n, ans[N];

// splay
struct SPLAY {
    int rt = 0, tot = 0, c[N][2], f[N], d[N], q[N], dl[N]={-INF}, m[N], prem[N], amtm[N];
    int newnode(int dx, int mx) {
        ++tot;
        d[tot] = dx; m[tot] = mx;
        return tot;
    }
    void maintain(int x) {
        amtm[x] = m[x]+amtm[c[x][0]]+amtm[c[x][1]];
        dl[x] = max(prem[x], max(dl[c[x][0]]+q[c[x][0]], dl[c[x][1]]+q[c[x][1]]));
    }
    void pushdown(int x) {
        if (c[x][0]) q[c[x][0]] += q[x];
        if (c[x][1]) q[c[x][1]] += q[x];
        prem[x] += q[x];
        q[x] = 0;
    }
    void rotate(int x) {
        int fx = f[x];
        pushdown(fx); pushdown(x);
        int d = c[fx][0]!=x;
        if (f[fx]) c[f[fx]][c[f[fx]][0]!=fx] = x; f[x] = f[f[x]];
        if (c[x][!d]) f[c[x][!d]] = fx; c[fx][d] = c[x][!d];
        f[fx] = x; c[x][!d] = fx;
        maintain(fx); maintain(x);
    }
    void splay(int x) {
        while (f[x]) {
            if (f[f[x]]) {
                if ((c[f[x]][0]==x)^(c[f[f[x]]][0]==f[x])) rotate(x);
                else rotate(f[x]);
            }
            rotate(x);
        }
        rt=x;
    }
    int build() {
        int x = newnode(-INF, 0), y = newnode(INF, 0);
        rt = x;
        c[x][1] = y;
        f[y] = x;
    }
    void find(int dx) {
        int x = rt;
        if (!x) return;

        while (c[x][dx>d[x]]) x = c[x][dx>d[x]];
        splay(x);
    }
    void insert(int dx, int mx) {
        int x = rt, fa = 0;
        while (x) {
            fa = x;
            x = c[x][dx>d[x]];
        }
        
        x = newnode(dx, mx);
        if (fa) c[fa][d[x]>d[fa]] = x;
        f[x] = fa;

        splay(x);
        prem[x] = m[x]+(c[x][0]?amtm[c[x][0]]:0)-d[x];
        if (c[x][1]) {
            q[c[x][1]] += m[x];
            pushdown(c[x][1]);
            maintain(c[x][1]);
        }
        dl[x] = max(0, max(prem[x], max(dl[c[x][0]], dl[c[x][1]])));
    }
} tr;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int d, m;

    cin >> n;
    for (int i=1; i<=n; ++i) {
        cin >> d >> m;
        tr.insert(d, m);
        ans[i] = tr.dl[tr.rt];
    }

    for (int i=1; i<=n; ++i) {
        cout << ans[i] << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
