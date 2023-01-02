/*
author: Corel
email: zcorel@hotmail.com
*/

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

// brute
int solve(int a, int b, int x) {
    if (x==1) {
        return 0;
    }
    
    int m = (b>=0)?b:x;
    int ax = a%x;

    vi re;
    long l=1L;
    int i=0;
    for (; i<m; ++i) {
        l=(l*ax)%x;
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

// a*b%m=1
void extended_euclidean(int a, int b, int &x, int &y) {
    if (b==0) { x=1; y=0; return; }
    extended_euclidean(b, a%b, y, x);
    y -= a/b*x;
}

int power(int x, int y, int m) {
    if (m==1) {
        return 0;
    }

    if (y==0) return 1;

    if (y<0) {
        y=-y;

        int z;
        extended_euclidean(x, m, x, z);
        if (x<0) x+=m;
    }

    if (y==1) return x;
    
    long pp = power(x, y>>1, m);
    long ret = (pp*pp)%m;
    if (y&1) {
        ret = (ret*x)%m;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t, a, b, x;
    cin >> t;
    while (t--) {
        cin >> a >> b >> x;
        cout << power(a, b, x) << "\n";
    }

    // cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}