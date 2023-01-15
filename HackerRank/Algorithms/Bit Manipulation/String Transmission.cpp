/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 先计算总数, 在DP计算周期串个数, 总数-周期串个数
 *   cnt 错误数, cnt0 0的个数
 *   dp[idx + 1][cnt + cnt0]         += dp[idx][cnt]    (flip 0)
 *   dp[idx + 1][cnt + n/div - cnt0] += dp[idx][cnt]    (flip 1)
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1001;
const int MOD=1e9+7;

typedef vector<int> vi;
typedef vector<vi> vvi;

int Cr[N][N];
int t, n, k;
string s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // Pascal's triangle
    Cr[0][0]=1;
    for (int i=1; i<N; ++i) {
        Cr[i][0]=1;
        for (int j=1; j<=i; ++j) {
            Cr[i][j]=(Cr[i-1][j-1]+Cr[i-1][j])%MOD;
        }
    }

    cin >> t;
    while (t--) {
        cin >> n >> k;
        cin >> s;

        long ans=0L;

        // total
        for (int i=0; i<=k; ++i) {
            (ans+=Cr[n][i])%=MOD;
        }

        // divisor
        vi div;
        for (int i=1; i<=n/2; ++i) {
            if (n%i==0) div.push_back(i);
        }

        vvi dp(div.size(), vi(n+k+1, 0));

        int cnt0, cnt1;
        for (int di=0; di<div.size(); ++di) {
            dp[di][0]=1;

            for (int i=0; i<div[di]; ++i) {
                // counting zero
                cnt0=0;
                for (int j=i; j<n; j+=div[di]) {
                    if (s[j]=='0') cnt0++;
                }
                cnt1=n/div[di]-cnt0;

                vi dp0(n+k+1, 0);
                swap(dp0, dp[di]);

                for (int j=0; j<=k; ++j) {
                    (dp[di][j+cnt0]+=dp0[j])%=MOD;
                    (dp[di][j+cnt1]+=dp0[j])%=MOD;
                }
            }

            // exclude divisor's divisor
            for (int dj=0; dj<di; ++dj) {
                if (div[di]%div[dj]==0) {
                    for (int j=0; j<=k; ++j) {
                        (dp[di][j]+=MOD-dp[dj][j])%=MOD;
                    }
                }
            }

            for (int j=0; j<=k; ++j) {
                (ans+=MOD-dp[di][j])%=MOD;
            }
        }

        cout << ans << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
