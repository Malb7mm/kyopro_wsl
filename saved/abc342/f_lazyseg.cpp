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
#define ansYN(x) cout << (x ? "Yes" : "No") << endl
#define cin1(a) a; cin >> a
#define cin2(a, b) a, b; cin >> a >> b
#define cin3(a, b, c) a, b, c; cin >> a >> b >> c
#define cin4(a, b, c, d) a, b, c, d; cin >> a >> b >> c >> d
#define cin_selector(_1, _2, _3, _4, NAME, ...) NAME
#define cin(...) cin_selector(__VA_ARGS__, cin4, cin3, cin2, cin1)(__VA_ARGS__)

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
#include <atcoder/lazysegtree>
//#include <atcoder/string>

#define MULTI_TESTCASES false
#define MODE 0 // -1: random test with naive(), 0: use solve(), 1: use naive()

#include <bits/stdc++.h>
using namespace std;

using S=double;
S op(S a, S b){
    return a+b;
}
S e(){
    return 0;
}
using F=double;
S mapping(F f, S s){
    return f+s;
}
F composition(F f, F g){
    return f+g;
}
F id(){
    return 0;
}

void solve() {
    ll cin(n);
    double cin(l);
    ll cin(d);
    lazy_segtree<S,op,e,F,mapping,composition,id> dp1(n+2);//dp1[i]:自分がiで止めたときのディーラーの勝率
    dp1.set(0,1);
    rep(i,l){
        auto val=dp1.get(i);
        auto lrover=[&](ll l, ll r, ll n){//閉区間[l,r]、インデックスの最大nから、r<nである新しい区間および>=nのカウントを返す
            auto left=l;
            auto right=r;
            auto rmax=n;
            auto overcnt=max(0LL,right-rmax);
            right=min(right,rmax);
            return make_tuple(left,right,overcnt);
        };
        auto [left,right,overcnt]=lrover(i+1,i+d,n+1);
        dp1.apply(left,right+1,val/d);
        dp1.apply(n+1,val/d*overcnt);
        dp1.set(i,0);
    }
    reprev(i,n){
        auto val=dp1.get(i)+dp1.get(i+1);
        dp1.set(i,val);
    }
    dp1.set(n+1,1);
    local{
        vector<double> vec;
        rep(i,n+2)vec.push_back(dp1.get(i));
        debug(vec);
    }
    lazy_segtree<S,op,e,F,mapping,composition,id> dp2(n+2);//dp2[i]:x=iのときの勝率
    dp2.set(n+1,0);//nを超えたら即負け
    dp2.set(n,1-dp1.get(n));//x=nのときの勝率
    reprev(i,n){
        double p_stop=1-dp1.get(i);//止めた場合の勝率
        auto left=i+1;
        auto right=i+d;
        auto rmax=n;
        auto overcnt=max(0LL,right-rmax);
        right=min(right,rmax);
        double p_cont=dp2.prod(left,right+1)/d;//サイコロを振った場合の勝率
        p_cont+=dp2.get(n+1)*overcnt/d;
        dp2.set(i,max(p_stop,p_cont));
    }
    local{
        vector<double> vec;
        rep(i,n+2)vec.push_back(dp2.get(i));
        debug(vec);
    }
    cout<<dp2.get(0)<<endl;
}

void naive() {
    
}

void next_case(CaseGenerator& cg) {
    auto n=cg.put_ll(2,10);
    cg.lb();
    rep(i,n){cg.put_ll(0,100);cg.put_ll(0,100);cg.lb();}
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