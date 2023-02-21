/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * len[i], 记录以i结尾的最长严格递增序列长度
 * idx[i], 记录长度i的的序列的结尾数中的最小数
 * s, 候选序列的结尾数集合, 最终, s也是最长严格递增序列
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e6+1;

set<int> s;
int n, v, l, len[N], idx[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    set<int>::iterator cur, prev, old;

    cin >> n;
    for (int i=0; i<n; ++i) {
        cin >> v;

        // 集合中查找v, 找不到则插入v
        cur = s.find(v);
        if (cur == s.end()) {
            cur = s.insert(v).first;
        }

        // 若v在集合中有前驱, 新的长度为前驱长度+1, 否则就是1
        l=1;
        if (cur != s.begin()) {
            prev = cur;
            --prev;

            l+=len[*prev];
        }

        // 若原来的长度小于新的长度, 更新之
        if (len[*cur] < l) {
            old = s.find(idx[l]);
            if (old != s.end()) {
                s.erase(old);
            }
            len[*cur]=l;
            idx[l]=*cur;
        }
    }

    // for (cur=s.begin(); cur != s.end(); ++cur) {
    //     cout << *cur << " ";
    // }
    // cout << "\n";
    cout << s.size() << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
