/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 从后往前递推求解, 如果要满足ans[i], 需要ans[i-i]>=(ans[i]+a[i]+1)/2
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+1;

int n, a[N];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i=0; i<n; ++i) cin >> a[i];

    int ans=0;
    for (int i=n-1; i>=0; --i) (ans+=a[i]+1)/=2;

    cout << ans << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
