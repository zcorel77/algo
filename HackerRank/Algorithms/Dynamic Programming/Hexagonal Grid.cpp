/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 两行拼成一行, 每次铺设产生的状态转移有两种, [1,1], [1,0,1]
 */

#include <bits/stdc++.h>

using namespace std;

const int N=22;
const int FULL=(1<<N)-1;

char dp[1<<N];

int t, n;
char solve(int a) {
    if (a==FULL) return 1;
    if (dp[a]!=-1) return dp[a];

    int k=1;
    while (a&k) k<<=1;

    dp[a]=0;
    if (!(a&(k<<1))) dp[a]|=solve(a|k|(k<<1));
    if (!(a&(k<<2))) dp[a]|=solve(a|k|(k<<2));
    return dp[a];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    memset(dp, -1, sizeof(dp));

    int a;
    string sa, sb;

    cin >> t;
    while (t--) {
        cin >> n;
        cin >> sa >> sb;

        a=0;
        for (int i=N-1; i>=n*2; --i) {
            (a<<=1)|=1;
        }

        for (int i=n-1; i>=0; --i) {
            (a<<=1)|=(sb[i]=='1');
            (a<<=1)|=(sa[i]=='1');
        }

        cout << (solve(a)==1?"YES":"NO") << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
