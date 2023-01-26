/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 分几种情况输出
 * 1. 就一个字母, 直接输出一串这个字母
 * 2. 频次最小的字母并非最小的字母
 *    不妨设为k, 存在比k小的字母a, 输出
 *    kaaabbb...k...mmmmnnnn...
 * 3. 频次最小的字母就是最小的字母
 *    不妨设为k, 输出, 注意k的频次小等于m的频次
 *    kkmkmkmkmkmmmmnnnnnnnn...
 */

#include <bits/stdc++.h>

using namespace std;

typedef pair<char, int> ci;
typedef vector<ci> vci;

int x;
vci p;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    for (int i=0; i<26; ++i) {
        cin >> x;
        if (x) p.emplace_back(i+'a', x);
    }

    if (p.size()==1) {
        // 就一个字母
        for (int i=0; i<p[0].second; ++i) {
            cout << p[0].first;
        }
    } else {
        sort(p.begin(), p.end(), [](const ci &a, const ci &b)->bool {
            return a.second==b.second?a.first<b.first:a.second<b.second;
        });
        sort(p.begin()+1, p.end());
    
        cout << p[0].first;
        --p[0].second;

        if (p[0].first>p[1].first) {
            // 频次最小的字母并非字典最小, 重排, 按字典序输出
            sort(p.begin(), p.end());
        } else {
            // 频次最小的字母就是最小的字母, 交替输出, 消耗掉频次最小的字母, 再按字典序输出
            while (p[0].second) {
                cout << p[0].first;
                --p[0].second;
                cout << p[1].first;
                --p[1].second;
            }
        }
        for (auto &e : p) {
            for (int i=0; i<e.second; ++i) {
                cout << e.first;
            }
        } 
    }
    cout << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
