/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 答案可为非全连接图,
 * 根据Q, 做特定类型的全连接图, 再考虑背包问题, 组合这些全连接图
 * 1, Q=2, 星型
 *    r
 *  / | \
 * x1...xn
 * 
 * 2, Q>2 even
 *      -------r------
 *     /       |      \
 *    a11     a12     a13
 *     |       |       |
 *    ...     ...     ...
 *     |       |       |
 *    ak1     ak2     ak3
 *   / | \   / | \   / | \
 *  x1...xn y1...ym z1...zl
 * 
 * 3, Q odd
 *      ---------------
 *      |             |
 *     r1-----r2-----r3
 *     /       |      \
 *    a11     a12     a13
 *     |       |       |
 *    ...     ...     ...
 *     |       |       |
 *    ak1     ak2     ak3
 *   / | \   / | \   / | \
 *  x1...xn y1...ym z1...zl
 */

#include <bits/stdc++.h>

using namespace std;

const int N=100;
const int M=100;
const int P=5001;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int p, q, n, c[P], d[P], ci[P], cj[P], ck[P];
vii E;

void solve() {
    // 需要考虑边的限制
    // 初始化组件
    int t=(q&1)?((q-1)/2*3):(q/2*3-3);
    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=N-i; ++j) {
            for (int k=1; k<=N-i-j; ++k) {
                int pp=i*j*k, qq=i+j+k+t;
                if (pp>p || qq>M) continue;
                if (!c[pp] || c[pp]>qq) {
                    c[pp]=qq; ci[pp]=i; cj[pp]=j; ck[pp]=k;
                }
            }
        }
    }

    // 最优分解组件, dp推进时, c[i]的子状态c[j], c[i-j]未必有解
    for (int i=2; i<=p; ++i) {
        for (int j=1; (j<<1)<=i; ++j) {
            if (!c[j] || !c[i-j]) continue;
            if (!c[i] || c[i]>c[j]+c[i-j]) {
                c[i]=c[j]+c[i-j];
                d[i]=j;
            }
        }
    }

    int ri, rj, rk;

    // 输出
    queue<int> que;
    que.push(p);
    while (que.size()) {
        int t=que.front(); que.pop();
        if (d[t]) {
            que.push(d[t]); que.push(t-d[t]);
            continue;
        }

        if (q&1) {
            ri=++n; rj=++n; rk=++n;
            E.emplace_back(ri, rj);
            E.emplace_back(rj, rk);
            E.emplace_back(rk, ri);
        } else {
            ri=rj=rk=++n;
        }

        for (int i=1; i<q/2; ++i) {
            E.emplace_back(ri, ++n); ri=n;
            E.emplace_back(rj, ++n); rj=n;
            E.emplace_back(rk, ++n); rk=n;
        }

        for (int i=0; i<ci[t]; ++i) E.emplace_back(ri, ++n);
        for (int j=0; j<cj[t]; ++j) E.emplace_back(rj, ++n);
        for (int k=0; k<ck[t]; ++k) E.emplace_back(rk, ++n);
    }
}

void solve_2() {
    // 无需考虑边数限制, 尽量少的点的组件得到的三元, 边数自然是最少的,
    // 若不能满足边数限制, 该询问无解
    // 初始化组件
    for (int i=3, j=1; j<=p && i<=N; ++i, (j*=i)/=(i-3)) {
        c[j]=i;
    }

    // 最优分解组件
    for (int i=2; i<=p; ++i) {
        for (int j=1; (j<<1)<=i; ++j) {
            if (!c[i] || c[i]>c[j]+c[i-j]) {
                c[i]=c[j]+c[i-j];
                d[i]=j;
            }
        }
    }

    int r;

    // 输出
    queue<int> que;
    que.push(p);
    while (que.size()) {
        int t=que.front(); que.pop();
        if (d[t]) {
            que.push(d[t]); que.push(t-d[t]);
            continue;
        }

        r=++n;
        for (int i=0; i<c[t]; ++i) {
            E.emplace_back(r, ++n);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> p >> q;
    if (q==2) solve_2();
    else solve();

    cout << n << " " << E.size() << "\n";
    for (auto &e : E) {
        cout << e.first << " " << e.second << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
