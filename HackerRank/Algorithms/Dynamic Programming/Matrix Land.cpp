/*
 * author: Corel
 *  email: zcorel@hotmail.com
 *        
 *       <----------i
 *          l[i]
 *                  i------------->
 *                      r[i]
 * 
 *             <------------->
 *       <----------i
 *          xl[i]
 * 
 *             <------------->
 *                  i------------->
 *                      xr[i]
 * 
 *             <------------->
 *       <----------i------------->
 *                a[i]
 *
 *  l[i], 位置i往左连续块的累计最大值
 *  r[i], 位置i往右连续块的累计最大值
 * xl[i], 位置i往左连续块的累计值加上联通上层某连续块的最大值
 * xr[i], 位置i往右连续块的累计值加上联通上层某连续块的最大值
 *  a[i], 位置i左连续块的累计值加右连续块的累计值加上联通上层某连续块的最大值
 */

#include <bits/stdc++.h>

using namespace std;

const int N=4e6+1;
const int INF=0x3f3f3f3f;

int v[N], l[N], r[N], xl[N], xr[N], a[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, vl, vr;
    cin >> n >> m;

    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j) {
            cin >> v[j];
        }

        vl=vr=0;
        for (int j=0, k; j<m; ++j) {
            k=m-j-1;
            l[j]=vl=max(vl+v[j], v[j]);
            r[k]=vr=max(vr+v[k], v[k]);
        }

        vl=vr=-INF;
        for (int j=0, k; j<m; ++j) {
            k=m-j-1;
            xl[j]=vl=max(vl+v[j], a[j]+l[j]);
            xr[k]=vr=max(vr+v[k], a[k]+r[k]);
        }

        for (int j=0; j<m; ++j) {
            a[j]=max(xl[j]+(j+1<m?max(r[j+1], 0):0), xr[j]+(j>0?max(l[j-1], 0):0));
        }
    }

    int ans = -INF;
    for (int j=0; j<m; ++j) {
        ans=max(ans, a[j]);
    }
    cout << ans << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
