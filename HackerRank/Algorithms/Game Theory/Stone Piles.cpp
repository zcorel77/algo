/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 暴力解gr[x]
 * 将x提取一个数[1,x), 形成一堆, 剩余成一堆并赋值mex, 或者递归
 * 递归的时候, 最小数比刚形成的一堆大
 * 对整个x可分组的情况递归完毕后, 利用mex提取gr[x]
 */

#include <bits/stdc++.h>

using namespace std;

const int N=51;
const int T=11;
const int MEX=64;

typedef vector<int> vi;

int t, n, x, gr[N];
bool mex[MEX];

void grundy(int mi, int nn, int prev) {
    for (int i=mi; i<(nn+1)/2; ++i) {
        mex[prev^gr[i]^gr[nn-i]]=1;
        grundy(i+1, nn-i, prev^gr[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    gr[0]=gr[1]=gr[2]=0; gr[3]=1;
    for (int i=4; i<N; ++i) {
        memset(mex, 0, sizeof(mex));
        grundy(1, i, 0);

        int k=0;
        while (k<MEX && mex[k]) ++k;
        gr[i]=k;
    }

    cin >> t;
    while (t--) {
        cin >> n;

        int ans=0;
        for (int i=0; i<n; ++i) {
            cin >> x;
            ans^=gr[x];
        }

        cout << (ans?"ALICE":"BOB") << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
