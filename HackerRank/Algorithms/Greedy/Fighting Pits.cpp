/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 两边队伍排序, 相同数合并对抗
 * a[k] 第k组, {力量, 相同力量累计数}
 * 
 */

#include <bits/stdc++.h>

using namespace std;

const int K=2e5+1;

typedef pair<int, int> ii;
typedef vector<ii> vii;

vii a[K];
int n, k, q;

int fight(int x, int y) {
    int xx=a[x].size()-1, yy=a[y].size()-1, kk;
    while (true) {
        if (xx<0) break;
        // 相同力量合并对抗
        kk=min((a[y][yy].second-1)/a[x][xx].first, (a[x][xx].second-1)/a[y][yy].first);
        yy-=kk*a[x][xx].first;
        xx-=kk*a[y][yy].first;
        yy-=a[x][xx].first;
        if (yy<0) break;
        xx-=a[y][yy].first;
    }
    return xx<0?y:x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k >> q;

    int s, t, o, x, y;
    for (int i=0; i<n; ++i) {
        cin >> s >> t;
        a[t].emplace_back(s, 1);
    }

    for (int i=1; i<=k; ++i) {
        sort(a[i].begin(), a[i].end());
        for (int j=1; j<a[i].size(); ++j) {
            if (a[i][j].first==a[i][j-1].first) {
                a[i][j].second+=a[i][j-1].second;
            }
        }
    }

    while (q--) {
        cin >> o >> x >> y;
        if (o==1) {
            // 题目保证新添加的数不小于组里任何一个数
            int sz=1;
            if (a[y].size() && a[y].back().first==x) {
                sz+=a[y].back().second;
            }
            a[y].emplace_back(x, sz);
        } else {
            cout << fight(x, y) << "\n";
        }
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
