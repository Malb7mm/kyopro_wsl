auto seq_sum=[&](ll a,ll d,ll n){return n*(2*a+(n-1)*d)/2;};//初項a 公差d 項数n
auto seq_sum2=[&](ll a,ll l,ll n){if(a>l)return 0LL;return n*(a+l)/2;};//初項a 末項l 項数n
auto seq_sum3=[&](ll a,ll d,ll l){if(a>l)return 0LL;ll n=(l-a)/d+1;return n*(2*a+(n-1)*d)/2;};//初項a 公差d 末項<=l