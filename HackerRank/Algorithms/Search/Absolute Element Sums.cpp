/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 原始数组A排序
 * 预先求出原始数组的递进和B
 * 累计变化值cc, 计算三个区间分界点的下标k0, k1
 * 三个区间(cc==0时, 两个区间)
 *   cc>0, (-INF, -cc), [-cc, 0), [0, INF)
 *   cc<0, (-INF, 0), [0, -cc], [-cc, INF)
 *   cc==0, (-INF, 0), [0, INF)
 * 根据k0, k1与递进和B, 计算出当前数组的绝对值和
 * 注意正负区间求和
 */

#include <bits/stdc++.h>

using namespace std;

const int N=5e5+1;
const int Q=5e5+1;

int n, q;
long a[N], b[N], c[Q], ans[Q];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i=1; i<=n; ++i) cin >> a[i];
    cin >> q;
    for (int i=1; i<=q; ++i) cin >> c[i];

    sort(a+1, a+n+1);
    for (int i=1; i<=n; ++i) b[i]=b[i-1]+a[i];

    int k0=lower_bound(a+1, a+n+1, 0)-a-1, k1;
    long ans0=b[n]-b[k0]*2, cc;
    for (int i=1; i<=q; ++i) {
        cc+=c[i];
        if (cc==0) {
            ans[i]=ans0;
        } else {
            k1=lower_bound(a+1, a+n+1, -cc)-a-1;
            ans[i]=ans0+cc*n+(b[k0]-b[k1])*2-cc*k1*2;
        }
    }

    for (int i=1; i<=q; ++i) {
        cout << ans[i] << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
