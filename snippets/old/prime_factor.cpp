auto pfactor=[&](ll n){
    vector<ll> primes={1};
    ll num=n;
    for(ll i=2;i*i<=n;i++){
        while(num%i==0){
            num/=i;
            primes.push_back(i);
        }
        if (num==1)break;
    }
    if (num!=1)primes.push_back(num);
    return primes;
};