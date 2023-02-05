/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * Persistency Trie
 * 用字典树存储整数的二进制描述, 寻找异或最大值时, 从高位到底位, 依次查看字典树中是否存在与参照数相同的位
 * 由于是区间查询, 对询问按r编组, 当按续将数组插入字典树执行到r的时候, 求解所有右边界为r的问询
 * 另, 利用持久化结构, 存储插入的历史记录
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+1;
const int Q=5e4;

struct Ask {
    int l, i;
    long a;

    Ask(int l, int i, long a):l(l), i(i), a(a) {}
};
vector<Ask> ask[N];

struct Trie {
    struct P {
        int ch[2], cnt;
    } p[N*64];
    int rt[N], tot=0;
    void clear() {
        memset(p, 0, sizeof(p));
        memset(rt, 0, sizeof(rt));
        tot=0;
    }
    void add(long x, int i) {
        rt[i]=++tot;

        int q=rt[i-1], r=rt[i];
        p[r].cnt = p[q].cnt+1;
        for (long h=1L<<62; h; h>>=1) {
            long xx=!!(x&h);
            p[r].ch[!xx] = p[q].ch[!xx];
            p[r].ch[xx] = ++tot;

            r=p[r].ch[xx]; q=p[q].ch[xx];
            p[r].cnt = p[q].cnt+1;
        }
    }
    long query(long x, int q, int r) {
        long ans=0L;
        q=rt[q], r=rt[r];
        for (long h=1L<<62; h; h>>=1) {
            long xx=!!(x&h);
            if (p[p[r].ch[!xx]].cnt>p[p[q].ch[!xx]].cnt) {
                ans^=h;
                r=p[r].ch[!xx]; q=p[q].ch[!xx];
            } else {
                r=p[r].ch[xx]; q=p[q].ch[xx];
            }
        }
        return ans;
    }
} trie;

int t, n, q;
long x[N], ans[Q];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int l, r;
    long a;

    cin >> t;
    while (t--) {
        trie.clear();
        for (int i=0; i<N; ++i) ask[i].clear();

        cin >> n >> q;
        for (int i=1; i<=n; ++i) {
            cin >> x[i];
        }

        for (int i=0; i<q; ++i) {
            cin >> a >> l >> r;
            if (l>r) swap(l, r);
            ask[r].emplace_back(l, i, a);
        }

        for (int i=1; i<=n; ++i) {
            trie.add(x[i], i);

            for (int j=0; j<ask[i].size(); ++j) {
                ans[ask[i][j].i] = trie.query(ask[i][j].a, ask[i][j].l-1, i); 
            }
        }

        for (int i=0; i<q; ++i) {
            cout << ans[i] << "\n";
        }
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
