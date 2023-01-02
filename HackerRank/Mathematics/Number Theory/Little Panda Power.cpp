/*
author: Corel
email: zcorel@hotmail.com
*/

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

int solve(int a, int b, int x) {
    if (x==1) {
        return 0;
    }
    
    int m = (b>=0)?b:x;
    int ax = a%x;

    vi re;
    long l = 1;
    int i = 0;
    for (; i<m; ++i) {
        l = (l*ax)%x;
        re.push_back(l);
        if (l==1) {
            break;
        }
    }
    if (i==b || i==0) {
        return l;
    }
    if (b>=0) {
        return re[(b+i)%(i+1)];
    } else {
        return re[((long)-b*i+i)%(i+1)];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t, a, b, x;
    cin >> t;
    while (t--) {
        cin >> a >> b >> x;
        cout << solve(a, b, x) << "\n";
    }

    // cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}