/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * state 记录所有在计算过程中遇到的数,及使用的因子
 * queue 挖掘所有因子
 */

#include <bits/stdc++.h>

using namespace std;

const int N=21;
const int K=21;

int n, k, a[N];
map<int, int> state;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    for (int i=0; i<k; ++i) {
        cin >> a[i];
    }
    sort(a, a+k, greater<int>());

    int x, y, z;

    queue<int> st;
    st.push(n);
    while (st.size()) {
        x=st.front();
        if (x==1) break;

        st.pop();
        for (int i=0; i<k; ++i) {
            y=x%a[i]; z=x/a[i];
            if (y==0 && state.find(z)==state.end()) {
                st.push(z);
                state.emplace(z, a[i]);
            }
        }
    }

    if (st.size()) {
        x=1;
        while (x<n) {
            cout << x << " ";
            x*=state[x]; 
        }
        cout << n << "\n";
    } else {
        cout << "-1\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
