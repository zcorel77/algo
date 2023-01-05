/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 二分第k个数的数值, 对于数值m, 建立新数组, 原值>m为1, 否则为0
 * 对新数组做q次排序, 结果第k个数为1, 则表示第k个数的数值>m
 */

#include <bits/stdc++.h>

using namespace std;

const int N=7.5e5+1;
const int Q=7.5e5+1;
const int INF=1e9;

int n, q, k, a[N], ql[Q], qr[Q];

// Segment tree
#define lo (o<<1)
#define ro lo+1
#define ls lo, l, (l+r)/2
#define rs ro, (l+r)/2+1, r
struct SegTree{
    int p[N<<2], q[N<<2];
    void build(int x, int o=1, int l=1, int r=n) {
        if (l==r) {
            q[o]=(a[l]>=x);
            p[o]=q[o];
        } else {
            build(x, ls); build(x, rs);
            q[o]=-1;
            p[o]=p[lo]+p[ro];
        }
    }
    void maintain(int o, int l, int r) {
        if (q[o]!=-1) {
            p[o]=(r-l+1)*q[o];
        } else {
            p[o]=p[lo]+p[ro];
        }
    }
    void pushdown(int o, int l, int r) {
        if (q[o]!=-1) {
            q[lo]=q[o]; q[ro]=q[o];
            q[o]=-1;
            maintain(ls); maintain(rs);
        }
    }
    void update(int x, int y, int v, int o=1, int l=1, int r=n) {
        if (x>r || l>y) return;
        if (x<=l && r<=y) {
            q[o]=v;
        } else {
            pushdown(o, l, r);
            update(x, y, v, ls); update(x, y, v, rs);
        }
        maintain(o, l, r);
    }
    int query(int x, int y, int o=1, int l=1, int r=n) {
        if (x>r || l>y) return 0;
        if (x<=l && r<=y) return p[o];
        pushdown(o, l, r);
        return query(x, y, ls)+query(x, y, rs);
    }
} st;

bool check(int x) {
    st.build(x);
    for (int i=1; i<=q; ++i) {
        int amt=st.query(ql[i], qr[i]);
        if (amt<qr[i]-ql[i]+1) st.update(ql[i], qr[i]-amt, 0);
        if (amt>0) st.update(qr[i]-amt+1, qr[i], 1);
    }
    return st.query(k, k);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q >> k;
    ++k;
    for (int i=1; i<=n; ++i) cin >> a[i];
    for (int i=1; i<=q; ++i) {
        cin >> ql[i] >> qr[i];
        ++ql[i]; ++qr[i];
    }

    int l=-INF, r=INF, mid, ans=0;
    while (l<=r) {
        mid=(l+r)/2;
        if (check(mid)) { l=mid+1; ans=mid; }
        else { r=mid-1; }
    }
    
    cout << ans << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
