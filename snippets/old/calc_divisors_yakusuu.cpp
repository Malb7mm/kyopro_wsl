auto calc_divisors=[&](ll n){
    vector<ll> divisors={};
    for(ll i=1;i*i<=n;i++){
        if(n%i==0){
            divisors.push_back(i);
            if(n/i!=i)divisors.push_back(n/i);
        }
    }
    return divisors;
};