/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 遍历m个除数, 若可整除, 分为偶数组状态为0, 分为奇数组状态为除数的解
 * 所有可整除的情况计算mex
 */

#include <bits/stdc++.h>

using namespace std;

const int M=10;

long n, s[M];
int m;
map<long, int> gr;

int solve(long nn) {
    if (gr.find(nn)!=gr.end()) return gr[nn];

    vector<int> mex(m+1, 0);
    for (int i=0; i<m; ++i) {
        if (nn%s[i]==0) {
            if ((nn/s[i])&1) {
                mex[solve(nn/s[i])]=1;
            } else {
                mex[0]=1;
            }
        }
    }

    for (int i=0; i<m; ++i) {
        if (mex[i]==0) return gr[nn]=i;
    }

    return gr[nn]=m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i=0; i<m; ++i) {
        cin >> s[i];
    }

    cout << (solve(n)?"First":"Second") << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
