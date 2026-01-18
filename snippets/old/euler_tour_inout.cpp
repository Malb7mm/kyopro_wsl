vector<ll> in(n+1),out(n+1),tour;
{
    ll timer=0;
    function<void(ll,ll)> dfs=[&](ll u,ll from){
        tour.push_back(u);
        in[u]=timer++;
        for(auto v:G[u]){
            if(v==from)continue;
            dfs(v,u);
        }
        tour.push_back(u);
        out[u]=timer++;
    };
    dfs(1,-1);
}