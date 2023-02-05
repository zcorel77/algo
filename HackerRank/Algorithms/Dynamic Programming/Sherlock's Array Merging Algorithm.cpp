/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 按列从后往前构造
 * 首先, 每列的数据在原始数据中是连续的递增序列,
 * 每列的元素个数是个递减序列, cnt[0]>=cnt[1]>=...
 * dp[i][j]表示[0-i]的原始序列中, 最小的列有j个数, 推进为
 * dp[i][j]=sum(dp[i-j][k]*A(k, j)), k>=j, A为排列数
 * 也就是说, 某列有j个数, 则前一列有k个数, k个数选j个数放在这列前面, 剩下的随意
 * 最后输出, 就是原始列最后一组递增序列可能产生的最后一列的可能性
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1201;
const int MOD=1e9+7;

int n, a[N], b[N], F[N], G[N], dp[N][N];

long power(long x, long y, long m) {
    if (y==1) {
        return x;
    }
    
    long pp = power(x, y/2, m)%m;
    long ret = (pp*pp)%m;
    if (y%2==1) {
        ret = (ret*x)%m;
    }
    return ret;
}

void factorial() {
    F[0]=1, G[0]=1;
    for (int k=1; k<N; ++k) {
        F[k] = (F[k-1]*1L*k)%MOD;
    }
    G[N-1] = power(F[N-1], MOD-2, MOD);
    for (int k=N-1; k>0; --k) {
        G[k-1] = (G[k]*1L*k)%MOD;
    }
}


int A(int a, int b) {
    return (F[a]*1L*G[a-b])%MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    factorial();

    cin >> n;
    for (int i=0; i<n; ++i) {
        cin >> a[i];
    }

    b[0]=1;
    for (int i=1; i<n; ++i) {
        if (a[i]>a[i-1]) b[i]=b[i-1]+1;
        else b[i]=1;
    }

    for (int i=1; i<=n; ++i) {
        if (i==b[i-1]) dp[i][i]=1;
        for (int j=1; j<=b[i-1]; ++j) {
            for (int k=j; k<=i-j; ++k) {
                dp[i][j] = (dp[i][j]+dp[i-j][k]*1L*A(k, j))%MOD;
            }
        }
    }

    long ans = 0L;
    for (int i=1; i<=b[n-1]; ++i) ans+=dp[n][i];
    cout << (ans%MOD)<< "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
