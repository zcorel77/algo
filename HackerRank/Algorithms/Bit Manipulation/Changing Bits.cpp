/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 线段树存储a[i]+b[i]~[0,2]
 * 处理carry
 * 查询最大的j, ma[j]=2, j<i
 * 查询区间[j,i]的mininum是否为1,是的话,j的carry传导到i
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+2;
const int INF=0x3f3f3f3f;

int n, q, a[N], b[N];

// segment tree
#define lo (o<<1)
#define ro (lo+1)
#define ls lo, l, (l+r)/2
#define rs ro, (l+r)/2+1, r
struct SegTree {
    int mi[N<<2], ma[N<<2];
    void build(int o=1, int l=1, int r=n) {
        if (l==r) {
            mi[o]=ma[o]=a[l]+b[l];
        } else {
            build(ls); build(rs);
            mi[o]=min(mi[lo], mi[ro]);
            ma[o]=max(ma[lo], ma[ro]);
        }
    }
    void update(int x, int o=1, int l=1, int r=n) {
        if (x>r || l>x) return;
        if (l==r) {
            mi[o]=ma[o]=a[l]+b[l];
        } else {
            update(x, ls); update(x, rs);
            mi[o]=min(mi[lo], mi[ro]);
            ma[o]=max(ma[lo], ma[ro]);
        }
    }
    int query_min(int x, int y, int o=1, int l=1, int r=n) {
        if (x>r || l>y) return INF;
        if (x<=l && r<=y) return mi[o];
        return min(query_min(x, y, ls), query_min(x, y, rs));
    }
    int find_max_pos(int x, int y, int v, int o=1, int l=1, int r=n) {
        if (x>r || l>y || ma[o]<v) return 0;
        if (l==r) return l;
        int ret = find_max_pos(x, y, v, rs);
        return ret?ret:find_max_pos(x, y, v, ls);
    }
} tr;

int carry(int y) {
    int x=tr.find_max_pos(1, y-1, 2);
    if (!x) return 0;
    if (x==y-1) return 1;
    return tr.query_min(x+1, y-1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q;

    string s;

    cin >> s;
    for (int i=0; i<n; ++i) {
        a[n-i]=s[i]-'0';
    }

    cin >> s;
    for (int i=0; i<n; ++i) {
        b[n-i]=s[i]-'0';
    }

    tr.build();

    int x, y, z;
    while (q--) {
        cin >> s;
        if (s.compare("set_a")==0) {
            cin >> x >> y;
            ++x;
            a[x]=y;
            tr.update(x);
        } else if (s.compare("set_b")==0) {
            cin >> x >> y;
            ++x;
            b[x]=y;
            tr.update(x);
        } else {
            cin >> x;
            ++x;

            cout << ((((x<n+1)?(a[x]+b[x]):0)+carry(x))&1);
        }
    }
    cout << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
