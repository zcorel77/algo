/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 数组a[N]添加俩个哨兵-INF, INF<<1, 对其排序,
 * 依次数组区间[a[i-1],a[i]]与区间[p,q]交集[l,r]
 * 求l, r, (a[i]+a[i-1])/2, (a[i]+a[i-1]+1)/2四个点与a[i-1], a[i]的距离
 * 其中后两个点需满足在交集[l,r]内
 */

#include <bits/stdc++.h>

using namespace std;

const int N=101;
const int INF=1e9+10;

int n, p, q, a[N];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i=0; i<n; ++i) cin >> a[i];
    cin >> p >> q;

    a[n++]=-INF; a[n++]=INF<<1;
    sort(a, a+n);

    int ans=0, mx=0, cur, l, r, mid;
    for (int i=1; i<n; ++i) {
        l=max(a[i-1], p);
        r=min(a[i], q);

        cur=min(l-a[i-1], a[i]-l);
        if (mx<cur) { mx=cur; ans=l; }

        cur=min(r-a[i-1], a[i]-r);
        if (mx<cur) { mx=cur; ans=r; }

        mid=(a[i-1]+a[i])/2;
        if (mid>=l && mid<=r) {
            cur=min(mid-a[i-1], a[i]-mid);
            if (mx<cur) { mx=cur; ans=mid; }
        }

        mid=(a[i-1]+a[i]+1)/2;
        if (mid>=l && mid<=r) {
            cur=min(mid-a[i-1], a[i]-mid);
            if (mx<cur) { mx=cur; ans=mid; }
        }
    }

    cout << ans << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
