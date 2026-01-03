// template reference: https://qiita.com/sorachandu/items/041169d34b9f9b99bcf7
// solve() is around line 360

#include <bits/stdc++.h>
using namespace std;

#include <atcoder/modint>
#include <atcoder/dsu>
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
#define ansYn(x) cout << (x ? "Yes" : "No") << endl
#define ansYN(x) cout << (x ? "YES" : "NO") << endl
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
#define LOCAL 0
#endif
#ifndef CPHEXT
#define CPHEXT 0
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
concept Container = std::ranges::range<T> && !Streamable<T>;

template <typename T>
concept ValStreamable = requires(std::ostream& os, T x) { os << x.val(); };

void debug_cerr_vonly(ValStreamable auto value, int nest) {
    std::cerr << value.val();
}

void debug_cerr_vonly(Streamable auto value, int nest) {
    std::cerr << value;
}

template <typename T1,typename T2>
void debug_cerr_vonly(pair<T1,T2> value, int nest) {
    std::cerr << "[";
    debug_cerr_vonly(value.first, nest);
    std::cerr << ", ";
    debug_cerr_vonly(value.second, nest);
    std::cerr << "]";
}

template <typename T1,typename T2,typename T3>
void debug_cerr_vonly(tuple<T1,T2,T3> value, int nest) {
    std::cerr << "[";
    debug_cerr_vonly(get<0>(value), nest);
    std::cerr << ", ";
    debug_cerr_vonly(get<1>(value), nest);
    std::cerr << ", ";
    debug_cerr_vonly(get<2>(value), nest);
    std::cerr << "]";
}

template <typename T1,typename T2,typename T3,typename T4>
void debug_cerr_vonly(tuple<T1,T2,T3,T4> value, int nest) {
    std::cerr << "[";
    debug_cerr_vonly(get<0>(value), nest);
    std::cerr << ", ";
    debug_cerr_vonly(get<1>(value), nest);
    std::cerr << ", ";
    debug_cerr_vonly(get<2>(value), nest);
    std::cerr << ", ";
    debug_cerr_vonly(get<3>(value), nest);
    std::cerr << "]";
}

void debug_cerr_vonly(Container auto value, int nest) {
    std::cerr << std::string(nest, ' ') << "{" << endl << std::string(nest + 1, ' ');
    bool first = true;
    for (const auto& v : value) {
        if (!first) std::cerr << ", ";
        debug_cerr_vonly(v, nest + 1);
        first = false;
    }
    std::cerr << endl << std::string(nest, ' ') << "}";
}

void debug_cerr(std::string name, auto value) {
    std::cerr << "# " << name << " = ";
    debug_cerr_vonly(value, 0);
    std::cerr << endl;
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
    Random random;
    std::stringstream& ss;
public:

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

//#define int ll

//#pragma GCC target("avx")
//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

//#include <atcoder/segtree>
#include <atcoder/lazysegtree>
//#include <atcoder/string>
//#include <atcoder/scc>

using S=tuple<ll,ll,ll>;//力,残りの人数,身長
S op(S a, S b){
    return {0,0,min(get<0>(a)*get<1>(a)+get<2>(a),get<0>(b)*get<1>(b)+get<2>(b))};
}
S e(){
    return {0,0,INFLL};
}
using F=ll;
S mapping(F f, S s){
    return {get<0>(s),get<1>(s)+f,get<2>(s)};
}
F composition(F f, F g){
    return f+g;
}
F id(){
    return 0;
}
// lazy_segtree<S,op,e,F,mapping,composition,id> seg(A);

#define MULTI_TESTCASES false
#define MODE -1 // -2: test(check) -1: test(naive) 0:solve 1:naive 2:check 3:next_case 4:jikken
#define SHOW_EVERY_TESTCASES false
#define HIDE_CERR true

//[概要]
//N人が一箇所に座布団を積むゲームをする 最初は0枚
//i人目の人は、いま積まれている座布団がH_i枚以下ならP_i枚の座布団を積むし、H_i枚を超えているならあきらめる
//なるべく多くの人に座布団を積ませたいので、人数を最大化しろ
//
//算数をするぞ！とおもったけどこれH+PやらH-Pやらで何とかなる問題なのか？（ヒント駆動考察）
//まず、座布団がx枚の状態のとき、a枚の座布団を積むとx+a未満の身長の人が脱落する
//身長の昇順で貪欲をすると、身長10力99999と身長100力1がいたとき最適解でなくなる
//逆に力の昇順で貪欲をすると、力10身長99999と力100身長1がいたとき最適解でなくなる
//力の弱い人は身長リミットを圧迫しないので先に来てほしいし、身長の低い人も積めなくなる前に先に来てほしい
//ある人が座布団を積めなくなる条件は、それより前の人の力の和が身長を超えたとき
//力順でソートをして累積和を取ればある人が位置できるインデックスの上界がわかる？
//サンプル3について考えてみると
//力でソートして1 1 2 2 3 3 3 3 4 4→累積和で1 2 4 6 9 12 15 18 22 26
//例えば人2は身長8力4なので、最大でも4人目までにしかなれない
//(累積和の中に自分の力を含む場合を考慮する必要がありそう
// と思ったけど、その場合直しても上界が下に動くだけ？)
//累積和は特に関係なさそう！ｗ
//サンプル3の答えで積む人は
//身長0力1 → 身長1力3 → 身長4力2 → 身長8力3or3 → 身長9力1or2 かな
//力の弱い人を先に取るデメリットってなんだ？
//力10身長99999と力100身長1のケースだと、力が弱い人を先に取ることで身長の低い人が積めなくなってしまうからだめだった
//逆に身長の低い人を先に取った場合に、その人の力が強すぎると積めなくなる人が増えてしまう
//結局いい塩梅に身長が低くて力の弱い人を取りたいわけだが W+Pはサンプル3の時点で違う
//ある人が座布団を乗せた時、その力×残りの人数だけ、残りの身長の総和が減る？
//あと乗せた人自身の身長分も減る
//これが最大になるように選ぶ？
//(力×残りの人数+自分の身長)が最小の選択肢を取り続ける？
//これが正解だとして、残りの人数が操作毎に変化するので単純には計算できない
//Range Affine Range Minみたいな遅延セグ木があれば処理はできそう
// ↑ 身長がそれぞれ違うからだめです！
// ↑ セグ木側でもっておけばよくないですか
// ↑ じゃあRange Affineじゃなくて積だけ作用させられればいいじゃんね
// ↑ なんならデータ側で力,人数,身長を持っておいて、人数だけ区間加算できるようにすればいい
//だめです！解散
//
//(解説読んだ)けどわからないのでgeminiに投げた 結果返ってきた答えをちゃんと証明した
//参加者i→参加者jの順で積んだ時、どちらも積める条件を考える
//iが積む前の座布団の高さをSとすると、iが積める条件はS<H_i
//iが積んだ後の座布団の高さはS+P_iなので、jが積める条件はS+P_i<H_j、移行してS<H_j-P_iである
//この条件をまとめるとS<min(H_i,H_j-P_i)
//逆に、j→iの順で積む場合はS<min(H_j,H_i-P_j)
//できるだけ緩い条件のほう、つまりSが大きくても積める方の順番を選びたいので、
//min(H_i,H_j-P_i)のほうが大きければi→jで積みたいし、そうでなければj→iで積みたい
//min(H_i,H_j-P_i)のほうが大きいか同じと仮定する（つまり、j→iをi→jに入れ替えて悪化しないと仮定する）
//f(i)>=f(j)ならばmin(H_i,H_j-P_i)>=min(H_j,H_i-P_j)となるような評価関数fを定めたい
//場合分けをして、min(H_i,H_j-P_i)>=min(H_j,H_i-P_j) が成り立つ条件について考える
//(1) H_i <= H_j-P_i かつ H_j <= H_i-P_j
//  この条件について、H_iとH_jの大小関係で場合分けして考える
//  (a) H_i>H_j のとき、一つ目の不等式を変形して H_j-H_i>=P_i とするとP_iは負となり、問題の制約を満たさない
//  (b) H_i<H_j のとき、二つ目の不等式について(a)と同様に考えるとP_jは負となり、問題の制約を満たさない
//  (c) H_i=H_j のとき、各不等式について(a)、(b)と同様に考えるとP_i、P_jはそれぞれ0以下となり、問題の制約を満たさない
//  したがって、問題の制約下でこの条件が満たされることはない
//(2) H_i >= H_j-P_i かつ H_j <= H_i-P_j ならば、H_j-P_i >= H_j     制約よりP_iは1以上であるため、H_j-P_i>=H_jは常に偽となり、命題は偽である
//(3) H_i <= H_j-P_i かつ H_j >= H_i-P_j ならば、    H_i >= H_i-P_j これは、P_jが1以上のとき常に成立するので、仮定が満たされているならば命題は常に真である
//(4) H_i >= H_j-P_i かつ H_j >= H_i-P_j ならば、H_j-P_i >= H_i-P_j
//したがって、「f(i)>=f(j)ならばH_j-P_i>=H_i-P_j」が必ず満たされるような評価関数fを定めればよい
//H_j-P_i>=H_i-P_jを変形するとH_j+P_j>=H_i+P_iとなり、f(x)=-(H_x+P_x)とおくと、「f(i)>=f(j)ならばH_j-P_i>=H_i-P_j」を満たす
//簡単のためf(x)の符号を反転して考えると、ある二人の参加者について、H_x+P_xの小さい方を先に並べたような順序は、
//その逆の順序と比べて積める人数が同じか多いといえる
//N人の参加者を並べる順序であって、座布団を積む人数が考え得る中で一番多いようなある順序について考える
//この順序のうち、ある隣り合う2人の参加者iとjについて、iの方が先であり、かつH_i+P_i>H_j+P_jであることを仮定する
//先の議論より、参加者iとjを入れ替え、j→iの順序としたとき、並び替え後のiまでの順序において座布団を積むことができた人数は、
//並び替え前のjまでの順序において座布団を積むことが出来た人数よりも多いか、もしくは同じであるといえる
//また、並び替え後のiまでのPの総和と、並び替え前のjまでのPの総和は等しいため、順序におけるそれ以降の結果には影響しない
//したがって、H_i+P_i>H_j+P_j、かつiが先であるような参加者iとjについて、その2名を入れ替えても解は悪化しない
//これに従い、隣接する参加者のうち評価関数の値が入れ変わっているような参加者の組を全て入れ替えると、
//これ以上参加者の組を入れ替えられなくなったとき、その順序においてH_x+P_xが昇順に並ぶことがわかる
//したがって、評価関数f(x)=H_x+P_xの昇順に参加者を並べる解は最適解の一つである
// ↑ これi,jをどっちの順序で並べても2人ともは積めないときにスワップしてもいい証明できてなくない？
//  ただそれは簡単で、
//  - i→j、j→iのどちらの順序も積める人数が1か、もしくはどちらも0かなら問題はない
//  - i→jで1枚だけ積めるケースを考えると、その直前までの座布団の枚数SがH_i以下ということを意味していて、
//    iとjをスワップしたときに、もしjが積めるなら少なくとも減りはしない(スワップ後のiも積めるならさっきの2人とも積める場合の議論よりすでにP_j+H_j<P_i+H_i)
//    jがもし積めなかったとしても、その場合Sはiが積む時点では変わらないのでiは積める したがって、スワップで解は悪化しない
//
//()
//
//
//https://gemini.google.com/share/6b34e487321c
void solve() {
    ll cin(n);
    lazy_segtree<S,op,e,F,mapping,composition,id> seg(n+1);
    //ll h_val=0;
    rep(i,n){
        ll cin(h,p);
        seg.set(i+1,{p,n-1,h});
        //h_val+=h;
    }
    ll anscnt=0;
    ll p_sum=0;
    rep(i,n){
        local{
            rep(i,n+1){
                auto val=seg.get(i);
                if(get<2>(val)==INFLL)continue;
                dmsg(format("seg[{}]=[{},{},{}]={}",i,get<0>(val),get<1>(val),get<2>(val),get<0>(val)*get<1>(val)+get<2>(val)));
            }
        }
        auto minval=get<2>(seg.all_prod());
        auto comp=[&](auto v){return get<0>(v)*get<1>(v)+get<2>(v)>minval;};
        auto idx=seg.max_right(0,comp);
        auto p=get<0>(seg.get(idx));
        auto h=get<2>(seg.get(idx));
        seg.set(idx,{0,0,INFLL});
        if(h>=p_sum){
            //h_val-=minval;
            anscnt++;
            p_sum+=p;
            seg.apply(0,n+1,-1);
        }
        debug(p_sum);
        //debug(h_val);
        //if(h_val<0)break;
    }
    cout<<anscnt<<endl;
}

void naive() {
    ll cin(_T);
    rep(_t,_T){
        ll cin(n);
        vector<ll> L(n),R(n);
        rep(i,n)cin>>L[i]>>R[i];
        auto I=L;
        while(I[0]<=R[0]){
            set<ll> set;
            bool ok=true;
            rep(i,n){
                if(set.contains(I[i])){ok=false;break;}
                set.insert(I[i]);
            }
            if(ok){ansYn(true);return;}
            reprev(i,n){
                I[i]++;
                if(I[i]<=R[i])break;
                if(i!=0)I[i]=L[i];
            }
        }
        ansYn(false);
    }
}

bool check() {
    return false;
}

void next_case(CaseGenerator& cg) {
    cg.put(1);cg.lb();
    auto n=cg.put_ll(1,4);
    cg.lb();
    rep(i,n){
        auto l=cg.put_ll(1,9);
        auto r=cg.put_ll(l,10);
        cg.lb();
    }
}

void jikken() {

}

signed main() {
    cerr << boolalpha << fixed << setprecision(15);
    cout << fixed << setprecision(15);
    stringstream dummy_cerr;
    if (LOCAL == 1 && CPHEXT == 0 && HIDE_CERR) {
        cerr.rdbuf(dummy_cerr.rdbuf());
    }
    if (LOCAL == 0 || CPHEXT == 1 || MODE >= 0) { 
        
        if (LOCAL == 0 || CPHEXT == 1 || MODE == 0) {
            int t = 1;
            if (MULTI_TESTCASES) cin >> t;
            rep(i, t) {
                solve();
            }
        }
        else if (MODE == 1) naive();
        else if (MODE == 2) check();
        else if (MODE == 4) jikken();
        else if (MODE == 3) {
            stringstream ss;
            CaseGenerator cg(ss);
            next_case(cg);
            cout << ss.str() << endl;
        }
    }
    // random test
    else {
        string discarded_input;

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
        string ans_solve;

        int i_target = 1;
        for (int i = 1;; i++) {
            auto testcase = generate();
            if (SHOW_EVERY_TESTCASES) {
                std_out << "- Case " << i << ":" << endl;
                std_out << generate() << endl;
            }

            ss_in << testcase;
            solve();
            ans_solve_ss << read_ss(ss_out);
            ans_solve = ans_solve_ss.str();
            clear_ss(ss_in);

            if (MODE == -1){
                stringstream ans_naive_ss;
                string ans_naive;

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
            }
            else if (MODE == -2) {
                stringstream out_check_ss;
                string out_check;

                ss_in << testcase << endl;
                ss_in << ans_solve;
                auto pass = check();
                out_check_ss << read_ss(ss_out);
                out_check = out_check_ss.str();
                clear_ss(ss_in);

                clear_ss(ans_solve_ss);
                clear_ss(out_check_ss);
                if (!pass) {
                    std_out << "! Counterexample has Found:" << endl;
                    std_out << testcase << endl;
                    std_out << "- Answer of solve():" << endl;
                    std_out << ans_solve << endl;
                    std_out << "- Output of check():" << endl;
                    std_out << out_check << endl;

                    std_in >> discarded_input;
                    std_out << endl;
                    i--;
                    continue;
                }
            }

            if (i == i_target) {
                std_out << "- " << i << " Cases Passed" << endl << endl;
                i_target *= 2;
            }
        }
    }
}