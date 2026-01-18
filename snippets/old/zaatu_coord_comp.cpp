struct zaatu {
    vector<ll> ve;
    void add(ll val) {
        ve.push_back(val);
    }
    map<ll,ll> comp() {
        map<ll,ll> map;
        sort(all(ve));
        ve.erase(unique(all(ve)),ve.end());
        ll serial=1;
        for(auto v:ve){
            map[v]=serial++;
        }
        return map;
    }
    map<ll,pair<ll,ll>> comp_width() {
        map<ll,pair<ll,ll>> map;
        sort(all(ve));
        ve.erase(unique(all(ve)),ve.end());
        ll serial=1,n=ve.size();
        rep(i,n-1){
            map[ve[i]]={serial++,ve[i+1]-ve[i]};
        }
        map[ve[n-1]]={serial++,INFLL};
        return map;
    }
};