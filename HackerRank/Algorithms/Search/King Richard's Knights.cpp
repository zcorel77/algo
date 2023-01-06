/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 计算旋转后框的恢复到原始矩阵的坐标
 * 计算查询点所在的框
 * 遍历需旋转的框, 每次把框外的值输出
 */

#include <bits/stdc++.h>

using namespace std;

const int N=3e7+1;
const int S=2e5+1;
const int L=2e5+1;

typedef vector<long> vl;
vl qq[S];

long q[L];
int n, s, l, a[S], b[S], d[S], aa[S], bb[S], ans[L][2];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    cin >> s;
    for (int i=1; i<=s; ++i) {
        cin >> a[i] >> b[i] >> d[i];
    }
    cin >> l;
    for (int i=0; i<l; ++i) {
        cin >> q[i];
    }

    aa[0] = a[0] = 1; bb[0] = b[0] = 1; d[0] = n;
    aa[1] = a[1]; bb[1] = b[1];
    for (int i=2; i<=s; ++i) {
        if (i%4==1) {
            aa[i] = aa[i-1]+(a[i]-a[i-1]);
            bb[i] = bb[i-1]+(b[i]-b[i-1]);
        } else if (i%4==2) {
            aa[i] = aa[i-1]+(b[i-1]+d[i-1]-b[i]-d[i]);
            bb[i] = bb[i-1]+(a[i]-a[i-1]);
        } else if (i%4==3) {
            aa[i] = aa[i-1]+(a[i-1]+d[i-1]-a[i]-d[i]);
            bb[i] = bb[i-1]+(b[i-1]+d[i-1]-b[i]-d[i]);
        } else {
            aa[i] = aa[i-1]+(b[i]-b[i-1]);
            bb[i] = bb[i-1]+(a[i-1]+d[i-1]-a[i]-d[i]);
        }
    }

    for (int i=0; i<l; ++i) {
        int x=q[i]/n+1, y=q[i]%n+1;
        int L=0, R=s, mid, qi;
        while (L<=R) {
            mid = (L+R)/2;
            if (aa[mid]<=x && x<=aa[mid]+d[mid]
                && bb[mid]<=y && y<=bb[mid]+d[mid]) { L=mid+1; qi=mid; }
            else { R=mid-1; }
        }
        qq[qi].push_back(i);
    }

    for (int i=0; i<=s; ++i) {
        for (auto &e: qq[i]) {
            int x=q[e]/n+1, y=q[e]%n+1;
            if (i%4==1) {
                ans[e][0] = a[i]+(y-bb[i]);
                ans[e][1] = b[i]+d[i]-(x-aa[i]);
            } else if (i%4==2) {
                ans[e][0] = a[i]+d[i]-(x-aa[i]);
                ans[e][1] = b[i]+d[i]-(y-bb[i]);
            } else if (i%4==3) {
                ans[e][0] = a[i]+d[i]-(y-bb[i]);
                ans[e][1] = b[i]+(x-aa[i]);
            } else {
                ans[e][0] = a[i]+(x-aa[i]);
                ans[e][1] = b[i]+(y-bb[i]);
            }
        }
    }

    for (int i=0; i<l; ++i) {
        cout << ans[i][0] << " " << ans[i][1] << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
