// template references: https://qiita.com/sorachandu/items/041169d34b9f9b99bcf7

#include <bits/stdc++.h>
using namespace std;

//#include <atcoder/>
//using namespace atcoder;

using ll = long long;
using ull = unsigned long long;
#define INF 1 << 29
#define rep2(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, x, n) for (int i = (int)(x); i < (int)(n); i++)
#define rep_selector(_1, _2, _3, NAME, ...) NAME
#define rep(...) rep_selector(__VA_ARGS__, rep3, rep2, rep1)(__VA_ARGS__)
#define reprev2(i, n) for (int i = (int)(n)-1; i >= 0; i--)
#define reprev3(i, x, n) for (int i = (int)(n)-1; i >= (int)(x); i--)
#define reprev_selector(_1, _2, _3, NAME, ...) NAME
#define reprev(...) reprev_selector(__VA_ARGS__, reprev3, reprev2, reprev1)(__VA_ARGS__)
#define all(x) x.begin(), x.end()
#define ansYN(x) cout << (x ? "Yes" : "No") << endl
#define cin1(a) a; cin >> a
#define cin2(a, b) a, b; cin >> a >> b
#define cin3(a, b, c) a, b, c; cin >> a >> b >> c
#define cin4(a, b, c, d) a, b, c, d; cin >> a >> b >> c >> d
#define cin_selector(_1, _2, _3, _4, NAME, ...) NAME
#define cin(...) cin_selector(__VA_ARGS__, cin4, cin3, cin2, cin1)(__VA_ARGS__)
#ifdef LOCAL
#define debug(x) debug_cerr(#x, x)
#else
#define debug(x) 
#endif

template<typename T1, typename T2> inline bool chmax(T1 &a, T2 b) {
    bool compare = a < b;
    if(compare) a = b;
    return compare;
}
template<typename T1, typename T2> inline bool chmin(T1 &a, T2 b) {
    bool compare = a > b;
    if(compare) a = b;
    return compare;
}

template <typename T>
concept Streamable = requires(std::ostream& os, T x) { os << x; };

template <typename T>
concept Container = std::ranges::range<T> && !Streamable<T>;;

void debug_cerr_vonly(Streamable auto value, int nest) {
    std::cerr << value;
}

void debug_cerr_vonly(Container auto value, int nest) {
    std::cerr << string(nest, ' ') << "{" << endl << string(nest + 1, ' ');
    bool first = true;
    for (const auto& v : value) {
        if (!first) std::cerr << ", ";
        debug_cerr_vonly(v, nest + 1);
        first = false;
    }
    std::cerr << endl << string(nest, ' ') << "}";
}

void debug_cerr(string name, auto value) {
    std::cerr << "# " << name << " = ";
    debug_cerr_vonly(value, 0);
    std::cerr << endl;
}

// *-*-*-*-*-*-*-*-*-*-*-* //
//            _            //
//  ___  ___ | |_   _____  //
// / __|/ _ \| \ \ / / _ \ //
// \__ \ (_) | |\ V /  __/ //
// |___/\___/|_| \_/ \___| //
//                         //
// *-*-*-*-*-*-*-*-*-*-*-* //

void solve() {
    int cin(n);
    string cin(s);
    vector<ll> R;
    rep(i,n){ll cin(r);R.push_back(r);}
    ll notree_max=0;
    int notree_max_idx=0;
    ll undertree_max=0;
    int undertree_max_idx=0;
    rep(i,n){
        if(s[i]=='.'&&R[i]>notree_max){
            notree_max=R[i];
            notree_max_idx=i;
        }
        if(s[i]=='#'&&R[i]>undertree_max){
            undertree_max=R[i];
            undertree_max_idx=i;
        }
    }

    function<ll(int,int,int,int,ll,ll)> subsolve = [&](int l, int r, int lk, int rk, ll kmax, ll max)->ll {
        bool nonext=false;
        ll lmax=0;
        ll lumax=0;
        if (l == lk) {
            int flag=0;
            while(true){
                lk--;
                if(lk<0){nonext=true;break;}
                if(flag==0 && s[lk]=='.')flag++;
                if(flag==1 && s[lk]=='#')break;
                if(s[lk]=='#')chmax(lumax,R[lk]);
                if(s[lk]=='.')chmax(lmax,R[lk]);
            }
        } else lmax=kmax;
        ll rmax=0;
        ll rumax=0;
        if (r == rk) {
            int flag=0;
            while(true){
                rk++;
                if(rk>=n){nonext=true;break;}
                if(flag==0 && s[rk]=='.')flag++;
                if(flag==1 && s[rk]=='#')break;
                if(s[rk]=='#')chmax(rumax,R[rk]);
                if(s[rk]=='.')chmax(rmax,R[rk]);
            }
        } else rmax=kmax;
        
        ll score=0;
        if (lmax>rmax){
            score+=lmax+max;
            kmax=rmax;
            chmax(max,lumax);
            chmax(max,lmax);
            if(!nonext)score+=subsolve(lk, r, lk, rk, kmax, max);
        }else{
            score+=rmax+max;
            kmax=lmax;
            chmax(max,rumax);
            chmax(max,rmax);
            if(!nonext)score+=subsolve(l, rk, lk, rk, kmax, max);
        }
        return score;
    };

    auto subsolve2 = [&](int x)->tuple<ll,int,int> {
        ll max=0;
        int i,j;
        for(i=x;;i--){
            chmax(max,R[i]);
            if(i-1<0 || s[i-1]=='#')break;
        }
        for(j=x;;j++){
            chmax(max,R[j]);
            if(j+1>=n || s[j+1]=='#')break;
        }
        return {max,i,j};
    };

    auto subsolve3 = [&](int x)->int {
        ll maxl=0; int maxlcnt=0;
        ll maxr=0; int maxrcnt=0;
        int i,j;
        for(i=x;;i--){
            if (R[i]>maxl){maxl=R[i];maxlcnt=1;}
            else if (R[i]==maxl){maxlcnt++;}
            if(i-1<0 || s[i-1]=='#')break;
        }
        for(j=x;;j++){
            if (R[j]>maxr){maxr=R[j];maxrcnt=1;}
            else if (R[j]==maxr){maxrcnt++;}
            if(j+1>=n || s[j+1]=='#')break;
        }
        return maxlcnt*maxrcnt;
    };

    function<ll(int,int,ll)> subsolve4 = [&](int l, int r, ll max)->ll {
        int lk=l, rk=r;
        ll lmax=0; int lmaxcnt=0;
        {
            int flag=0;
            while(true){
                lk--;
                if(lk<0)break;
                if(flag==0 && s[lk]=='.')flag++;
                if(flag==1 && s[lk]=='#')break;
                if(s[lk]=='.'){
                    if (R[lk]>lmax){lmax=R[lk];lmaxcnt=1;}
                    else if (R[lk]==lmax){lmaxcnt++;}
                }
            }
        }
        ll rmax=0; int rmaxcnt=0;
        {
            int flag=0;
            while(true){
                rk++;
                if(rk>=n)break;
                if(flag==0 && s[rk]=='.')flag++;
                if(flag==1 && s[rk]=='#')break;
                if(s[rk]=='.'){
                    if (R[rk]>rmax){rmax=R[rk];rmaxcnt=1;}
                    else if (R[rk]==rmax){rmaxcnt++;}
                }
            }
        }
        
        int ptn=max;
        if (lmax>rmax){
            ptn*=lmaxcnt;
        }else{
            ptn*=rmaxcnt;
        }
        return ptn;
    };

    ll notree_score=0;
    int notree_ptn=0;
    {
        auto [max,l,r]=subsolve2(notree_max_idx);
        debug(max);
        debug(l);
        debug(r);
        notree_ptn=subsolve4(l,r,max);
        notree_score=subsolve(l,r,l,r,0,max);
    }
    ll undertree_score=0;
    int undertree_ptn=0;
    {
        auto [max,l,r]=subsolve2(undertree_max_idx);
        debug(max);
        debug(l);
        debug(r);
        undertree_ptn=subsolve3(undertree_max_idx);
        undertree_score=subsolve(l,r,l,r,0,max);
    }
    debug(notree_score);
    debug(notree_ptn);
    debug(undertree_score);
    debug(undertree_ptn);

    if(notree_score>undertree_score)cout<<notree_ptn;
    if(notree_score<undertree_score)cout<<undertree_ptn;
    if(notree_score==undertree_score)cout<<notree_ptn+undertree_ptn;
}

int main() {
    std::cerr << std::boolalpha;
    int t = 1;
    //cin >> t;
    rep(i, t) solve();
}