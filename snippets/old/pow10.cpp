set<ll> pow10s;
void init_pow10(){
    if(pow10s.size()==0){
        ll tmp=1;
        rep(i,19){
            pow10s.insert(tmp);
            tmp*=10;
        }
        pow10s.insert(INFLL+1LL);
    }
}
bool is_pow10(ll n){
    init_pow10();
    return pow10s.contains(n);
}
ll lower_pow10(ll n){
    init_pow10();
    return *(--pow10s.upper_bound(n));
}