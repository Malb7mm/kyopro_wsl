#define STRUCT_ID__ lseg1
namespace mystd {
    namespace STRUCT_ID__ {
        // https://betrue12.hateblo.jp/entry/2020/09/23/005940
        using S = ll;
        using F = ll;

        S op(S a, S b){ return max(a, b); }
        S e(){ return -INFLL; }
        S mapping(F f, S x){ return f+x; }
        F composition(F f, F g){ return f+g; }
        F id(){ return 0; }

        using It = lazy_segtree<S,op,e,F,mapping,composition,id>;
    }
}
#undef STRUCT_ID__
using namespace mystd;
// lseg1::It seg(vector<lseg1::S>(n,0));