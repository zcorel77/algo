/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 输入数组排序, 抽取连续数段
 * 对连续数段统计数频
 * 根据数频贪婪的组织连续序列
 *   利用segment tree维护序列长度,
 *     如果当前数频小等于前数数频, 则前数数频区段尾部部分都+1,
 *     否则前数数频区段全+1, 再追加一部分区段赋值1
 *   最后查询segment tree最小值
 * 如果某段连续数段得到的最短序列长度为1, 则答案为1, 退出
 * 注意控制fill_n的调用次数, 多了容易TLE
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e6+1;
const int INF=0x3f3f3f3f;

int t, n, x[N], cnt[N];

// segment tree
#define lo (o<<1)
#define ro (lo+1)
#define ls lo, l, (l+r)/2
#define rs ro, (l+r)/2+1, r
struct SegTree {
    int p[N<<2], q[N<<2];
    void init() {
        fill_n(p, n<<2, 0);
        fill_n(q, n<<2, 0);
    }
    void maintain(int o, int l, int r) {
        if (l==r) {
            p[o]=q[o];
        } else {
            p[o]=min(p[lo], p[ro])+q[o];
        }
    }
    void pushdown(int o, int l, int r) {
        q[lo]+=q[o]; q[ro]+=q[o];
        q[o]=0;
        maintain(ls); maintain(rs);
    }
    void update(int x, int y, int v, int o=1, int l=1, int r=n) {
        if (x>y) return;
        if (x>r || l>y) return;
        if (x<=l && r<=y) {
            q[o]+=v;
        } else {
            pushdown(o, l, r);
            update(x, y, v, ls); update(x, y, v, rs);
        }
        maintain(o, l, r);
    }
    int query(int x, int y, int o=1, int l=1, int r=n) {
        if (x>r || l>y) return INF;
        if (x<=l && r<=y) return p[o];
        pushdown(o, l, r);
        return min(query(x, y, ls), query(x, y, rs));
    }
} tr;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;
    while (t--) {
        cin >> n;
        if (n==0) {
            cout << "0\n";
            continue;
        }

        for (int i=0; i<n; ++i) {
            cin >> x[i];
        }

        sort(x, x+n);
        x[n]=INF;

        tr.init();
        fill_n(cnt, n, 0);

        int ans=INF, st, ed;
        for (int i=0, j=1; j<=n; ++j) {
            if (x[j]<=x[j-1]+1) {
                ++cnt[i+x[j]-x[i]];
                continue;
            }
            ++cnt[i];

            st=ed=i+1;
            for (int k=i; k<=i+x[j-1]-x[i]; ++k) {
                if (cnt[k]<=ed-st+1) {
                    st=ed-cnt[k]+1;
                } else {
                    ed=st+cnt[k]-1;
                }
                tr.update(st, ed, 1);
            }

            ans=min(ans, tr.query(i+1, ed));
            if (ans==1) break;
            i=j;
        }

        cout << ans << "\n";
    }
    
    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
