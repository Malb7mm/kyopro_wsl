#define STRUCT_ID__ Lseg1
namespace mystd {
    namespace STRUCT_ID__ {
        // https://betrue12.hateblo.jp/entry/2020/09/23/005940
        struct S{
            long long value;
            int size;
        };
        using F = long long;

        S op(S a, S b){ return {a.value+b.value, a.size+b.size}; }
        S e(){ return {0, 0}; }
        S mapping(F f, S x){ return {x.value + f*x.size, x.size}; }
        F composition(F f, F g){ return f+g; }
        F id(){ return 0; }

        using It = lazy_segtree<S,op,e,F,mapping,composition,id>;
    }
}
#undef STRUCT_ID__
using namespace mystd;
// Lseg1::It seg(vector<Lseg1::S>(n,0));