/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 离散化数据, 计算各个值的频次
 * 按频次分组, 每组排序(使用set, 后面删除操作时复杂度O(log(n))),
 * 从频次高的组开始, 推答案层
 * 推的过程, 注意当前答案层, 与当前频次层的数的选择
 * 推一个当前答案层的数进下一个答案层, 然后在当前频次层中选择一个大于该数的最小数,
 * 并将其推进下一个答案层(若不存在则无法复原), 然后在当前频次层中删除该数
 * 新的答案层产生后, 整个推进最终答案, 再利用该答案层和下一个频次层构造下一个答案层
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1<<18;

typedef vector<int> vi;
typedef set<int> si;
typedef si::iterator sii;

int n, m, l, w, a[N<<1], b[N<<1], c[N];
si cc[N];

bool solve() {
    memcpy(b, a, sizeof(int)*m);
    sort(b, b+m);
    w=unique(b, b+m)-b;

    if (w!=n) return false;

    // discretize and counting
    for (int i=0, j; i<m; ++i) {
        j=lower_bound(b, b+w, a[i])-b;
        ++c[j];
    }

    for (int i=0; i<n; ++i) {
        cc[c[i]].insert(i);
    }

    l=1;
    for (int j=n>>1; (1<<l)<=n; ++l, j>>=1) {
        if (cc[l].size()!=j)
            return false;
    }

    vi cur, prev, res;
    cur.push_back(*cc[l].begin());
    --l;

    sii ia, ib;
    for (; l>0; --l) {
        res.insert(res.end(), cur.begin(), cur.end());
        swap(cur, prev);
        cur.clear();

        for (auto &i : prev) {
            ia=cc[l].insert(i).first;
            ib=ia; ++ib;
            if (ib==cc[l].end()) return false;
            cur.push_back(*ia); cur.push_back(*ib);
            cc[l].erase(ia); cc[l].erase(ib);
        }
    }

    res.insert(res.end(), cur.begin(), cur.end());

    for (int i=0; i<res.size(); ++i) {
        a[i]=b[res[i]];
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    m=(n<<1)-1;
    
    for (int i=0; i<m; ++i) {
        cin >> a[i];
    }

    if (solve()) {
        cout << "YES\n";
        for (int i=0; i<m; ++i) {
            cout << a[i] << (i==(m-1)?"\n":" ");
        }
    } else {
        cout << "NO\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
