/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 原始字符串拆成两段(所有拆法), 计算两段间的公共子序列
 * dp[i][j]表示a(i)与b(j)的公共子序列个数, 
 * 即, a(j-1)与b(j)的公共子序列个数加上a(i)与b(j-1)的公共子序列个数,
 *   此时, a(i-1)与b(j-1)的公共子序列个数计算了两次, 因此需减去一个a(i-1)与b(j-1)的公共子序列个数,
 *   又, 若a[i]==b[j], 则所有a(i-1)与b(j-1)的公共子序列追加a[i](也就是b[j])又构成新的公共子序列,
 *   在此情况下, 需要加回一个a(i-1)与b(j-1)的公共子序列个数
 * 因此, 推进公式如下
 * dp[i][j]=dp[i-1][j]+dp[i][j-1]-((a[i]==a[j])?0:dp[i-1][j-1])
 */

#include <bits/stdc++.h>

using namespace std;

const int N=201;
const int MOD=1e9+7;

int dp[N][N];

int solve(const string &a, const string &b) {
    int n=a.length(), m=b.length();

    memset(dp, 0, sizeof(dp));
    fill_n(dp[0], m+1, 1);

    for (int i=1; i<=n; ++i) {
        dp[i][1] = (a[0]==b[0]);
        for (int j=2; j<=m; ++j) {
            dp[i][j] = dp[i][j-1]+dp[i-1][j]-(a[i-1]==b[j-1]?0:dp[i-1][j-1]);
            dp[i][j] %= MOD;
        }
    }
    return dp[n][m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t, n;
    string s;

    cin >> t;
    while (t--) {
        cin >> s;

        int ans = 0;
        for (int i=1; i<s.length(); ++i) {
            (ans+=solve(s.substr(i), s.substr(0, i)))%=MOD;
        }
        cout << ans << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
