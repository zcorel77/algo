/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 序列拆成若干段递增序列, 这些序列满足, 最后一个元素>=n/2, 且每个元素>=前驱的两倍
 * 并可有结论, 递增序列长度d=floor(log2(n))
 * 则有递推, a[m]=sum(c[i]*a[m-i]), i~[1,d], c[i]为长度i的递增序列种数
 * c[i]分解成u[i][j], j为序列中第一个元素,
 * 即, c[i]=sum(u[i][j]), j~[1, n]
 * 则有递推u[i][j]=sum(u[i-1][k]), k>=2*j, i>0, j<n/2
 *               =0, i>0, j>=n/2
 *               =0, i=0, j<n/2
 *               =1, i=0, j>=n/2
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+1;
const int M=5e5+1;
const int D=17;
const int MOD=1e8+7;

int a[M], c[D], u[D][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t, n, m, d;

    cin >> t;
    while (t--) {
        cin >> n >> m;

        memset(a, 0, sizeof(a));
        memset(c, 0, sizeof(c));
        memset(u, 0, sizeof(u));

        for (int j=n; j>n/2; --j) {
            u[0][j]=1;
        }
        c[0]=n-n/2;

        for (int i=1; i<D; ++i) {
            d=0;
            for (int j=n; j>0; --j) {
                // d, sum(u[i-1][k])
                d=(d+u[i-1][j])%MOD;
                u[i][j/2]=d;
            }

            for (int j=n; j>0; --j) {
                c[i]=(c[i]+u[i][j])%MOD;
            }
        }

        a[0]=1;
        for (int i=1; i<=m; ++i) {
            for (int j=0; c[j]&&j+i<=m; ++j) {
                a[i+j]=(a[i+j]+a[i-1]*1L*c[j])%MOD;
            }
        }

        cout << a[m] << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
