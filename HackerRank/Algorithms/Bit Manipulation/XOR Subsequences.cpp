/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 利用 Fast Walsh-Hadamard Transform 计算卷积
 * Brute Force, TLE
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+1;
const int V=1<<16;
const int MOD=1e9+1;
const int INV2=(MOD+1)>>1;

int n;
long a[V], cnt[V];

void transform(int x, int y) {
    if (x==y-1) return;

    int h=(y-x)/2, z=x+h;
    transform(x, z); transform(z, y);
    for (int i=x; i<z; ++i) {
        long a1=a[i], a2=a[i+h];
        a[i]=(a1-a2+MOD)%MOD;
        a[i+h]=(a1+a2)%MOD;
    }
}

void detransform(long x, long y) {
    if (x==y-1) return;

    int h=(y-x)/2, z=x+h;
    for (int i=x; i<z; ++i) {
        long a1=a[i], a2=a[i+h];
        a[i]=(a1+a2)*INV2%MOD;
        a[i+h]=(a2-a1+MOD)*INV2%MOD;
    }
    detransform(x, z); detransform(z, y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int x, xx=0;

    cin >> n;
    for (int i=0; i<n; ++i) {
        cin >> x;
        ++a[xx^=x];
    }
    memcpy(cnt, a, sizeof(long)*V);

    // Brute Force
    // a[0] += 1L;
    // for (int i=0; i<V; ++i) {
    //     for (int j=0; j<i; ++j) {
    //         cnt[i^j] += a[i]*a[j];
    //     }
    // }

    // Fast Walsh-Hadamard Transform
    transform(0, V);

    for (int i=0; i<V; ++i) {
        (a[i]*=a[i])%=MOD;
    }

    detransform(0, V);

    // remove diagonal, i^i=0, i~[0,n)
    a[0]-=n;

    // deduplicate, i^j=j^i
    for (int i=0; i<V; ++i) {
        (cnt[i]+=a[i]*INV2)%=MOD;
    }

    int ma_i=0;
    for (int i=1; i<V; ++i) {
        if (cnt[ma_i]<cnt[i]) ma_i=i;
    }
    cout << ma_i << " " << cnt[ma_i] << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
