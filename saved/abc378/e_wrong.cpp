// template reference: https://qiita.com/sorachandu/items/041169d34b9f9b99bcf7

#include <bits/stdc++.h>
using namespace std;

#include <atcoder/modint>
using namespace atcoder;
using mint10 = modint1000000007;
using mint = modint998244353;

using ll = long long;
using ull = unsigned long long;
#define INF (1 << 30)
#define INFLL (1LL << 60)

#define walk2(dr, dc) for (auto [dr, dc] : vector<pair<int, int>>{{1, 0}, {0, 1}, {-1, 0}, {0, -1}})
#define walk3(dr, dc, i) for (auto [dr, dc, i] : vector<tuple<int, int, int>>{{1, 0, 0}, {0, 1, 1}, {-1, 0, 2}, {0, -1, 3}})
#define walk_selector(_1, _2, _3, NAME, ...) NAME
#define walk(...) walk_selector(__VA_ARGS__, walk3, walk2)(__VA_ARGS__)
#define within(l,v,r) (l <= v && v <= r)
#define rep2(i, n) for (ll i = 0; i < (ll)(n); i++)
#define rep3(i, x, n) for (ll i = (ll)(x); i < (ll)(n); i++)
#define rep_selector(_1, _2, _3, NAME, ...) NAME
#define rep(...) rep_selector(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define reprev2(i, n) for (ll i = (ll)(n)-1; i >= 0; i--)
#define reprev3(i, x, n) for (ll i = (ll)(n)-1; i >= (ll)(x); i--)
#define reprev_selector(_1, _2, _3, NAME, ...) NAME
#define reprev(...) reprev_selector(__VA_ARGS__, reprev3, reprev2)(__VA_ARGS__)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define ansYN(x) cout << (x ? "Yes" : "No") << endl
#define cin1(a) a; cin >> a
#define cin2(a, b) a, b; cin >> a >> b
#define cin3(a, b, c) a, b, c; cin >> a >> b >> c
#define cin4(a, b, c, d) a, b, c, d; cin >> a >> b >> c >> d
#define cin_selector(_1, _2, _3, _4, NAME, ...) NAME
#define cin(...) cin_selector(__VA_ARGS__, cin4, cin3, cin2, cin1)(__VA_ARGS__)
#define vec3(T, w1, init) vector<T>(w1, init)
#define vec4(T, w1, w2, init) vector<vector<T>>(w1, vec3(T, w2, init))
#define vec5(T, w1, w2, w3, init) vector<vector<vector<T>>>(w1, vec4(T, w2, w3, init))
#define vec6(T, w1, w2, w3, w4, init) vector<vector<vector<vector<T>>>>(w1, vec5(T, w2, w3, w4, init))
#define vec7(T, w1, w2, w3, w4, w5, init) vector<vector<vector<vector<vector<T>>>>>(w1, vec6(T, w2, w3, w4, w5, init))
#define vec8(T, w1, w2, w3, w4, w5, w6, init) vector<vector<vector<vector<vector<vector<T>>>>>>(w1, vec7(T, w2, w3, w4, w5, w6, init))
#define vec9(T, w1, w2, w3, w4, w5, w6, w7, init) vector<vector<vector<vector<vector<vector<vector<T>>>>>>>(w1, vec8(T, w2, w3, w4, w5, w6, w7, init))
#define vec10(T, w1, w2, w3, w4, w5, w6, w7, w8, init) vector<vector<vector<vector<vector<vector<vector<vector<T>>>>>>>>(w1, vec9(T, w2, w3, w4, w5, w6, w7, w8, init))
#define vec_selector(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME
#define vec(...) vec_selector(__VA_ARGS__, vec10, vec9, vec8, vec7, vec6, vec5, vec4, vec3)(__VA_ARGS__)

#ifdef LOCAL
#define debug1(x) debug_cerr(#x, x)
#define debug2(name, x) debug_cerr(name, x)
#define debug_selector(_1, _2, NAME, ...) NAME
#define debug(...) debug_selector(__VA_ARGS__, debug2, debug1)(__VA_ARGS__)
#define dmsg(x) cerr << "- " << x << endl;
#define local if constexpr (false) {} else
#else
#define debug(...) ;
#define dmsg(x) ;
#define local if constexpr (true) {} else 
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

template <typename T>
concept ValStreamable = requires(std::ostream& os, T x) { os << x.val(); };

template <typename T1,typename T2>
void debug_cerr_vonly(pair<T1,T2> value, int nest) {
    std::cerr << "[" << value.first << ", " << value.second << "]";
}

void debug_cerr_vonly(ValStreamable auto value, int nest) {
    std::cerr << value.val();
}

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

class Random {
public:
    mt19937_64 rnd;

    Random() {
        random_device seed_gen;
        rnd.seed(seed_gen());
    }
    ll gen_ll(ll min, ll max) {
        uniform_int_distribution<ll> dist(min, max);
        return dist(rnd);
    }
    string gen_str(string chars, int length) {
        ostringstream oss;
        int arrlen = chars.length();
        for (int i = 0; i < length; i++) {
            oss << chars[gen_ll(0, arrlen - 1)];
        }
        return oss.str();
    }
};

class CaseGenerator {
private:
    stringstream& ss;
public:
    Random random;

    CaseGenerator(stringstream& ss_in): ss(ss_in) {}

    void lb() {
        ss << "\n";
    }
    ll put_ll(ll min, ll max) {
        auto value = random.gen_ll(min, max);
        ss << value << " ";
        return value;
    }
    string put_str(string chars, int length) {
        auto value = random.gen_str(chars, length);
        ss << value << " ";
        return value;
    }
    string put_str(string chars, int length, function<bool(string)> check) {
        string value;
        do {
            value = random.gen_str(chars, length);
        } while(!check(value));
        ss << value << " ";
        return value;
    }
};

// *-*-*-*-*-*-*-*-*-*-*-* //
//            _            //
//  ___  ___ | |_   _____  //
// / __|/ _ \| \ \ / / _ \ //
// \__ \ (_) | |\ V /  __/ //
// |___/\___/|_| \_/ \___| //
//                         //
// *-*-*-*-*-*-*-*-*-*-*-* //

//#include <atcoder/dsu>
//#include <atcoder/segtree>
//#include <atcoder/lazysegtree>
//#include <atcoder/string>

#define MULTI_TESTCASES false
#define MODE 0 // -1: random test with naive(), 0: use solve(), 1: use naive()

void solve() {
    int cin(n,m);
    vector<ll> A;
    rep(i,n){ll cin(a);A.push_back(a);}
    // 累積和をとる
    vector<ll> B={0};
    rep(i,n){B.push_back(B[i]+A[i]%m);}
    ll ans=0;
    debug(B);
    rep(i,0,n){
        ans+=(-B[i])%m*(n-i);
        dmsg(format("i={},ans+={}",i,(-B[i])%m*(n-i)));
        dmsg(format("-B[{}] * {}",i,n-i));
    }
    rep(i,1,n+1){
        ans+=B[i]%m*i;
        dmsg(format("i={},ans+={}",i,(B[i])%m*i));
        dmsg(format("B[{}] * {}",i,i));
    }
    cout<<ans<<endl;
}

void naive() {
    int cin(n,m);
    vector<ll> A={0};
    rep(i,n){ll cin(a);A.push_back(a);}
    ll ans=0;
    rep(l,1,n+1)rep(r,l,n+1){
        ll sum=0;
        rep(i,l,r+1){sum+=A[i];}
        sum%=m;
        dmsg(format("l={},r={},sum={}",l,r,sum));
        ans+=sum;
    }
    cout<<ans<<endl;
}

void next_case(CaseGenerator& cg) {
    auto n=cg.put_ll(2,10);
    cg.put_ll(1,10);
    cg.lb();
    rep(i,n){
        cg.put_ll(0,10);
    }
}

int main() {
    cerr << boolalpha << fixed << setprecision(15);
    cout << fixed << setprecision(15);
    if (MODE >= 0) { 
        int t = 1;
        if (MULTI_TESTCASES) cin >> t;
        rep(i, t) {
            if (MODE == 0) solve();
            if (MODE == 1) naive();
        }
    }
    // random test with naive()
    else if (MODE == -1) {
        string discarded_input;
        stringstream dummy_cerr;
        cerr.rdbuf(dummy_cerr.rdbuf());

        auto cin_rdbuf = cin.rdbuf();
        auto cout_rdbuf = cout.rdbuf();
        istream std_in(cin_rdbuf);
        ostream std_out(cout_rdbuf);
        stringstream ss_in;
        stringstream ss_out;
        cin.rdbuf(ss_in.rdbuf());
        cout.rdbuf(ss_out.rdbuf());

        stringstream ss_gen;
        CaseGenerator cg(ss_gen);

        auto clear_ss = [&](stringstream& ss){
            ss.str("");
            ss.clear(std::stringstream::goodbit);
        };

        auto read_ss = [&](stringstream& ss){
            auto result = ss.str();
            clear_ss(ss);
            return result;
        };

        auto generate = [&]{
            next_case(cg);
            ss_gen << endl;
            return read_ss(ss_gen);
        };

        std_out << "- Example of Generated Case:" << endl;
        std_out << generate() << endl;

        stringstream ans_solve_ss;
        stringstream ans_naive_ss;
        string ans_solve;
        string ans_naive;

        int i_target = 1;
        for (int i = 1;; i++) {
            auto testcase = generate();

            ss_in << testcase;
            solve();
            ans_solve_ss << read_ss(ss_out);
            ans_solve = ans_solve_ss.str();
            clear_ss(ss_in);

            ss_in << testcase;
            naive();
            ans_naive_ss << read_ss(ss_out);
            ans_naive = ans_naive_ss.str();
            clear_ss(ss_in);

            bool pass;
            while (true) {
                string s_solve, s_naive;
                ans_solve_ss >> s_solve;
                ans_naive_ss >> s_naive;
                if (s_solve != s_naive) {
                    pass = false;
                    break;
                }
                if (ans_solve_ss.eof() && ans_naive_ss.eof()) {
                    pass = true;
                    break;
                }
                else if (ans_solve_ss.eof() || ans_naive_ss.eof()) {
                    pass = false;
                    break;
                }
            }

            clear_ss(ans_solve_ss);
            clear_ss(ans_naive_ss);
            if (!pass) {
                std_out << "! Counterexample has Found:" << endl;
                std_out << testcase << endl;
                std_out << "- Answer of solve():" << endl;
                std_out << ans_solve << endl;
                std_out << "- Answer of naive():" << endl;
                std_out << ans_naive << endl;

                std_in >> discarded_input;
                std_out << endl;
                i--;
                continue;
            }

            if (i == i_target) {
                std_out << "- " << i << " Cases Passed" << endl << endl;
                i_target *= 2;
            }
        }
    }
}

// solve() is around line 170