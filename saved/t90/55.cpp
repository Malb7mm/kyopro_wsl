// template references: https://qiita.com/sorachandu/items/041169d34b9f9b99bcf7

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
#define INF 1 << 29
#define rep2(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, x, n) for (int i = x; i < (int)(n); i++)
#define rep_selector(_1, _2, _3, NAME, ...) NAME
#define rep(...) rep_selector(__VA_ARGS__, rep3, rep2, rep1)(__VA_ARGS__)
#define all(x) x.begin(), x.end()
#define ansYN(x) cout << (x ? "Yes" : "No") << endl
#define cin1(a) a; cin >> a
#define cin2(a, b) a, b; cin >> a >> b
#define cin3(a, b, c) a, b, c; cin >> a >> b >> c
#define cin4(a, b, c, d) a, b, c, d; cin >> a >> b >> c >> d
#define cin_selector(_1, _2, _3, _4, NAME, ...) NAME
#define cin(...) cin_selector(__VA_ARGS__, cin4, cin3, cin2, cin1)(__VA_ARGS__)
#ifdef LOCAL
#define debug(x) debug_cerr(#x, x)
#else
#define debug(x) 
#endif

template<typename T1, typename T2> inline bool chmax(T1 &a, T2 b) {
    bool compare = a < b;
    if(compare) a = b;
    return compare;
}
template<typename T1, typename T2> inline bool chmin(T1 &a, T2 b) {
    bool compare = a > b;
    if(compare) a = b;
    return compare;
}

template <typename T>
concept Streamable = requires(std::ostream& os, T x) { os << x; };

template <typename T>
concept Container = std::ranges::range<T> && !Streamable<T>;;

void debug_cerr_vonly(Streamable auto value, int nest) {
    std::cerr << value;
}

void debug_cerr_vonly(Container auto value, int nest) {
    std::cerr << string(nest, ' ') << "{" << endl << string(nest + 1, ' ');
    bool first = true;
    for (const auto& v : value) {
        if (!first) std::cerr << ", ";
        debug_cerr_vonly(v, nest + 1);
        first = false;
    }
    std::cerr << endl << string(nest, ' ') << "}";
}

void debug_cerr(string name, auto value) {
    std::cerr << "# " << name << " = ";
    debug_cerr_vonly(value, 0);
    std::cerr << endl;
}

// *-*-*-*-*-*-*-*-*-*-*-* //
//            _            //
//  ___  ___ | |_   _____  //
// / __|/ _ \| \ \ / / _ \ //
// \__ \ (_) | |\ V /  __/ //
// |___/\___/|_| \_/ \___| //
//                         //
// *-*-*-*-*-*-*-*-*-*-*-* //

void solve() {
    int cin(n,p,q);
    vector<ll> A = {};
    rep(i,n){ll cin(a);A.push_back(a);}
    int cnt = 0;
    rep(i1,n)rep(i2,i1+1,n)rep(i3,i2+1,n)rep(i4,i3+1,n)rep(i5,i4+1,n){
        ll a = A[i1];
        a = a * A[i2] % p; 
        a = a * A[i3] % p; 
        a = a * A[i4] % p; 
        a = a * A[i5] % p;
        if(a==q)cnt++; 
    }
    cout<<cnt;
}

int main() {
    std::cerr << std::boolalpha;
    int t = 1;
    //cin >> t;
    rep(i, t) solve();
}