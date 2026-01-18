//https://nyaannyaan.github.io/library/data-structure/union-find-with-potential.hpp
//(modified)
#line 2 "data-structure/union-find-with-potential.hpp"

template <class S, auto op, auto e, auto inv>
struct UnionFindWithPotential {
    // https://github.com/atcoder/ac-library/blob/master/atcoder/segtree.hpp からひったくってきた
    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                  "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                  "e must work as S()");
    static_assert(std::is_convertible_v<decltype(inv), std::function<S(S)>>,
                  "inv must work as S(S)");

    vector<int> dat;
    vector<S> pot;

    UnionFindWithPotential(int N) : dat(N, -1), pot(N, e()) {}

    int root(int x) {
        if (dat[x] < 0) return x;
        int r = root(dat[x]);
        pot[x] = op(pot[dat[x]], pot[x]);
        return dat[x] = r;
    }

    // return P(x) - P(root(x))
    S potential(int x) {
        root(x);
        return pot[x];
    }

    bool same(int x, int y) { return root(x) == root(y); }

    // return P(x) - P(y)
    S diff(int x, int y) {
        return op(inv(potential(y)), potential(x));
    }

    // s.t. P(x) = P(y) + p
    // return Satisfiablility
    bool merge(int x, int y, S p) {
        p = op(op(potential(y), p), inv(potential(x)));
        x = root(x), y = root(y);
        if (x == y) return p == e();
        if (dat[x] < dat[y]) swap(x, y), p = inv(p);
        dat[y] += dat[x];
        dat[x] = y;
        pot[x] = p;
        return true;
    }

    // return size of CC including x
    int size(int x) { return -dat[root(x)]; }
};
struct S_ufp {
    // xx xy
    // yx yy
    mint xx,xy,yx,yy;
    friend bool operator==(const S_ufp& a, const S_ufp& b){return (a.xx==b.xx&&a.xy==b.xy&&a.yx==b.yx&&a.yy==b.yy);}
};
S_ufp op_ufp(S_ufp a, S_ufp b) {
    return {a.xx*b.xx+a.xy*b.yx, a.xx*b.xy+a.xy*b.yy, a.yx*b.xx+a.yy*b.yx, a.yx*b.xy+a.yy*b.yy};
}
S_ufp e_ufp() {
    return {1,0,0,1};
}
S_ufp inv_ufp(S_ufp v) {
    mint factor=v.xx*v.yy-v.xy*v.yx;
    return {v.yy/factor,-v.xy/factor,-v.yx/factor,v.xx/factor};
}
//UnionFindWithPotential<S_ufp,op_ufp,e_ufp,inv_ufp> uf(n+1);