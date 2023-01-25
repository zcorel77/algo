/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 预先求一堆i个石子的grundy[i], 分三种情况, k=2, k=3, k>=4
 * 然后DP求解, 求解总共n个石子分m堆产生的各种grundy[0~1024]的个数
 * 依m从1到10推进
 */

#include <bits/stdc++.h>

using namespace std;

const int N=601;
const int M=10;
const int K=601;
const int T=1024;
const int MOD=1e9+7;

typedef vector<int> vi;

int n, m, k, gr[N], dp[2][N][T];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> k;
    if (k==2) {
        // 最多分两堆
        // 偶数堆可以分成两堆一样的, 奇数堆肯定分布成两堆一样的, 
        // 且不管怎么分, 对方能分出两堆一样的加一个奇数堆
        // 偶数堆必赢, 奇数堆必输
        for (int i=1; i<=n; ++i) {
            gr[i]=(i&1)^1;
        }
    } else if (k==3) {
        // 最多分三堆
        for (int i=1; i<=n; ++i) {
            vi mex(i+1, 0);
            for (int j=1; j<i; ++j) {
                mex[gr[j]^gr[i-j]]=1;
            }
            for (int j=1; j<i; ++j) {
                for (int l=1; l<j; ++l) {
                    mex[gr[l]^gr[j-l]^gr[i-j]]=1;
                }
            }
            int j=0;
            for (; j<T; ++j) {
                if (!mex[j]) break;
            }
            gr[i]=j;
        }
    } else {
        // 最多分四堆以上
        // k->{1, k-1}, {1, 1, k-2}, {1, 1, 1, k-3}, {2, 2, k-4}, ...
        // 所有小于k的状态都可以转移到, 且
        // gr[1]=0, gr[2]=1, ...
        // 因此, gr[k] = k-1
        for (int i=1; i<=n; ++i) {
            gr[i]=i-1;
        }
    }

    // dynamic programing
    int mm=0;
    dp[mm][0][0]=1;
    for (int i=0; i<m; ++i) {
        mm^=1;
        memset(dp[mm], 0, sizeof(int)*N*T);
        for (int j=0; j<=n; ++j) {
            for (int t=0; t<T; ++t) {
                // j个石头分i堆grundy为t的计数不为0的话
                // 更新从j+1到n个石头分i+1堆grundy为t^gr[第i堆石子]的计数
                if (!dp[mm^1][j][t]) continue;

                for (int l=1; l<=n-j; ++l) {
                    (dp[mm][l+j][t^gr[l]]+=dp[mm^1][j][t])%=MOD;
                }
            }
        }
    }

    long ans=0L;
    for (int t=1; t<T; ++t) {
        ans+=dp[mm][n][t];
    }

    cout << ans%MOD << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
