function<pair<int,int>(int,int,vector<vector<int>>,set<int>&)> dfs=[&](int u, int cnt, vector<vector<int>> G, set<int>& visited)->pair<int,int>{
    visited.insert(u);
    int farthest_v=-1;
    int farthest_dist=cnt;
    for(auto v:G[u]){
        if(!visited.contains(v)){
            if(farthest_dist==cnt){
                farthest_dist++;
                farthest_v=v;
            }
            auto [fv,fd]=dfs(v,cnt+1,G,visited);
            if(fd>farthest_dist){
                farthest_dist=fd;
                farthest_v=fv;
            }
        }
    }
    return {farthest_v,farthest_dist};
};