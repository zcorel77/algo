/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * dp[l][r][fl][fr]
 * [l,r]间的回文串数, fl是否含l所在字符串的字符, fr是否含r所在字符串中的字符
 * 推进按字符串长度1到长度n
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1002;
const int MOD=1e9+7;

char a[N];
int g[N], dp[N][N][2][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t, n, m, l;
    string s;

    cin >> t;
    while (t--) {
        n=1;

        cin >> m;
        for (int i=0; i<m; ++i) {
            cin >> s;
            l=s.length();

            memcpy(a+n, s.c_str(), l);
            fill_n(g+n, l, i);
            n+=l;
        }

        memset(dp, 0, sizeof(dp));
        for (int i=0; i<=n; ++i) {
            for (int j=0; j<i; ++j) {
                dp[i][j][0][0]=1;
            }
        }

        for (int i=0; i<n-1; ++i) {
            for (int l=1, r; l<n-i; ++l) {
                r=l+i;
                if (g[l]==g[r]) {
                    dp[l][r][0][0]=1;
                    dp[l][r][1][1]=(dp[l+1][r][1][1]+dp[l][r-1][1][1])%MOD;
                    if (a[l]==a[r]) {
                        (dp[l][r][1][1]+=dp[l+1][r-1][0][0])%=MOD;
                    } else {
                        (dp[l][r][1][1]+=MOD-dp[l+1][r-1][1][1])%=MOD;
                    }
                } else if (g[l]!=g[l+1] && g[r]!=g[r-1]) {
                    dp[l][r][0][0]=(l+1==r?1:dp[l+1][r-1][1][1]);
                    dp[l][r][1][0]=dp[l][r-1][1][1];
                    dp[l][r][0][1]=dp[l+1][r][1][1];
                    dp[l][r][1][1]=(a[l]==a[r]?dp[l][r][0][0]:0);
                } else if (g[l]!=g[l+1]) {
                    dp[l][r][0][0]=dp[l][r-1][0][0];
                    dp[l][r][1][0]=dp[l][r-1][1][0];
                    dp[l][r][0][1]=dp[l+1][r][1][1];
                    dp[l][r][1][1]=dp[l][r-1][1][1];
                    if (a[l]==a[r]) {
                        (dp[l][r][1][1]+=dp[l+1][r-1][1][1])%=MOD;
                        (dp[l][r][1][1]+=dp[l+1][r-1][1][0])%=MOD;
                        if (g[l]+1==g[r]) {
                            ++dp[l][r][1][1];
                            dp[l][r][1][1]%=MOD;
                        }
                    }
                } else if (g[r]!=g[r-1]) {
                    dp[l][r][0][0]=dp[l+1][r][0][0];
                    dp[l][r][1][0]=dp[l][r-1][1][1];
                    dp[l][r][0][1]=dp[l+1][r][0][1];
                    dp[l][r][1][1]=dp[l+1][r][1][1];
                    if (a[l]==a[r]) {
                        (dp[l][r][1][1]+=dp[l+1][r-1][1][1])%=MOD;
                        (dp[l][r][1][1]+=dp[l+1][r-1][0][1])%=MOD;
                        if (g[l]+1==g[r]) {
                            ++dp[l][r][1][1];
                            dp[l][r][1][1]%=MOD;
                        }
                    }
                } else {
                    dp[l][r][0][0]=dp[l+1][r-1][0][0];
                    dp[l][r][1][0]=dp[l][r-1][1][0];
                    dp[l][r][0][1]=dp[l+1][r][0][1];
                    dp[l][r][1][1]=(dp[l+1][r][1][1]+dp[l][r-1][1][1])%MOD;
                    if (a[l]==a[r]) {
                        (dp[l][r][1][1]+=dp[l+1][r-1][0][0])%=MOD;
                        (dp[l][r][1][1]+=dp[l+1][r-1][1][0])%=MOD;
                        (dp[l][r][1][1]+=dp[l+1][r-1][0][1])%=MOD;
                    } else {
                        (dp[l][r][1][1]+=MOD-dp[l+1][r-1][1][1])%=MOD;
                    }
                }
            }
        }

        cout << dp[1][n-1][1][1] << "\n"; 
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
