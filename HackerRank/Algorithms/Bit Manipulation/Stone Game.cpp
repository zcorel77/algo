/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 可改变的必胜总数-每堆先都拿掉1之后可改变的必胜总数
 * 可改变的必胜总数, 即所有位的异或和为0
 * dp计算可改变的必胜总数, 
 * 所有堆从小到大排序, 最大位k, 存在t个含第k位的堆, 从p[n-t+1]开始含第k位
 * g(i, j) 表示第i堆, 后续堆已抹掉j个第k位, 的总数
 * g(i, j) = g(i-1, j)*(p[i]-2^k+1)+g(i-1, j+1)*2^k  (i>n-t, j>0) (分别为第i堆抹掉第k位, 和不抹掉第k位)
 *           g(i-1, j)*(p[i]-2^k+1)+g(i-1, j+1)      (i>n-t, j=0) (分别为第i堆抹掉第k位, 和第i堆收尾)
 *           g(i-1, j)*(p[i]+1)                      (1<=i<=n-t)   (不含第k位的数)
 *           1                                       (i=0, j>0, t-j为偶数, 也就是剩了偶数个第k位没抹去, 正好相互抵消了)
 *           0                                       (其他)
 * 
 * 如果偶数个数含第k位, 且一个都不抹去, 则所有数抹去第k位, 再计算
 * 
 * r[i]=p[i]^k, i>=n-t
 * p0=(p[0]+1)(p[1]+1)...(p[n-t-1]+1)
 * p1=(r[n-t]+1)(r[n-t+1]+1)...(r[n-1]+1)
 */

#include <bits/stdc++.h>

using namespace std;

const int N=101;
const int MOD=1e9+7;

inline int hibit(int x) {
    if (!x) return 0;
    int y = 1;
    while (x>>=1) {
        y<<=1;
    }
    return y;
}

long power(long x, long y) {
    if (y==0) return 1L;
    if (y==1) return x;
    
    long pp = power(x, y>>1)%MOD;
    long ret = (pp*pp)%MOD;
    if (y&1) {
        (ret*=x)%=MOD;
    }
    return ret;
}

int n, p[N], q[N];
long solve() {
    int ma=0, k=0, t=0, m=0;
    for (int i=0; i<n; ++i) ma=max(ma, p[i]);

    k=hibit(ma);
    if (!k) return 1L;

    long p0=1L, p1=1L, ans[2][2]={{1L}};
    for (int i=0; i<n; ++i) {
        if (p[i]&k) {
            ans[m^1][t]=(ans[m][t]*((p[i]^k)+1)+ans[m][t^1]*k)%MOD;
            t^=1;
            ans[m^1][t]=(ans[m][t]*((p[i]^k)+1)+ans[m][t^1]*k)%MOD;
            m^=1;
            (p1*=(p[i]^k)+1)%=MOD;
        } else {
            (p0*=p[i]+1)%=MOD;
        }
    }
    // 去掉一个k位都没抹去的情况
    (ans[m][0]+=MOD-p1)%=MOD;
    // 除去最后一个k, 乘上p0
    ((ans[m][t]*=power(k, MOD-2))%=MOD)*=p0;

    // 一个k位都没抹去的话, 所有数抹去k位, 再解一遍
    if (t^1) {
        for (int i=0; i<n; ++i) if (p[i]&k) p[i]^=k;
        ans[m][t]+=solve();
    }
    return ans[m][t]%MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i=0; i<n; ++i) {
        cin >> p[i]; q[i]=p[i]-1;
    }

    long ans=solve();
    swap(p, q);
    (ans+=MOD-solve())%=MOD;

    cout << ans << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
