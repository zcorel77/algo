/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * dp求解
 * dp[n][k]对于十进制整数n有多少个长度为k的decibinary,
 * a[n][k]累计对于十进制整数n有多少个长度小于k的decibinary,
 * b[n]累计对于十进制整数n有多少个表达小于n的decibinary
 * 关键如何给出N,K
 * 对于N, 应该超不过decibinary99..9(15个)所表达的十进制整数
 * 也就是9*(2^0+2^1+...+2^14)约为295000
 * 在就是找K, 描述295000最多可以用几位的decibinary
 * 也就是100...0, (K-1个0), 所以K约为 ceil(log2(N))+1=20
 * 给定x, 二分查找n, k, 然后在暴力求解
 */

#include <bits/stdc++.h>

using namespace std;

const int N=295000;
const int K=20;

int q;
long x, a[N][K], b[N], dp[N][K];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    fill_n(a[0], K, 1); // 100..0
    b[0]=1;
    // dp[0][1]=1;

    for (int i=1; i<N; ++i) {
        for (int j=1; j<K; ++j) {
            a[i][j]=a[i][j-1];
            for (int k=1; k<10; ++k) {
                x=k*(1<<(j-1));
                // 长度小于j的数都能进位到j
                // if (x<=i) dp[i][j]+=a[i-x][j-1];
                if (x<=i) a[i][j]+=a[i-x][j-1];
            }
            // a[i][j]=a[i][j-1]+dp[i][j];
        }
        b[i]=b[i-1]+a[i][K-1];
    }

    cin >> q;
    while (q--) {
        cin >> x;

        // 二分查找an
        int l=0, r=N-1, m, an=0, ak=0;
        while (l<=r) {
            m=(l+r)/2;
            if (b[m]<x) { l=m+1; }
            else { r=m-1; an=m; }
        }
        if (an!=0) x-=b[an-1];

        // 二分查找ak
        l=0, r=K-1;
        while (l<=r) {
            m=(l+r)/2;
            if (a[an][m]<x) { l=m+1; }
            else { r=m-1; ak=m; }
        }

        --ak;
        if (ak<0) {
            cout << 0;
        } else {
            while (ak>=0) {
                for (int i=0; i<10; ++i) {
                    int bn=an-(1<<ak)*i;
                    if (x>a[bn][ak]) {
                        x-=a[bn][ak];
                    } else {
                        cout << i;
                        --ak; an=bn;
                        break;
                    }
                }
            }
        }
        cout << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
