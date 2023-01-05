/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 单点距离排序
 * 二分最大点对距离
 * 对于距离k, 单点距离大于k的点集查询是否存在点对距离大于k
 * 假定ai<bi,
 * 对于某个单点距离大于k的点i, 考虑距离大于k的点集中, 所有aj+k小于ai的点j
 * 利用segment tree, 把aj赋值到位置bj, 查询满足条件的三个bj区间中的最大aj, 判别aj与bi距离是否大于k
 * 满足条件的bj区间, [max(0, bi-c+k), ai-k], [ai+k, bi-k], [bi+k, min(c, ai+c-k)]
 * 
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+1;
const int C=1e6+1;

int n, c, p[N][2], sp[N];

// Segment tree
#define lo (o<<1)
#define ro (lo+1)
#define ls lo, l, (l+r)/2
#define rs ro, (l+r)/2+1, r
struct SegTree {
    int p[C<<2];
    void clear() {
        fill_n(p, (c+1)<<2, -1);
    }
    void maintain(int o, int l, int r) {
        p[o]=max(p[lo], p[ro]);
    }
    void update(int x, int v, int o=1, int l=0, int r=c) {
        if (x>r || l>x) return;
        if (l==r) {
            p[o]=v;
        } else {
            update(x, v, ls); update(x, v, rs);
            maintain(o, l, r);
        }
    }
    int query(int x, int y, int o=1, int l=0, int r=c) {
        if (x>y) return -1;
        if (x>r || l>y) return -1;
        if (x<=l && r<=y) return p[o];
        return max(query(x, y, ls), query(x, y, rs));
    }
} st;

bool check(int k) {
    st.clear();

    int mx;
    for (int i=0, j=0; i<n; ++i) {
        for (; j<i; ++j) {
            if (p[sp[j]][1]-p[sp[j]][0]<k || p[sp[j]][0]+c-p[sp[j]][1]<k) continue;
            if (p[sp[j]][0]+k>p[sp[i]][0]) break;
            st.update(p[sp[j]][1], p[sp[j]][0]);
        }
        if (p[sp[i]][1]-p[sp[i]][0]<k || p[sp[i]][0]+c-p[sp[i]][1]<k) continue;
        mx=st.query(max(0, p[sp[i]][1]-c+k), p[sp[i]][0]-k);
        mx=max(mx, st.query(p[sp[i]][0]+k, p[sp[i]][1]-k));
        mx=max(mx, st.query(p[sp[i]][1]+k, min(c, p[sp[i]][0]+c-k)));
        if (mx<0) continue;
        if (mx+c >= p[sp[i]][1]+k) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> c;
    for (int i=0; i<n; ++i) {
        cin >> p[i][0] >> p[i][1];
        if (p[i][0]>p[i][1]) swap(p[i][0], p[i][1]);
    }

    iota(sp, sp+n, 0);
    sort(sp, sp+n, [](const int &x, const int &y)->bool {
        return p[x][0]<p[y][0];
    });
    
    int l=0, r=c/2, mid, ans=0;
    while (l<=r) {
        mid=(l+r)/2;
        if (check(mid)) { l=mid+1; ans=mid; }
        else { r=mid-1; }
    }

    cout << ans << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
