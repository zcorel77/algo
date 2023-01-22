/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 首先该任务肯定收敛, 不存在无解的情况
 * 如果不是原始数列且最小值为1, 则剩余次数为最大数
 * 检查下相邻数间距, 若存在1, 则剩余次数为最大数-最小数+1
 * 否则每轮, 求所有数的最大公约数, 每个数约去最大公约数
 *   如果有公约数, 最后的解就含这个公约数的因子, 除去这个公约数好判断
 * 另外, 每轮中遍历所有间隔时, 如果数组长度大于64的时候, 计数每个间隔,
 *   否则记录每个间隔
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+1;

int n, a[N], b[N];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i=0; i<n; ++i) cin >> a[i];

    sort(a, a+n);
    n=unique(a, a+n)-a;

    int ans=0;
    while (n) {
        if (n==1) {
            ++ans;
            break;
        }

        if (ans && a[0]==1) {
            ans+=a[n-1];
            break;
        }

        // 计算最小间隔, 判定是否退出循环, 有一定优化
        int min_interval=a[0];
        for (int i=1; i<n; ++i) {
            if ((min_interval=a[i]-a[i-1])==1) {
                break;
            }
        }
        if (min_interval==1) {
            ans+=a[n-1]-a[0]+1;
            break;
        }

        if (n>64) {
            fill_n(b, a[n-1]-a[0]+1, 0);
            for (int i=0; i<n; ++i) {
                for (int j=0; j<i; ++j) {
                    ++b[a[i]-a[j]];
                }
            }
            n=a[n-1]-a[0]+1;
            fill_n(a, n, 0);

            int j=0;
            for (int i=0; i<n; ++i) if (b[i]) a[j++]=i;
            n=j;
        } else {
            fill_n(b, n*n/2+1, 0);

            int k=0;
            for (int i=0; i<n; ++i) {
                for (int j=0; j<i; ++j) {
                    b[k++]=a[i]-a[j];
                }
            }
            swap(a, b);
            n=k;

            sort(a, a+n);
            n=unique(a, a+n)-a;
        }

        int g=0;
        for (int i=0; i<n; ++i) {
            if ((g=__gcd(g, a[i]))==1) break;
        }
        if (g>1) for (int i=0; i<n; ++i) a[i]/=g;

        ++ans;
    }

    cout << ans << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
