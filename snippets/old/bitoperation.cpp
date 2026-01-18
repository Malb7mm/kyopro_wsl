ll set1_bit(ll val, int bit) {
    return val|=(1LL<<bit);
}
ll set0_bit(ll val, int bit) {
    return val&=~(1LL<<bit);
}
ll flip_bit(ll val, int bit) {
    return val^=(1LL<<bit);
}
bool ispop_bit(ll val, int bit) {
    return val&(1LL<<bit);
}
