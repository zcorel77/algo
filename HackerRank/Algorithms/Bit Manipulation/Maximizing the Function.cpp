/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 区间异或和可由两个边界的前缀异或和求解 Xor[x, y]=Xor[0, x-1]^Xor[0, y]
 * 也就是若Xor[0, x-1]与Xor[0, y]不相同, Xor[x, y]为1
 * 求解区间[x,y]所有子区间异或和的和, 也就是相当求解区间[x-1,y]中有多少对Xor[0, i], Xor[0, j]不相同
 * 要使区间[x,y]所有子区间异或和的和最大, 也就是尽量使Xor[0, i]为0的个数与为1的个数接近
 * 改变一个位置k的值, 将改变位置i之后所有的Xor[0, i], k<=i<=n的值
 * 只要k>0, 总能找到一个位置, 使得Xor[0, i]为0的个数为总数的一半
 */

#include <bits/stdc++.h>

using namespace std;

const int N=5e5+2;

int n, q, a[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // 原始数据x的下标为[0, n-1], 前缀异或和s[k]=x[0]^x[1]^...^x[k-1]
    // xx 前缀异或和, a[i]前缀异或和为1的个数, 也就是前缀异或和的前缀和
    // a[i]=s[0]+s[1]+...+s[i-1]
    int xx=0, x, y, k, c, h;

    cin >> n >> q;
    for (int i=1; i<=n; ++i) {
        cin >> x;
        a[i+1] = a[i]+(xx^=x);
    }

    while (q--) {
        cin >> x >> y >> k;
        y += 2;
        c = y-x;
        h = k?(c/2):(a[y]-a[x]);
        cout << (h*1L*(c-h)) << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
