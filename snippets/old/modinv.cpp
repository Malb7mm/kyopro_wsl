ll modinv(ll a,ll m){
    ll b=m,u=1,v=0;
	while(b){
		ll t=a/b;
		a-=t*b;
		u-=t*v;
        swap(a,b);
        swap(u,v);
	}
	u%=m;
	if(u<0)u+=m;
	return u;
}