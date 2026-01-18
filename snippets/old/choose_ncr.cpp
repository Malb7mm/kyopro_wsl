vector<mint10> fact={1};
rep(i,1,200010){fact.push_back(fact[i-1]*i);}
auto choose=[&](ll n,ll r){return fact[n]/(fact[r]*fact[n-r]);};