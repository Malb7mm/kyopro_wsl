auto lrover=[&](ll l, ll r, ll n){//閉区間[l,r]、インデックスの最大nから、r<nである新しい区間および>=nのカウントを返す
    auto left=l;
    auto right=r;
    auto rmax=n;
    auto overcnt=max(0LL,right-rmax);
    right=min(right,rmax);
    return make_tuple(left,right,overcnt);
};