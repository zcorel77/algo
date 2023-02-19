/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 每行按位表示, 0: '.', 1: '#', e.g. 101001: '#.#..#'
 */

#include <bits/stdc++.h>

using namespace std;

const int N=22;
const int M=1<<8;
const int MOD=1e9+7;
const int shape2[4][2]={{1, 7}, {7, 1}, {4, 7}, {7, 4}};
const int shape3[4][3]={{1, 1, 3}, {3, 1, 1}, {2, 2, 3}, {3, 2, 2}};

int state[N], n, m, full;
long dp[N][M][M];

long solve(int r, int s0, int s1, int s2) {
    if (s0==full) {
        if (r==n) return 1;
        if (dp[r][s1][s2] == -1)
            dp[r][s1][s2] = solve(r+1, s1, s2, state[r+3]);
        return dp[r][s1][s2];
    }

    long ret = 0;

    int cur = 1;
    while (cur&s0) cur<<=1;

    for (int i=0; i<m-2; ++i) {
        for (int j=0; j<4; ++j) {
            int sh0 = shape2[j][0]<<i;
            int sh1 = shape2[j][1]<<i;
            // 当前格未填, 或第一行冲突, 或第二行冲突
            if (!(sh0&cur) || (sh0&s0) || (sh1&s1)) continue;
            ret += solve(r, s0|sh0, s1|sh1, s2);
        }
    }

    for (int i=0; i<m-1; ++i) {
        for (int j=0; j<4; ++j) {
            int sh0 = shape3[j][0]<<i;
            int sh1 = shape3[j][1]<<i;
            int sh2 = shape3[j][2]<<i;
            // 当前格未填, 或第一行冲突, 或第二行冲突, 或第三行冲突
            if (!(sh0&cur) || (sh0&s0) || (sh1&s1) || (sh2&s2)) continue;
            ret += solve(r, s0|sh0, s1|sh1, s2|sh2);
        }
    }

    return ret%MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    string s;

    cin >> t;
    while (t--) {
        cin >> n >> m;
        full=(1<<m)-1;

        memset(state, 0, sizeof(state));
        memset(dp, -1, sizeof(dp));

        for (int i=0; i<n; ++i) {
            cin >> s;
            for (int j=0; j<m; ++j) {
                if (s[j]=='#') {
                    state[i]|=(1<<j);
                }   
            }
        }
        state[n]=state[n+1]=full;

        cout << solve(0, state[0], state[1], state[2]) << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
