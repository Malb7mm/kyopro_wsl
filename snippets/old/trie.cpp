auto trie=vec(ll,m,26,-1);
auto trie_rev=vec(ll,m,-1);
auto trie_cnt=vec(ll,m,0);
vector<ll> to_trie(n);
{
    ll serial=1;
    rep(i,n){
        ll curidx=0;
        trie_cnt[0]++;
        for(auto c:S[i]){
            if(trie[curidx][c-'a']==-1){
                trie[curidx][c-'a']=serial;
                trie_rev[serial]=curidx;
                curidx=serial++;
            }
            else{
                curidx=trie[curidx][c-'a'];
            }
            trie_cnt[curidx]++;
        }
        to_trie[i]=curidx;
    }
}