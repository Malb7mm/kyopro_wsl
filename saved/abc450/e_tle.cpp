// solve() is around line 630

//for library checker/yukicoder
//#define ATCODER 1

#include <bits/stdc++.h>
using namespace std;

//https://github.com/atcoder/ac-library/blob/864245a00b00dd008d1abfdc239618fdb7d139da/atcoder/dsu.hpp
#ifndef ATCODER_DSU_HPP
#define ATCODER_DSU_HPP 1
namespace atcoder {struct dsu {public:dsu() : _n(0) {}explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}int merge(int a, int b) {assert(0 <= a && a < _n);assert(0 <= b && b < _n);int x = leader(a), y = leader(b);if (x == y) return x;if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);parent_or_size[x] += parent_or_size[y];parent_or_size[y] = x;return x;}bool same(int a, int b) {assert(0 <= a && a < _n);assert(0 <= b && b < _n);return leader(a) == leader(b);}int leader(int a) {assert(0 <= a && a < _n);return _leader(a);}int size(int a) {assert(0 <= a && a < _n);return -parent_or_size[leader(a)];}std::vector<std::vector<int>> groups() {std::vector<int> leader_buf(_n), group_size(_n);for (int i = 0; i < _n; i++) {leader_buf[i] = leader(i);group_size[leader_buf[i]]++;}std::vector<std::vector<int>> result(_n);for (int i = 0; i < _n; i++) {result[i].reserve(group_size[i]);}for (int i = 0; i < _n; i++) {result[leader_buf[i]].push_back(i);}result.erase(std::remove_if(result.begin(), result.end(),[&](const std::vector<int>& v) { return v.empty(); }),result.end());return result;}private:int _n;std::vector<int> parent_or_size;int _leader(int a) {if (parent_or_size[a] < 0) return a;return parent_or_size[a] = _leader(parent_or_size[a]);}};}
#endif  // ATCODER_DSU_HPP

namespace atcoder {}
using namespace atcoder;
#ifdef ATCODER
#include <atcoder/fenwicktree>
#include <atcoder/segtree>
#include <atcoder/lazysegtree>
#include <atcoder/convolution>
#include <atcoder/math>
#include <atcoder/modint>
#include <atcoder/string>
#include <atcoder/scc>
#include <atcoder/mincostflow>
using mint10 = modint1000000007;
using mint = modint998244353;
#endif

using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t;
using ui128 = __uint128_t;
using pll = pair<ll,ll>;
using pil = pair<int,ll>;
using tll3 = tuple<ll,ll,ll>;
using tll4 = tuple<ll,ll,ll,ll>;
using tll5 = tuple<ll,ll,ll,ll,ll>;
using tll6 = tuple<ll,ll,ll,ll,ll,ll>;
using vll = vector<ll>;
using vpll = vector<pll>;
using vtll3 = vector<tll3>;
using vtll4 = vector<tll4>;
using vtll5 = vector<tll5>;
using vtll6 = vector<tll6>;
using vi128 = vector<i128>;
using sll = set<ll>;
using vstr = vector<string>;
using vvll = vector<vector<ll>>;
using vvint = vector<vector<int>>;
using vvpll = vector<vector<pll>>;
using vvpil = vector<vector<pil>>;
constexpr int INF = 1 << 30;
constexpr ll INFL = 1LL << 48;
constexpr ll INFLL = 1LL << 62;
constexpr ll LL18 = 1000000000000000000LL;
constexpr ll LL9 = 1000000000LL;
constexpr char el = '\n';
constexpr char sp = ' ';

#define walk2(dr, dc) for (auto [dr, dc] : vector<pair<int, int>>{{1, 0}, {0, 1}, {-1, 0}, {0, -1}})
#define walk3(dr, dc, i) for (auto [dr, dc, i] : vector<tuple<int, int, int>>{{1, 0, 0}, {0, 1, 1}, {-1, 0, 2}, {0, -1, 3}})
#define walk_selector(_1, _2, _3, NAME, ...) NAME
#define walk(...) walk_selector(__VA_ARGS__, walk3, walk2)(__VA_ARGS__)
#define walkx(dr, dc) for (auto [dr, dc] : vector<pair<int, int>>{{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}})
#define within(l,v,r) (l <= v && v <= r)
#define rep2(i, n) for (ll i = 0; i < (ll)(n); i++)
#define rep3(i, x, n) for (ll i = (ll)(x); i < (ll)(n); i++)
#define rep4(i, x, n, s) for (ll i = (ll)(x); i < (ll)(n); i += s)
#define rep_selector(_1, _2, _3, _4, NAME, ...) NAME
#define rep(...) rep_selector(__VA_ARGS__, rep4, rep3, rep2)(__VA_ARGS__)
#define reprev2(i, n) for (ll i = (ll)(n)-1; i >= 0; i--)
#define reprev3(i, x, n) for (ll i = (ll)(n)-1; i >= (ll)(x); i--)
#define reprev4(i, x, n, s) for (ll i = (ll)(n)-1; i >= (ll)(x); i -= s)
#define reprev_selector(_1, _2, _3, _4, NAME, ...) NAME
#define reprev(...) reprev_selector(__VA_ARGS__, reprev4, reprev3, reprev2)(__VA_ARGS__)
#define repsubset(i, s) for (ll i = (ll)(s); i >= 0; i--, i &= (i >= 0 ? s : i))
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define ansyn(x) cout << (x ? "yes" : "no") << endl
#define ansYn(x) cout << (x ? "Yes" : "No") << endl
#define ansYN(x) cout << (x ? "YES" : "NO") << endl
#define cin1(a) a; cin >> a
#define cin2(a, b) a, b; cin >> a >> b
#define cin3(a, b, c) a, b, c; cin >> a >> b >> c
#define cin4(a, b, c, d) a, b, c, d; cin >> a >> b >> c >> d
#define cin5(a, b, c, d, e) a, b, c, d, e; cin >> a >> b >> c >> d >> e
#define cin6(a, b, c, d, e, f) a, b, c, d, e, f; cin >> a >> b >> c >> d >> e >> f
#define cin7(a, b, c, d, e, f, g) a, b, c, d, e, f, g; cin >> a >> b >> c >> d >> e >> f >> g
#define cin8(a, b, c, d, e, f, g, h) a, b, c, d, e, f, g, h; cin >> a >> b >> c >> d >> e >> f >> g >> h
#define cin_selector(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME
#define cin(...) cin_selector(__VA_ARGS__, cin8, cin7, cin6, cin5, cin4, cin3, cin2, cin1)(__VA_ARGS__)

#ifdef LOCAL
#define debug1(x) debug_cerr(#x, x)
#define debug2(name, x) debug_cerr(name, x)
#define debug_selector(_1, _2, NAME, ...) NAME
#define debug(...) debug_selector(__VA_ARGS__, debug2, debug1)(__VA_ARGS__)
#define debugs(...) debug_cerr(#__VA_ARGS__, make_tuple(__VA_ARGS__))
#define debugsn(name, ...) debug_cerr(name, make_tuple(__VA_ARGS__))
#define dmsg(x) cerr << "- " << x << endl;
#define local if constexpr (false) {} else
#else
#define debug(...) ;
#define debugs(...) ;
#define debugsn(...) ;
#define dmsg(x) ;
#define local if constexpr (true) {} else 
#define LOCAL 0
#endif
#ifndef CPHEXT
#define CPHEXT 0
#endif
#ifndef MODE
#define MODE 0 // -2: test(check) -1: test(naive) 0:solve 1:naive 2:check 3:next_case 4:jikken
#endif
#ifndef SHOW_EVERY_TESTCASES
#define SHOW_EVERY_TESTCASES false
#endif
#ifndef SHOW_CERR
#define SHOW_CERR false
#endif

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
using namespace __gnu_pbds;
template <typename T,typename comp=less<T>>
using indexed_set = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T,typename T2>
using pqueue = priority_queue<T,vector<T>,T2>;

template<typename T, typename... Args>
auto Vec(T init, int n, Args... args) {
    if constexpr (sizeof...(args) == 0) {
        return std::vector<T>(n, init);
    } else {
        return std::vector(n, Vec<T>(init, args...));
    }
}

std::ostream& operator<<(std::ostream& os, __uint128_t n) {
    if (n == 0) return os << "0";
    std::string s;
    while (n > 0) {
        s += (char)('0' + (n % 10));
        n /= 10;
    }
    std::reverse(s.begin(), s.end());
    return os << s;
}
std::istream& operator>>(std::istream& is, __int128_t& n) {
    std::string s;
    is >> s;
    n = 0;
    bool neg = false;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '-') neg = true;
        else n = n * 10 + (s[i] - '0');
    }
    if (neg) n = -n;
    return is;
}
std::istream& operator>>(std::istream& is, __uint128_t& n) {
    std::string s;
    is >> s;
    n = 0;
    for (size_t i = 0; i < s.size(); i++) {
        n = n * 10 + (s[i] - '0');
    }
    return is;
}
std::ostream& operator<<(std::ostream& os, __int128_t n) {
    if (n == 0) return os << "0";
    if (n < 0) {
        os << "-";
        n = -n;
    }
    return os << (__uint128_t)n;
}
template <typename T1, typename T2>
istream& operator>>(istream& is, pair<T1, T2>& p) {
    is >> p.first >> p.second;
    return is;
}
template <typename... Args>
istream& operator>>(istream& is, tuple<Args...>& t) {
    apply([&is](auto&... args) {
        ((is >> args), ...);
    }, t);
    return is;
}
template <typename T>
istream& operator>>(istream& is, vector<T>& v) {
    for (T& in : v) {
        is >> in;
    }
    return is;
}

template<typename T>
inline T div_ceil(T a, T b) {
    return (a + b - 1) / b;
}

template<typename T, typename... Args> 
inline bool chmax(T &ref, Args&&... args) {
    auto old = ref;
    ref = std::max({ref, (T)args...});
    return old != ref;
}
template<typename T, typename... Args> 
inline bool chmin(T &ref, Args&&... args) {
    auto old = ref;
    ref = std::min({ref, (T)args...});
    return old != ref;
}
template<typename T>
inline bool chclamp(T& val, T minv, T maxv) {
    auto old_val = val;
    val = max(minv, min(maxv, val));
    return old_val != val;
}

template<typename T, typename... Args>
inline T set1(T &val, Args&&... bits) {
    return (val | ... | (1LL<<bits));
}
template<typename T, typename... Args>
inline T set0(T &val, Args&&... bits) {
    return (val & ... & ~(1LL<<bits));
}
template<typename T, typename... Args>
inline T flip(T &val, Args&&... bits) {
    return (val ^ ... ^ (1LL<<bits));
}
template<typename T, typename... Args>
inline bool isset(T &val, Args&&... bits) {
    return (... && (bool)(val & (1LL<<bits)));
}
template<typename T, typename... Args>
inline bool isset_any(T &val, Args&&... bits) {
    return (... || (bool)(val & (1LL<<bits)));
}
template<typename T, typename... Args>
inline bool isnset(T &val, Args&&... bits) {
    return (... && !(bool)(val & (1LL<<bits)));
}
template<typename T, typename... Args>
inline bool isnset_any(T &val, Args&&... bits) {
    return (... || !(bool)(val & (1LL<<bits)));
}

template <typename F>
inline long long nibutan(long long ok, long long ng, F f) {
    while (std::abs(ok - ng) > 1) {
        auto mid = std::min(ok, ng) + std::abs(ok - ng) / 2;
        if (f(mid)) ok = mid;
        else ng = mid;
    }
    return ok;
}

template <int... Is>
struct CustomComp {
    template <typename T>
    bool operator()(const T& lhs, const T& rhs) const {
        bool result = false;
        bool found = false;
        ((
            [&]() {
                if (found) return;
                constexpr int idx = (Is > 0 ? Is : -Is) - 1;
                auto&& val_l = std::get<idx>(lhs);
                auto&& val_r = std::get<idx>(rhs);
                if (Is > 0) {
                    if (val_l < val_r) { result = true; found = true; }
                    else if (val_r < val_l) { result = false; found = true; }
                } else {
                    if (val_r < val_l) { result = true; found = true; }
                    else if (val_l < val_r) { result = false; found = true; }
                }
            }()
        ), ...);
        return result;
    }
};
// 正のとき l<r でtrue
// ソート:正=昇順
// 優先度付きキュー:負=昇順
template <int... Is>
constexpr CustomComp<Is...> comp;
// 正のとき l<r でtrue
// ソート:正=昇順
// 優先度付きキュー:負=昇順
template <int... Is>
using Comp = decltype(comp<Is...>);

void multicases(function<void()> f) {
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        f();
    }
}

template <typename T>
concept Streamable = requires(std::ostream& os, T x) { os << x; };

template <typename T>
concept Container = std::ranges::range<T> && !Streamable<T>;

template <typename T>
concept ValStreamable = requires(std::ostream& os, T x) { os << x.val(); };

#ifdef ATCODER
template <typename T> struct is_acl_segtree : std::false_type {};
template <class S, auto op, auto e>
struct is_acl_segtree<atcoder::segtree<S, op, e>> : std::true_type {};

template <typename T> struct is_acl_lazy_segtree : std::false_type {};
template <class S, auto op, auto e, class F, auto m, auto c, auto id>
struct is_acl_lazy_segtree<atcoder::lazy_segtree<S, op, e, F, m, c, id>> : std::true_type {};
#endif

struct DebugImpl {
    template <typename T>
    static void run(const T& value, int nest) {
        if constexpr (ValStreamable<T>) {
            run(value.val(), nest);
        }
        else if constexpr (Streamable<T>) {
            if constexpr (std::is_unsigned_v<T>) {
                if      (value >=  INFL)  std::cerr << "INF";
                else if (value ==  INF)   std::cerr << "inf";
                else std::cerr << value;
            }
            else if constexpr (std::is_integral_v<T>) {
                if      (value >=  INFL)  std::cerr << "INF";
                else if (value <= -INFL)  std::cerr << "-INF";
                else if (value ==  INF)   std::cerr << "inf";
                else if (value == -INF)   std::cerr << "-inf";
                else std::cerr << value;
            }
            else std::cerr << value;
        }
        else if constexpr (Container<T>) {
            std::cerr << std::string(nest, ' ') << "{" << endl << std::string(nest + 1, ' ');
            bool first = true;
            for (const auto& v : value) {
                if (!first) std::cerr << ", ";
                run(v, nest + 1);
                first = false;
            }
            std::cerr << endl << std::string(nest, ' ') << "}";
        }
#ifdef ATCODER
        else if constexpr (is_acl_segtree<T>::value || is_acl_lazy_segtree<T>::value) {
            auto& nc_value = const_cast<T&>(value);
            int n = nc_value.max_right(0, [](auto){ return true; });
            
            std::cerr << std::string(nest, ' ') << "{";
            for (int i = 0; i < n; i++) {
                if (i > 0) std::cerr << ", ";
                run(nc_value.get(i), nest + 1);
            }
            std::cerr << "}";
        }
#endif
        else {
            handle_tuple_or_pair(value, nest);
        }
    }

    template <typename T>
    static void handle_tuple_or_pair(const T& value, int nest) {
        if constexpr (requires { typename tuple_size<T>::type; } && !Container<T>) {
             std::cerr << "[";
             std::apply([&](const auto&... args) {
                 size_t n = 0;
                 ((std::cerr << (n++ == 0 ? "" : ", "), run(args, nest)), ...);
             }, value);
             std::cerr << "]";
        }
        else {
            std::cerr << "?";
        }
    }
};

void debug_cerr_vonly(auto const& value, int nest) {
    DebugImpl::run(value, nest);
}

void debug_cerr(std::string name, auto value) {
    std::cerr << "# " << name << " = ";
    debug_cerr_vonly(value, 0);
    std::cerr << endl;
}

template<class T>
struct shifted_vector : std::vector<T> {
    int origin;
    shifted_vector(int l, int r) : std::vector<T>(r - l + 1), origin(-l) {}
    T& operator[](int i) { return std::vector<T>::at(i + origin); }
};

namespace ahc {
    std::chrono::system_clock::time_point now() {
        return std::chrono::system_clock::now();
    }

    double elapsed(std::chrono::system_clock::time_point start) {
        auto now = ahc::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
    }

    unsigned int rand() {
        static unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
        unsigned int t = x ^ (x << 11);
        x = y; y = z; z = w;
        return w = ((w ^ (w >> 19)) ^ (t ^ (t >> 8)));
    }

    bool sa_min(long long prev_score, long long new_score, double current_time, double end_time, double start_temp, double end_temp) {
        if (new_score < prev_score) return true;
        double progress = current_time / end_time;
        if (progress >= 1.0) progress = 1.0;
        double temp = start_temp + (end_temp - start_temp) * progress;
        if (temp <= 1e-9) return false;
        double delta = (double)(new_score - prev_score);
        double prob = std::exp(-delta / temp);
        double p = (double)(rand() % 100000) / 100000;
        return p < prob;
    }

    bool sa_max(long long prev_score, long long new_score, double current_time, double end_time, double start_temp, double end_temp) {
        return sa_min(-prev_score, -new_score, current_time, end_time, start_temp, end_temp);
    }
}

class Random {
public:
    std::mt19937_64 engine;

    Random() {
        std::random_device seed_gen;
        engine.seed(seed_gen());
    }
    long long gen_ll(long long min, long long max) {
        std::uniform_int_distribution<long long> dist(min, max);
        return dist(engine);
    }
    std::string gen_str(std::string chars, int length) {
        std::ostringstream oss;
        int arrlen = chars.length();
        for (int i = 0; i < length; i++) {
            oss << chars[gen_ll(0, arrlen - 1)];
        }
        return oss.str();
    }
};

class GraphGenerator {
    Random random;
    std::stringstream& ss;
public:
    std::map<long long, std::vector<long long>> graph;
    std::set<std::pair<long long, long long>> edges;
    std::set<std::pair<long long, long long>> unique_edges;
    atcoder::dsu uf;
    //デフォルトは単純無向グラフ
    bool loop = false;
    bool multigraph = false;
    bool directed = false;
    bool cycle = true;
    bool connected = true;

    GraphGenerator(std::stringstream& ss_in): ss(ss_in) {}

    long long build_tree(long long n_min, long long n_max) {
        assert(n_min >= 2);
        assert(n_max >= 2);
        assert(n_max >= n_min);

        auto loop = false, multigraph = false, directed = false, cycle = false;
        std::swap(this->loop, loop);
        std::swap(this->multigraph, multigraph);
        std::swap(this->directed, directed);
        std::swap(this->cycle, cycle);

        long long n, m;
        do {
            n = random.gen_ll(n_min, n_max);
            m = n - 1;
        } while (!try_build(n, m));

        std::swap(this->loop, loop);
        std::swap(this->multigraph, multigraph);
        std::swap(this->directed, directed);
        std::swap(this->cycle, cycle);
        return n;
    }

    long long build_tree(long long n_max) {
        return build_tree(2, n_max);
    }

    pair<long long, long long> build(long long n_min, long long n_max, long long m_min, long long m_max) {
        assert(n_min >= 2);
        assert(n_max >= 2);
        assert(n_max >= n_min);
        assert(m_min >= 1);
        assert(m_max >= 1);
        assert(m_max >= m_min);

        long long n, m;
        do {
            n = random.gen_ll(n_min, n_max);
            m = random.gen_ll(m_min, m_max);
        } while (!try_build(n, m));
        return {n, m};
    }

    pair<long long, long long> build(long long n_max, long long m_max) {
        return build(2, n_max, 1, m_max);
    }

    bool try_build(long long n, long long m) {
        std::vector<long long> nodes(n);
        std::iota(nodes.begin(), nodes.end(), 1);
        for (int i = n; i < 2 * m; i++) {
            auto node = random.gen_ll(1, n);
            nodes.push_back(node);
        }
        std::ranges::shuffle(nodes, random.engine);

        bool success = true;
        graph.clear();
        edges.clear();
        unique_edges.clear();
        uf = atcoder::dsu(n+1);

        for (int i = 0; i < 2 * m; i += 2) {
            auto u = nodes[i];
            auto v = nodes[i + 1];

            if (!loop && u == v) { success = false; break; }
            if (!multigraph && edges.contains({u, v})) { success = false; break; }
            if (!cycle && !directed && uf.same(u, v)) { success = false; break; }

            graph[u].push_back(v);
            edges.insert({u, v});
            unique_edges.insert({u, v});
            if (!directed) {
                graph[v].push_back(u);
                edges.insert({v, u});
            }
            uf.merge(u, v);
        }
        if (!success) return false;

        if (connected) {
            for (int i = 2; i <= n; i++) {
                if (!uf.same(1, i)) return false;
            }
        }

        if (!cycle && directed) {
            set<ll> seen, finished;

            function<bool(int)> dfs = [&](int u){
                seen.insert(u);
                for (auto v : graph[u]) {
                    if (finished.contains(v)) continue;
                    if (seen.contains(v) && !finished.contains(v)) return true;
                    if (dfs(v)) return true;
                }
                finished.insert(u);
                return false;
            };

            for (int i = 1; i <= n; i++) {
                if (!finished.contains(i) && dfs(i)) { success = false; break; }
            }
        }
        return success;
    }

    void put_edges(function<void()> after = NULL) {
        auto itr = unique_edges.begin();

        while (itr != unique_edges.end()) {
            if (itr != unique_edges.begin()) ss << endl;
            auto [u, v] = *itr;

            ss << u << " " << v << " ";
            if (after != NULL) after();
            itr++;
        }
    }
};

class CaseGenerator {
    std::stringstream& ss;
public:
    Random random;

    CaseGenerator(std::stringstream& ss_in): ss(ss_in) {}

    void lb() {
        ss << endl;
    }
    template <typename T>
    void put(T value) {
        ss << value << " ";
    }
    long long put_ll(long long min, long long max) {
        auto value = random.gen_ll(min, max);
        ss << value << " ";
        return value;
    }
    long long put_ll(long long min, long long max, function<bool(long long)> check) {
        long long value;
        do {
            value = random.gen_ll(min, max);
        } while (!check(value));
        ss << value << " ";
        return value;
    }
    std::string put_str(std::string chars, int length) {
        auto value = random.gen_str(chars, length);
        ss << value << " ";
        return value;
    }
    std::string put_str(std::string chars, int length, function<bool(std::string)> check) {
        std::string value;
        do {
            value = random.gen_str(chars, length);
        } while (!check(value));
        ss << value << " ";
        return value;
    }
    GraphGenerator make_graph() {
        return GraphGenerator(ss);
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

//#pragma GCC target("avx")
//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

//https://qiita.com/hamamu/items/4d081751b69aa3bb3557#comment-09da436b204261f1624d
namespace mystd{
    template<class T> size_t HashCombine(const size_t seed,const T &v){
       return seed^(std::hash<T>()(v)+0x9e3779b9+(seed<<6)+(seed>>2));
    }
    template<typename T>
    struct hash{
        size_t operator()(const T& keyval) const noexcept {
            return std::hash<T>()(keyval);
        }
    };
    /* pair用 */
    template<class T,class S>
    struct hash<std::pair<T,S>>{
        size_t operator()(const std::pair<T,S> &keyval) const noexcept {
            return HashCombine(std::hash<T>()(keyval.first), keyval.second);
        }
    };
    /* vector用 */
    template<class T>
    struct hash<std::vector<T>>{
        size_t operator()(const std::vector<T> &keyval) const noexcept {
            size_t s=0;
            for (auto&& v: keyval) s=HashCombine(s,v);
            return s;
        }
    };
    /* tuple用 */
    template<int N>
    struct HashTupleCore{
        template<class Tuple> size_t operator()(const Tuple &keyval) const noexcept{
            size_t s=HashTupleCore<N-1>()(keyval);
            return HashCombine(s,std::get<N-1>(keyval));
        }
    };
    template <> struct HashTupleCore<0>{
        template<class Tuple> size_t operator()(const Tuple &keyval) const noexcept{ return 0; }
    };
    template<class... Args>
    struct hash<std::tuple<Args...>>{
        size_t operator()(const std::tuple<Args...> &keyval) const noexcept {
            return HashTupleCore<std::tuple_size<std::tuple<Args...>>::value>()(keyval);
        }
    };
    template<typename K, typename T>
    using unordered_map = std::unordered_map<K,T,hash<K>>;
    template<typename K>
    using unordered_set = std::unordered_set<K,hash<K>>;
}

// 1:x
// 2:O
// 3:Ox
// 4:OxO
// 5:OxO|Ox
// 6:OxOOx|OxO
// 7:OxOOxOxO|OxOOx
// 8:OXOOxOxOOxOOx|OxOOxOxO
// 9:OXOOxOxOOxOOxOxOOxOxO|OxOOxOxOOxOOx
// 文字列の前半部分がコピーされていく
// あまりをとって再帰にできそう
// 何文字あるか！？！？
// これ再帰だとぜんぜん間に合わないっぽい
void solve() {
    string cin(x,y);
    ll cin(q);
    auto start=ahc::now();
    i128 lx=x.length(),ly=y.length();
    vi128 Fib={lx,ly};
    {
        i128 val=lx+ly;
        while(true){
            if(val>=INFLL)break;
            Fib.push_back(val);
            val=Fib[Fib.size()-1]+Fib[Fib.size()-2];
        }
    }
    //debug(Fib);
    string s=y+x;
    ll ls=lx+ly;
    vvll charcnts(26);
    rep(i,26){
        char c='a'+i;
        vll V(ls);
        ll cnt=0;
        rep(j,ls){
            if(c==s[j])cnt++;
            V[j]=cnt;
        }
        charcnts[i]=V;
    }
    mystd::unordered_map<pair<i128,char>,ll> memo;
    ll callcnt=0;
    function<ll(i128,char)> calc=[&](i128 i,char c){
        callcnt++;
        if(i<0)return 0LL;
        if(i<ls)return charcnts[c-'a'][i];
        if(memo.contains({i,c}))return memo[{i,c}];
        i128 fibv=*prev(upper_bound(all(Fib),i));
        return memo[{i,c}]=calc(fibv-1,c)+calc(i%fibv,c);
    };
    auto calc2=[&](i128 i,char c){
        if(i<0)return 0LL;
        if(i<ls)return charcnts[c-'a'][i];
        if(memo.contains({i,c}))return memo[{i,c}];
        i128 fibv=*prev(upper_bound(all(Fib),i));
        return memo[{i,c}]=calc(fibv-1,c)+calc(i%fibv,c);
    };
    debug(Fib.size());
    debug(ahc::elapsed(start));
    rep(_q,q){
        ll cin(l,r);l--;r--;
        char cin(c);
        cout<<calc(r,c)-calc(l-1,c)<<el;
        //calc(r,c)-calc(l-1,c);
        //debugs(_q,callcnt);
    }
    debug(ahc::elapsed(start));
    debug(callcnt);
}

void naive() {

}

bool check() {
    return true;
}

void next_case(CaseGenerator& cg) {
    ll n=1;
    ll m=100000;
    auto x=cg.put_str("abcdefghijklmnopqrstuvwxyz",n);
    cg.lb();
    auto y=cg.put_str("abcdefghijklmnopqrstuvwxyz",n);
    cg.lb();
    ll q=cg.put_ll(m,m);
    cg.lb();
    rep(_q,q){
        ll l=cg.random.gen_ll(1,1000000000000000000LL);
        ll r=cg.random.gen_ll(1,1000000000000000000LL);
        if(l>r)swap(l,r);
        cg.put(l);
        cg.put(r);
        cg.put_str("abcdefghijklmnopqrstuvwxyz",1);
        cg.lb();
    }
}

void jikken() {
    __int128_t a=1,b=1;
    rep(i,500000){
        auto c=a+b;
        a=b;
        b=c;
        cout<<c<<el;
        if(c>INFLL){cout<<i<<el;break;}
    }
}

signed main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    cerr << boolalpha << fixed << setprecision(3);
    cout << fixed << setprecision(15);
    stringstream dummy_cerr;if (LOCAL == 1 && CPHEXT == 0 && !SHOW_CERR) {cerr.rdbuf(dummy_cerr.rdbuf());}if (LOCAL == 0 || CPHEXT == 1 || MODE >= 0) { if (LOCAL == 0 || CPHEXT == 1 || MODE == 0) solve();else if (MODE == 1) naive();else if (MODE == 2) check();else if (MODE == 4) jikken();else if (MODE == 3) {stringstream ss;CaseGenerator cg(ss);next_case(cg);cout << ss.str() << endl;}}else {string discarded_input;auto cin_rdbuf = cin.rdbuf();auto cout_rdbuf = cout.rdbuf();istream std_in(cin_rdbuf);ostream std_out(cout_rdbuf);stringstream ss_in;stringstream ss_out;cin.rdbuf(ss_in.rdbuf());cout.rdbuf(ss_out.rdbuf());stringstream ss_gen;CaseGenerator cg(ss_gen);auto clear_ss = [&](stringstream& ss){ss.str("");ss.clear(std::stringstream::goodbit);};auto read_ss = [&](stringstream& ss){auto result = ss.str();clear_ss(ss);return result;};auto generate = [&]{next_case(cg);ss_gen << endl;return read_ss(ss_gen);};std_out << "- Example of Generated Case:" << endl;std_out << generate() << endl;stringstream ans_solve_ss;string ans_solve;int i_target = 1;for (int i = 1;; i++) {auto testcase = generate();if (SHOW_EVERY_TESTCASES) {std_out << "- Case " << i << ":" << endl;std_out << testcase << endl;}ss_in << testcase;solve();ans_solve_ss << read_ss(ss_out);ans_solve = ans_solve_ss.str();clear_ss(ss_in);if (MODE == -1){stringstream ans_naive_ss;string ans_naive;ss_in << testcase;naive();ans_naive_ss << read_ss(ss_out);ans_naive = ans_naive_ss.str();clear_ss(ss_in);bool pass;while (true) {string s_solve, s_naive;ans_solve_ss >> s_solve;ans_naive_ss >> s_naive;if (s_solve != s_naive) {pass = false;break;}if (ans_solve_ss.eof() && ans_naive_ss.eof()) {pass = true;break;}else if (ans_solve_ss.eof() || ans_naive_ss.eof()) {pass = false;break;}}clear_ss(ans_solve_ss);clear_ss(ans_naive_ss);if (!pass) {std_out << "! Counterexample has Found:" << endl;std_out << testcase << endl;std_out << "- Answer of solve():" << endl;std_out << ans_solve << endl;std_out << "- Answer of naive():" << endl;std_out << ans_naive << endl;std_in >> discarded_input;std_out << endl;i--;continue;}}else if (MODE == -2) {stringstream out_check_ss;string out_check;ss_in << testcase << endl;ss_in << ans_solve;auto pass = check();out_check_ss << read_ss(ss_out);out_check = out_check_ss.str();clear_ss(ss_in);clear_ss(ans_solve_ss);clear_ss(out_check_ss);if (!pass) {std_out << "! Counterexample has Found:" << endl;std_out << testcase << endl;std_out << "- Answer of solve():" << endl;std_out << ans_solve << endl;std_out << "- Output of check():" << endl;std_out << out_check << endl;std_in >> discarded_input;std_out << endl;i--;continue;}}if (i == i_target) {std_out << "- " << i << " Cases Passed" << endl << endl;i_target *= 2;}}}
}

// modの取り忘れがないか？
// 998と10^9+7を間違えてないか？
// 計算途中で値がオーバーフローしないか？
// bit全探索で1<<60とかやってないか？(1LL<<60)
// 入力制約がllの範囲でオーバーフローしていないか？
// 入力の型を間違えていないか？(ll cin(s)とか)
// 定数倍 map→unordered_map→vector
// 参照絡みで事故ってないか？