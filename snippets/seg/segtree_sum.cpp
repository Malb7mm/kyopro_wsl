#define STRUCT_ID__ Seg1
namespace mystd {
    namespace STRUCT_ID__ {
        using S = ll;

        S op(S a, S b){ return a+b; }
        S e(){ return 0; }

        using It = segtree<S,op,e>;
    }
}
#undef STRUCT_ID__
using namespace mystd;
// Seg1::It seg(vector<seg1::S>(n,0));