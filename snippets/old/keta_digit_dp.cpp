auto calc=[&](string n){
    int len=n.length();
    ll ans=0;
    auto dp=vec(ll,len+1,2,0);//dp[i桁目まで][1=tight]
    dp[0][1]=1;
    rep(i,len)rep(tight,2)rep(j,10){
        if(tight&&j>(n[i]-'0'))continue;
        dp[i+1][tight&&(j==(n[i]-'0'))]+=dp[i][tight];
    }
    rep(tight,2){
        ans+=dp[len][tight];
    }
    return ans;
};