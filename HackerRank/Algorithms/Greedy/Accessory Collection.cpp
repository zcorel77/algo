/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 找到锚点K=a[D-1], 大等于K的元素个数总和为N-1
 */

#include <bits/stdc++.h>

using namespace std;

long t, l, a, n, d;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;
    while (t--) {
        cin >> l >> a >> n >> d;
        if (d>a) {
            cout << "SAD\n";
            continue;
        }

        if (d==1) {
            cout << a*l << "\n";
            continue;
        }

        long ans=0L, r, m, k;
        for (int i=1; i<=l; ++i) {
            // 最大d-1种都配i个, n-1个剩余r
            r=n-1-i*(d-1);
            if (r<0) break;
            // 刨去r, 尽可能给所有种类分i个, 有m种没分到
            m=max(0L, a-(l-r)/i);
            // 总共分掉k
            k=(a-m)*i+r;
            // 所有种类都分了,但没分完l,无解
            if (k<l && m==0) continue;
            // r个元素取值a, 其他l-r个元素取值m, 然后所有种类都有i个
            // 相当与求面积
            //                                   i  |  r
            //                                 ------------
            //                               i |          |
            //                             -----          |
            //                           i |              |
            //                         -----              |
            //                      i |                   |
            //                    -----                   | a
            //    i | ... | i | i |                       |
            //  -------------------                       |
            //  |                                         |
            // m|                                         |
            //  |                                         |
            //  -------------------------------------------
            //              l
            ans=max(ans, (a-m)*(a-m+1)/2*i-(a-m)*(l-r)+a*l);
        }
        if (ans)
            cout << ans << "\n";
        else
            cout << "SAD\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
