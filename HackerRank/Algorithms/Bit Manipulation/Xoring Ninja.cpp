/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 按位算, 一共31位, 计算每位在各种组合中产生的贡献
 * 对于每一位, 有贡献的方式为取奇数个1, 随意个0,
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+1;
const int C=31;
const int MOD=1e9+7;

long ans;
int t, n, a, cnt[C];

long power(long x, long y) {
    if (y==0) return 1L;
    if (y==1) return x;
    
    long pp = power(x, y>>1)%MOD;
    long ret = (pp*pp)%MOD;
    if (y&1) {
        ret = (ret*x)%MOD;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;
    while (t--) {
        ans = 0L;
        fill_n(cnt, C, 0);

        cin >> n;
        for (int i=0; i<n; ++i) {
            cin >> a;
            for (int c=0; c<C; ++c) {
                if (a&(1<<c)) ++cnt[c];
            }
        }

        for (int c=0; c<C; ++c) {
            if (cnt[c]>0) 
                (ans+=power(2, cnt[c]-1)*power(2, n-cnt[c])%MOD*(1<<c))%=MOD;
        }
        cout << ans << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
