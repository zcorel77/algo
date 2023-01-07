/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 预先计算每个字符的个数cnt[N], 除2得到目标串的每个字符的个数half[N]
 * 目标串生成过程中记录每个字符的个数ready[N]
 * 从n-1到0, 读取原串字符c, 依次处理, 
 * 若ready[c]已满足half[c], 则cnt[c]减一,
 * 否则, 判断是否替换目标串末尾字符d, 直至条件不满足, 条件为,
 *   c小于d, 且ready[d]+cnt[d]>half[d],
 *   也就是说替换掉d, d在后续过程还有足够的数量使之增长到half[d]
 * 将c添加到目标串末尾, ready[c]加一, cnt[c]减一
 */

#include <bits/stdc++.h>

using namespace std;

const int N=1e4+1;
const int C=26;

char s[N], ans[N];
int n, cnt[C], half[C], ready[C];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> s;
    n=strlen(s);

    for (int i=0; i<n; ++i) ++cnt[s[i]-'a'];
    for (int i=0; i<C; ++i) half[i] = cnt[i]/2;

    int c, tot=0;
    for (int i=n-1, j=n-1; i>=0; --i) {
        c=s[i]-'a';
        if (ready[c]==half[c]) { --cnt[c]; continue; }

        while (tot>0 && s[i]<ans[tot-1]
            && ready[ans[tot-1]-'a']+cnt[ans[tot-1]-'a']>half[ans[tot-1]-'a']) {
            --ready[ans[--tot]-'a'];
        }
        ans[tot++]=s[i];
        ++ready[c];
        --cnt[c];
    }
    ans[tot]='\0';

    cout << ans << "\n";

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
