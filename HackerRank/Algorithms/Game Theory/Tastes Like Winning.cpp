/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 首先, nim游戏, 必胜策略为所有数的异或和不为0
 * 不妨计算异或和为0的个数, 再由总可能数减掉异或和为0的个数
 * a(k, i) i堆, k种数的全排列
 * f(i) i堆, 所有数不同, 且异或和为0的个数
 * 由于前i-1堆任意情况,都可以确定唯一的第i个数, 使得i个数异或和为0
 * 若前i-1堆异或和为0, 则需要第i个数为0, 这些case不允许, 排除掉
 * 若第i个数与前i-1个数中某个重复, 也得排除, 该情况下, 剩余i-2个数异或和为0,
 * 第i个数取值范围(k-1-(i-2)), 某个重复数的位置可有i-1中选择,
 * 所以, f(i)=i-1堆的全排列-f(i-1)-(i-1)*(k-1-(i-2))*f(i-2)
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e7+1;
const int MOD=1e9+7;

int n, m;
int f[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    int k=1, a;
    for (int i=0; i<m; ++i) {
        (k<<=1)%=MOD;
    }

    a=k-1, f[0]=1, f[1]=0;
    for (int i=2; i<=n; ++i) {
        f[i]=(a-f[i-1]-(i-1)*1L*(k-i+1)%MOD*f[i-2])%MOD;
        a=a*1L*(k-i)%MOD;
    }

    (((a-=f[n])%=MOD)+=MOD)%=MOD;
    cout << a << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
