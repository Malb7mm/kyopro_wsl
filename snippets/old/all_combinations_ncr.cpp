template <typename T> vector<vector<T>> all_combinations(vector<T> &vec, int r) {
    vector<vector<T>> result;
    auto n=vec.size();
    vector<int> indices;
    vector<T> combination;
    rep(i,r){indices.push_back(i);combination.push_back(vec[i]);}
    while(true){
        result.push_back(combination);
        ll i=r-1;
        for(;i>=0;i--){
            indices[i]++;
            if(indices[i]<n-(r-i)+1){
                combination[i]=vec[indices[i]];
                break;
            }
        }
        if(i==-1)break;//全組合せ列挙完了
        i++;
        for(;i<r;i++){
            indices[i]=indices[i-1]+1;
            combination[i]=vec[indices[i]];
        }
    }
    return result;
}