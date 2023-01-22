/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * recursion solution got TLE,
 * so, try dynamic programing
 * 推进3个状态, +, -, *的结果
 * 然后从末尾状态dp[n-1][0]往回找推进路径
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e4+1;
const int M=101;

int n, a[N];
char dp[N][M], op[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i=0; i<n; ++i) {
        cin >> a[i];
    }

    dp[0][a[0]]=1;
    for (int i=1; i<n; ++i) {
        for (int j=0; j<M; ++j) {
            if (dp[i-1][j]) {
                dp[i][(j+a[i])%M]='+';
                dp[i][(j-a[i]+M)%M]='-';
                dp[i][(j*a[i])%M]='*';
            }
        }
    }

    if (dp[n-1][0]) {
        int r=0;
        for (int i=n-1; i>0; --i) {
            op[i]=dp[i][r];
            if (dp[i][r]=='+') {
                (r+=M-a[i])%=M;
            } else if (dp[i][r]=='-') {
                (r+=a[i])%=M;
            } else {
                for (int j=0; j<M; ++j) {
                    if ((j*a[i])%M==r) {
                        r=j;
                        break;
                    }
                }
            }
        }

        cout << a[0];
        for (int i=1; i<n; ++i) {
            cout << op[i] << a[i];
        }
        cout << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
