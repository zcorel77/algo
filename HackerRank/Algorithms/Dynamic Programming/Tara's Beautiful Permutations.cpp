/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * dp[i][j][k],
 *   i出现两次的数的个数,
 *   j出现一次的数的个数,
 *   k末尾数是从出现一次(k==1)或两次(k==0)的数中选的
 * 
 * 末尾数k==1的情况, 需判断当前的k'
 *   如果k'==1, dp[x-1][y][k]*x
 *   如果k'==0, dp[x-1][y][k]*(x-1)
 * 末尾数k==0的情况,
 *   dp[x+1][y-1][k]*y
 */

#include <bits/stdc++.h>

using namespace std;

const int N=2001;
const int MOD=1e9+7;

int dp[N][N][2], a[N];

int solve(int x, int y, int z) {
    if (x<0 || y<0) return 0;
    if (dp[x][y][z]!=-1) return dp[x][y][z];

    long ret=solve(x-1, y, 1)*1L*(z?x:(x-1))
            +solve(x+1, y-1, 0)*1L*y;
    return dp[x][y][z]=ret%MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    memset(dp, -1, sizeof(dp));
    dp[0][0][0]=0, dp[0][0][1]=1;

    int t, n, m;

    cin >> t;
    while (t--) {
        cin >> n;
        for (int i=1; i<=n; ++i) {
            cin >> a[i];
        }

        sort(a, a+n+1);

        m=0;
        for (int i=1; i<=n; ++i) {
            if (a[i]==a[i-1]) ++m;
        }
        n-=m<<1;

        cout << solve(n, m, 1) << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
