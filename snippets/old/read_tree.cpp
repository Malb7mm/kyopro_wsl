vector<vector<int>> G(n+1,vector<int>());
rep(i,n-1){
    int cin(u,v);
    G[u].push_back(v);
    G[v].push_back(u);
}