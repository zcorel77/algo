/*
 * author: Corel
 *  email: zcorel@hotmail.com
 * 
 */

#include <bits/stdc++.h>

using namespace std;

typedef vector<pair<int, int>> vii;

const int N=4;
// Queen moves (8), Rook moves (first 4), Bishop moves (last 4)
const int xs[] = {1, -1, 0, 0, 1, 1, -1, -1}, ys[] = {0, 0, 1, -1, 1, -1, 1, -1};
// knight moves
const int xk[] = {1, -1, 2, -2, 1, -1, 2, -2}, yk[] = {2, 2, 1, 1, -2, -2, -1, -1};
// pown promotions
const int pros[] = {2, 3, 4};
const map<char, int> piece = {{'Q', 1}, {'R', 2}, {'B', 3}, {'N', 4}, {'P', 5}};

inline int sign(int x) { return (x==0)?0:((x<0)?-1:1); }
bool bwin(int);
bool wwin(int);

int g, w, b, m, board[N][N];

vii getMoves(int x, int y) {
    vii mvs;
    int s=0, e=8;
    if (abs(board[x][y])==2) {
        // Rook
        e=4;
    } else if (abs(board[x][y])==3) {
        // Bishop
        s=4;
    } else if (abs(board[x][y])==4) {
        // Knight
        int xx, yy;
        for (int i=0; i<8; i++) {
            xx=x+xk[i], yy=y+yk[i];
            if (xx>=0 && xx<N && yy>=0 && yy<N
                && sign(board[x][y])!=sign(board[xx][yy])) {
                    mvs.emplace_back(xx, yy);
            }
        }
        return mvs;
    } else if (abs(board[x][y])==5) {
        // Pawn
        int xx, yy;
        if (board[x][y]>0) {
            // White
            yy=y+1;
            if (yy<N && board[x][yy]==0) {
                mvs.emplace_back(x, yy);
            }
        } else {
            // Black
            yy=y-1;
            if (yy>=0 && board[x][yy]==0) {
                mvs.emplace_back(x, yy);
            }
        }
        xx=x+1;
        if (xx>=0 && xx<N && yy>=0 && yy<N
            && sign(board[x][y])==-sign(board[xx][yy])) {
            mvs.emplace_back(xx, yy);
        }
        xx=x-1;
        if (xx>=0 && xx<N && yy>=0 && yy<N
            && sign(board[x][y])==-sign(board[xx][yy])) {
            mvs.emplace_back(xx, yy);
        }
        return mvs;
    }

    int xx, yy, u, v;
    for (int k=s; k<e; k++) {
        u=xs[k], v=ys[k], xx = x+u, yy=y+v;
        while (xx>=0 && xx<N && yy>=0 && yy<N
                && sign(board[x][y])!=sign(board[xx][yy])) {
            mvs.emplace_back(xx, yy);
            if (board[xx][yy]!=0) break;
            xx+=u, yy+=v;
        }
    }
    return mvs;
}

bool bwin(int m) {
    if (m<=1) return false;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (board[i][j]>=0) continue;
            vii mvs = getMoves(i, j);
            for (auto &mv : mvs) {
                int o = board[i][j], d = board[mv.first][mv.second];
                if (d==1) return false;
                board[mv.first][mv.second]=o;
                board[i][j]=0;

                bool flag=wwin(m-1);
                // promotion
                if (flag && o==-5 && mv.second==0) {
                    for (auto &p : pros) {
                        board[mv.first][mv.second]=-p;
                        flag=wwin(m-1);
                        if (!flag) break;
                    }
                }

                board[i][j]=o;
                board[mv.first][mv.second]=d;
                if (!flag) return false;
            }
        }
    }
    return true;
}

bool wwin(int m) {
    if (m<=0) return false;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (board[i][j]<=0) continue;
            vii mvs = getMoves(i, j);
            for (auto &mv : mvs) {
                int o = board[i][j], d = board[mv.first][mv.second];
                if (d==-1) return true;
                board[mv.first][mv.second]=o;
                board[i][j]=0;

                bool flag=bwin(m-1);
                // promotion
                if (!flag && o==5 && mv.second==N-1) {
                    for (auto &p : pros) {
                        board[mv.first][mv.second]=p;
                        flag=bwin(m-1);
                        if (flag) break;
                    }
                }

                board[i][j]=o;
                board[mv.first][mv.second]=d;
                if (flag) return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    char p[2], c[2];
    int r;

    cin >> g;
    while (g--) {
        memset(board, 0, sizeof(int)*N*N);
        
        cin >> w >> b >> m;
        for (int i=0; i<w; ++i) {
            cin >> p >> c >> r;
            board[c[0]-'A'][r-1]=piece.at(p[0]);
        }

        for (int i=0; i<b; ++i) {
            cin >> p >> c >> r;
            board[c[0]-'A'][r-1]=-piece.at(p[0]);
        }

        cout << (wwin(m)?"YES":"NO") << "\n";
    }

    cout << "Time = " << double(clock()) / CLOCKS_PER_SEC << "\n";
    return 0;
}
