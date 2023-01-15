/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 预先求[0, 2^k-1]区间的1的个数
 * 划分大于0的区间和小于0的区间,
 *   0<=a<=b [0,b]区间的1的个数-[0,a-1]区间的1的个数
 *   a<0<=b  [0,b]区间的1的个数+[a,0)区间的1的个数
 *   a<=b<0  [a,0)区间的1的个数-[b,0)区间的1的个数
 * 
 * 负数区间求1的个数,转化为所有位都为1的个数-反转为正数区间的1的个数
 * 不理解, HackerRank服务器为啥 (x+1)&(1<<31), x==2^31-1 不能取真
 * 特意实现一个case的分支 x==2^31-1
 */

#include <bits/stdc++.h>

using namespace std;

const int C=32;

int t, a, b;
long cnt[C];

long calc(int x) {
    long ans=0L;
    if (x==1<<(C-1)) {
        // x==-2^31
        ans=calc(x+1)+1L;
    } else if (x==(1L<<(C-1))-1) {
        // x==2^31-1
        ans=cnt[C-1];
    } else if (x>0) {
        for (int i=C-1; i>=0; --i) {
            int k=1<<i;
            if ((x+1)&k) {
                ans+=cnt[i]+((x+1)^k);
                x^=k;
            }
        }
    } else if (x<0) {
        x=-x;
        ans+=C*1L*x;
        ans-=calc(x-1);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // cnt[k], 1's in [0, 2^k-1]
    for (int i=1; i<C; ++i) {
        cnt[i]=(cnt[i-1]<<1)+(1L<<(i-1));
    }

    cin >> t;
    while (t--) {
        cin >> a >> b;

        long ans=0L;
        if (a>b) swap(a, b);
        if (b>0) {
            ans+=calc(b);
        } else if (b<0) {
            ans-=calc(b+1);
        }

        if (a>0) {
            ans-=calc(a-1);
        } else if (a<0) {
            ans+=calc(a);
        }

        cout << ans << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
