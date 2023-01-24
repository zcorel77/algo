/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * Nim游戏, 利用Mex, 预先计算好一堆x个瓶子的grundy
 * x个瓶子的Mex状态为, x-1, x-2, 
 *   以及x中间删除一个或俩个连续瓶子, 也就是产生若干种两堆的状态 
 * 利用DP求解
 * 问题输入转化为k堆瓶子, 异或求解
 */

#include <bits/stdc++.h>

using namespace std;

const int N=301;

int t, n, p[N], gr[N], mex[N];
string s;

void grundy(int x) {
    fill_n(mex, x, 0);
    mex[gr[x-1]]=1;
    mex[gr[x-2]]=1;
    for (int i=1; i<x-1; ++i) {
        mex[gr[i]^gr[x-i-1]] = 1;
    }
    for (int i=1; i<x-2; ++i) {
        mex[gr[i]^gr[x-i-2]] = 1;
    }

    int k=0;
    for (; k<x; ++k) {
        if (!mex[k]) break;
    }
    gr[x]=k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    gr[0]=0; gr[1]=1;
    for (int i=2; i<N; ++i) {
        grundy(i);
    }

    cin >> t;
    while (t--) {
        cin >> n;
        cin >> s;

        fill_n(p, n, 0);

        int k=0;
        for (int i=0; i<n; ++i) {
            if (s[i]=='I') ++p[k];
            else if (p[k]) ++k;
        }

        int x=0;
        for (int i=0; i<=k; ++i) {
            x^=gr[p[i]];
        }

        cout << (x?"WIN":"LOSE") << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
