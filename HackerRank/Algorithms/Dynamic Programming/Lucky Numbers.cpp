/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * dp只缓存完备情况, 非完备情况暴力解算
 * 完备情况指, 低位数字都包含[0-9]的情况
 */

#include <bits/stdc++.h>

using namespace std;

const int K=18;
const int N=18*9+1;
const int M=18*9*9+1;

int d[K];
long dp[K][N][M];
bool prime[M];

// b, 第b个数字, s, 数字和, ss, 数字平方和, flag, 是否完整
long go(int b, int s, int ss, bool flag) {
    if (b==K) return prime[s]&&prime[ss];

    long &cache = dp[b][s][ss];
    if (flag && cache>=0) return cache;

    long ret=0L;
    for (int i=0; i<=(flag?9:d[b]); ++i) {
        ret+=go(b+1, s+i, ss+i*i, flag||i<d[b]);
    }

    if (flag) cache=ret;
    return ret;
}

long solve(long x) {
    if (x<=1) return 0;
    for (int i=K-1; i>=0; --i) {
        d[i]=x%10; x/=10;
    }
    return go(0, 0, 0, false);
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // seiving
    fill_n(prime+2, M-2, true);
    for (int i=2; i<M; ++i) {
        if (prime[i]) {
            for (int j=i<<1; j<M; j+=i) prime[j]=false;
        }
    }

    fill_n((long*)dp, K*N*M, -1L);

    int t;
    long a, b;

    cin >> t;
    while (t--) {
        cin >> a >> b;
        cout << solve(b)-solve(a-1) << endl;
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
