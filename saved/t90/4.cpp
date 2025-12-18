#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

void solve() {
    int h, w;
    cin >> h >> w;
    vector<vector<int>> A(h, vector<int>(w));
    vector<int> tate(w);
    vector<int> yoko(h);
    rep(i, h) {
        rep(j, w) {
            int a;
            cin >> a;
            A[i][j] = a;
            tate[j] += a;
            yoko[i] += a;
        }
    }
    rep(i, h) {
        rep(j, w) {
            cout << tate[j] + yoko[i] - A[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int t = 1;
    //cin >> t;
    rep(i, t) solve();
}