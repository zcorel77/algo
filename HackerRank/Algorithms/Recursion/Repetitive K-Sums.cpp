/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * multiset, 有序, O(logn) 插入, 删除, 查找元素
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<long> vl;
typedef multiset<long> msl;

int t, n, k;
long l;
msl s;
vl ans;

long cmb(long n, long k) {
    if (k>n-k) k=n-k;
    if (!k) return 1L;

    long ret=n;
    for (long i=2L; i<=k; ++i) {
        ret*=(n-i+1L);
        ret/=i;
    }
    return ret;
}

void clean(int i, int k, long amt) {
    // 剩余由最小数填补
    if (i==0) {
        amt+=k*ans[i];
        k=0;
    }

    if (k) {
        // 递归
        for (int j=0; j<=k; ++j) {
            clean(i-1, k-j, amt+j*ans[i]);
        }
    } else {
        // 清理, 每次移除一个
        s.erase(s.find(amt));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long x;

    cin >> t;
    while (t--) {
        s.clear();
        ans.clear();

        cin >> n >> k;

        // 组合数, 有放回的n个球取k个的方案数
        l=cmb(n+k-1, k);
        for (int i=0; i<l; ++i) {
            cin >> x;
            s.insert(x);
        }

        // 选取组合最小数/k
        ans.push_back(*s.begin()/k);
        s.erase(s.begin());

        for (int i=1; i<n; ++i) {
            // 选取组合最小数减去k-1倍的原始最小数
            ans.push_back(*s.begin()-ans.front()*(k-1));
            // 清除所有已选数的k次组合所能产生的组合数
            for (int j=1; j<=k; ++j) {
                clean(i-1, k-j, j*ans[i]);
            }
        }

        for (int i=0; i<n; ++i) {
            cout << ans[i] << (i<n-1?" ":"\n");
        }
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
