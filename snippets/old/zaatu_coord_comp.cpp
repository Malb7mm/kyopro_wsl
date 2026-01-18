struct zaatu {
    vector<ll> ve;
    void add(ll val) {
        ve.push_back(val);
    }
    map<ll,ll> comp(ll serial_begin=1) {
        map<ll,ll> map;
        sort(all(ve));
        ve.erase(unique(all(ve)),ve.end());
        ll serial=serial_begin;
        for(auto v:ve){
            map[v]=serial++;
        }
        return map;
    }
    map<ll,pair<ll,ll>> comp_width(ll serial_begin=1) {
        map<ll,pair<ll,ll>> map;
        sort(all(ve));
        ve.erase(unique(all(ve)),ve.end());
        ll serial=serial_begin,n=ve.size();
        rep(i,n-1){
            map[ve[i]]={serial++,ve[i+1]-ve[i]};
        }
        map[ve[n-1]]={serial++,INFLL};
        return map;
    }
};