vector<vector<vector<ll>>> patterns;
vector<vector<ll>> groups;
function<void(int)> dfs=[&](int i){
    if(i==n){
        patterns.push_back(groups);
        return;
    }
    rep(g,groups.size()){
        groups[g].push_back(i);
        dfs(i+1);
        groups[g].pop_back();
    }
    groups.push_back({i});
    dfs(i+1);
    groups.pop_back();
};
dfs(0);