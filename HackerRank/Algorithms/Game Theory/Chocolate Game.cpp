/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 偶数堆的话, 对方从奇数堆(k)拿, 我方则从k+1堆拿走相同数, 保持偶数堆与前堆之差
 * 奇数堆的话, 对方从偶数堆(k)拿, 我方则从k+1堆拿走相同数, 保持奇数堆与前堆之差
 * 简化之, 从末尾算, 奇数堆(1, 3, 5...)与前堆之差的异或和就是整个序列的胜态
 * 求子序列胜态数, 也就是总数-子序列负态数,
 * 子序列负态也就是存在两个后缀异或和相同, (引入一个0序列, 后缀异或和为0)
 * 计算子序列负态, 需记忆两个后缀异或和, 起点分别为n, n-1
 * 从后往前遍历数组,
 * 一边寻找与当前后缀异或和相同的后缀异或和计数, 并累计答案,
 * 一边累加后缀异或和计数
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+1;

int n, a[N];
map<int, int> cnt[2]={{{0, 1}}, {{0, 1}}};

long solve() {
    long ans=0L;

    // 后缀异或和
    int suf[2]={0, 0}, k;
    for (int i=n; i>0; --i) {
        k=i&1;
        // i起始, i后面的后缀异或和中若存在与i起始的异或和相同, 则存在区间异或和为0
        ans+=cnt[k][suf[k]^a[i]];
        // i-1起始
        if (i>1) ans+=cnt[k][suf[k]^(a[i]-a[i-1])];
        ++cnt[k][suf[k]^=(a[i]-a[i-1])];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i=1; i<=n; ++i) {
        cin >> a[i];
    }

    cout << n*1L*(n-1)/2-solve() << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
