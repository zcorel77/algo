/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 先排序, 计算相邻两个数的差, 跨度k的两个数的差
 * 计算, 连续k个数中, 所有数到头数的差和, 所有数到尾数的差和,
 * 顺便累加前k个数的逐对差和, 即对尾数[1,k)求和(求和项, 所有数到尾数的差和)
 * 推进k个数的逐对差和, 右移时, 减掉所有数到头数的差和, 并更新之
 * 更新所有数到新的尾数的差和, 并加之
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+1;

int n, k, p[N], d1[N], dk[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    for (int i=0; i<n; ++i) {
        cin >> p[i];
    }

    sort(p, p+n);
    for (int i=1; i<n; ++i) {
        d1[i]=p[i]-p[i-1];
    }

    for (int i=k-1; i<n; ++i) {
        dk[i]=p[i]-p[i-k+1];
    }

    long diff_l=0L, diff_r=0L, sum=0L, ans=0L;
    for (int i=1; i<k; ++i) {
        diff_l+=p[i]-p[0];
        diff_r+=i*1L*d1[i];
        sum+=diff_r;
    }
    ans=sum;

    for (int i=k; i<n; ++i) {
        sum-=diff_l;
        diff_l-=(k-1)*1L*d1[i-k+1];
        diff_l+=dk[i];

        diff_r-=dk[i-1];
        diff_r+=(k-1)*1L*d1[i];
        sum+=diff_r;
        ans=min(ans, sum);
    }
    cout << ans << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
