/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 完全一样的字符串不可归纳, 返回字符串长度
 * 做变换, * a: 1, b:2, c:3,
 * 则有, a^b=c, b^c=a, c^a=b
 * 求所有字符串表示值的异或和,
 * 异或和为0, 返回2, 否则, 返回1
 */

#include <bits/stdc++.h>

using namespace std;

const int N=101;

int n, a, u;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    string s;

    cin >> t;
    while (t--) {
        cin >> s;

        n=s.length(), a=s[0]-'`', u=1;
        for (int i=1; i<n; ++i) {
            a^=s[i]-'`';
            u&=s[i]==s[i-1];
        }

        if (u) {
            cout << n << "\n";
        } else {
            cout << (a?1:2) << "\n";
        }
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
