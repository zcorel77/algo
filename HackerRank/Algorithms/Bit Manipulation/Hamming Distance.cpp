/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 * 用{0,1}描述{a,b}字符串
 * [0,32),[32, 64)...
 * 每段字符串用一个int表示
 */

#include <bits/stdc++.h>

using namespace std;

const int N=5e4;
const int K=(N>>5)+5;
const int L=32;

int n, m;
uint a[K], b[K], c[K];
string s;

void fetch(uint *x, const uint *y, int l, int len) {
    int k=l/L, r=l%L;
    if (r) {
        for (int i=0; i<=len/L+1; ++i) {
            x[i]=(y[k+i]<<r)|(y[k+i+1]>>(L-r));
        }
    } else {
        memcpy(x, y+k, sizeof(int)*(len/L+1));
    }
}

void concat(uint *x, const uint *y, int l, int len) {
    int k=l/L, r=l%L;
    if (r) {
        uint z=(1<<(L-r))-1;
        (x[k]&=(~z))|=(y[0]>>r);
        for (int i=1; i<=len/L+1; ++i) {
            x[k+i]=(y[i-1]<<(L-r))|(y[i]>>r);
        }
    } else {
        memcpy(x+k, y, sizeof(uint)*(len/L+1));
    }
}

void copy(uint *x, const uint *y, int l, int len) {
    int k=l/L, r=l%L;
    if (r) {
        uint z=(1<<(L-r))-1;
        (x[k]&=(~z))|=(y[k]&z);
        ++k;
    }
    memcpy(x+k, y+k, sizeof(uint)*(len/L+1));
}

void flip(uint &x) {
    uint z=0;
    for (int j=0; j<L; ++j) {
        z<<=1;
        z|=x&1;
        x>>=1;
    }
    x=z;
}

void reverse(uint *x, int len) {
    int k=(len+L-1)/L, r=len%L;
    for (int i=0; i<k/2; ++i) {
        swap(x[i], x[k-i-1]);
        flip(x[i]);
        flip(x[k-i-1]);
    }
    if (k&1) flip(x[k/2]);

    if (r) {
        x[k]=0;
        for (int i=0; i<k; ++i) {
            (x[i]<<=(L-r))|=x[i+1]>>r;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    cin >> s;

    int k=0, r=n%L;
    for (int i=0; i<n; ++i) {
        if (i%L==0) ++k;
        (a[k-1]<<=1)|=(s[i]=='b');
    }

    for (int i=n; i%L; ++i) {
        a[k-1]<<=1;
    }

    char o[2], ch[2];
    int l1, l2, r1, r2, len, k11, k12, r11, r12;
    uint z1, z2;
    int ttt=0;
    cin >> m;
    while (m--) {
        cin >> o;
        if (o[0]=='C') {
            cin >> l1 >> r1 >> ch;
            --l1; --r1; ch[0]-='a';
            
            k11=l1/L; k12=r1/L;
            r11=l1%L; r12=r1%L;

            if (k11==k12) {
                z1=((1<<(r12-r11+1))-1)<<(L-r12-1);
                if (ch[0]) { a[k11]|=z1; }
                else { a[k11]&=(~z1); }
            } else {
                z1=(r11?(1<<(L-r11)):0)-1;
                z2=(1<<(L-r12-1))-1;

                if (ch[0]) { a[k11]|=z1; a[k12]|=(~z2); }
                else { a[k11]&=(~z1); a[k12]&=z2; }
                for (int i=k11+1; i<k12; ++i) a[i]=ch[0]?-1:0;
            }
        } else if (o[0]=='S') {
            cin >> l1 >> r1 >> l2 >> r2;
            --l1; --r1; --l2; --r2;

            copy(b, a, 0, l1);
            fetch(c, a, l2, r2-l2+1);
            concat(b, c, l1, r2-l2+1);
            fetch(c, a, r1+1, l2-r1-1);
            concat(b, c, l1+r2-l2+1, l2-r1-1);
            fetch(c, a, l1, r1-l1+1);
            concat(b, c, l1+r2-r1, r1-l1+1);
            copy(b, a, r2+1, n-r2-1);

            swap(a, b);
        } else if (o[0]=='R') {
            cin >> l1 >> r1;
            --l1; --r1;

            copy(b, a, 0, l1);
            fetch(c, a, l1, r1-l1+1);
            reverse(c, r1-l1+1);
            concat(b, c, l1, r1-l1+1);
            copy(b, a, r1+1, n-r1-1);

            swap(a, b);
        } else if (o[0]=='W') {
            cin >> l1 >> r1;
            --l1; --r1;

            fetch(c, a, l1, r1-l1+1);

            int k=(r1-l1+1)/L, r=(r1-l1+1)%L;
            for (int i=0; i<k; ++i) {
                for (int j=0; j<L; ++j) {
                    cout << (((c[i]>>(L-j-1))&1)?'b':'a');
                }
            }
            for (int j=0; j<r; ++j) {
                cout << (((c[k]>>(L-j-1))&1)?'b':'a');
            }
            cout << "\n";
            ++ttt;
        } else if (o[0]=='H') {
            cin >> l1 >> l2 >> len;
            --l1; --l2;

            fetch(b, a, l1, len);
            fetch(c, a, l2, len);

            int k=len/L, r=len%L, ans=0;
            for (int i=0; i<k; ++i) {
                ans+=__builtin_popcount(b[i]^c[i]);
            }
            if (r) {
                z1=(1<<(L-r))-1;
                ans+=__builtin_popcount((b[k]^c[k])&(~z1));
            }
            cout << ans << "\n";
            ++ttt;
        }
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
