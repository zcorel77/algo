/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 打表, 发现起始0, 循环节9, (0 0 1 1 2 2 3 3 4)
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e4+1;
const int primes[] = {2, 3, 5, 7, 11, 13};

int t, n, gr[N];
bool mex[N];

void grundy() {
    gr[0]=gr[1]=0;
    for (int i=2; i<N; ++i) {
        memset(mex, 0, sizeof(bool)*i);
        for (int p : primes) {
            if (i>=p) mex[gr[i-p]]=1;
        }

        int k=0;
        while (k<i && mex[k]) ++k;
        gr[i]=k;
    }
}

const int cgr[] = {0, 0, 1, 1, 2, 2, 3, 3, 4};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // grundy();

    int ans;
    long x;

    cin >> t;
    while (t--) {
        ans=0;

        cin >> n;
        for (int i=0; i<n; ++i) {
            cin >> x;
            ans^=cgr[x%9];
        }

        cout << (ans?"Manasa":"Sandy") << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
