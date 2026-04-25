#define STRUCT_ID__ Lseg1
namespace mystd {
    namespace STRUCT_ID__ {
        struct S { mint value; mint value2; ll width; };
        using F = mint;
        std::ostream& operator<<(std::ostream& os, S n) {
            return os << n.value.val();
        }

        S op(S a, S b){ return { a.value + b.value, a.value2 + b.value2, a.width + b.width }; }
        S e(){ return { 0, 0, 0 }; }
        S mapping(F f, S x){ return { x.value + f * x.width, x.value2 + 2*f * x.value + f*f * x.width, x.width }; }
        F composition(F f, F g){ return f+g; }
        F id(){ return 0; }

        using It = lazy_segtree<S,op,e,F,mapping,composition,id>;
    }
}
namespace STRUCT_ID__ = mystd:: STRUCT_ID__ ;
#undef STRUCT_ID__
// Lseg1::It seg(vector<Lseg1::S>(n,{0,0,1}));