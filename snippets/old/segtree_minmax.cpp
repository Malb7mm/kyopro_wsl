using S_min=ll;
S_min op_min(S_min a, S_min b){
    return min(a,b);
}
S_min e_min(){
    return INFLL;
}
using S_max=ll;
S_max op_max(S_max a, S_max b){
    return max(a,b);
}
S_max e_max(){
    return -INFLL;
}
// segtree<S_min,op_min,e_min> seg_min(n);
// segtree<S_max,op_max,e_max> seg_max(n);