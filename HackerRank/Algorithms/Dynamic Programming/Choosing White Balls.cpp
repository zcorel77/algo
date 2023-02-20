/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 状压
 * 每轮对所有可能求解, 并取平均
 * map键值由长度(32 high bits)和状态(32 low bits)组成, 状态, 1白球, 0黑球
 * 注意, 需用hash map (__gnu_pbds::cc_hash_table), 普通map会TLE
 * 
 * 亦可考虑一个长度阈值(比如2^25), 小于阈值时用码表, 大于阈值时用map
 */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

const int N=30;

inline long mov(const long &a, const long &i) {
    return (a>>(i+1)<<i)|(a&((1L<<i)-1L));
}

__gnu_pbds::cc_hash_table<long, double> mem; 
double solve(long a, long n, long k) {
    if (!k) return 0;

    long h = (n<<32)|a;
    if (mem.find(h)!=mem.end()) return mem[h];

    double ans = 0.;
    for (long i=0, j; i<n; ++i) {
        j=n-i-1;
        ans += max(solve(mov(a, i), n-1, k-1)+((a>>i)&1),
                   solve(mov(a, j), n-1, k-1)+((a>>j)&1));
    }
    ans/=n;

    return mem[h]=ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, k, a=0;
    string s;

    cin >> n >> k;
    cin >> s;

    for (int i=0; i<n; ++i) {
        (a<<=1)|=(s[i]=='W');
    }

    cout << fixed << setprecision(8) << solve(a, n, k) << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
