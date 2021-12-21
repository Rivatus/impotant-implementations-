// Problem link: https://codeforces.com/contest/1620/problem/G
// Editorial: https://codeforces.com/blog/entry/98061


#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define F first
#define S second
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<int, int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pld;
typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef vector<pll> vpl;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a,x) for (auto& a : x)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
const int mod = 998244353 ;

ll powmod(ll a,ll b) {ll res=1; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a;a=a*a;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}

int n ; 

void flip(int *H) {
    int j = (1<<n)-1;
    for(int i=0;i<(1<<(n-1));++i) {
        swap(H[i], H[i^j]);
    }
}

// Given H(x) = sum(G(y)) for all y which are subset of x, we can find H using mobius tranformation. 
// This function takes H as input and transforms it into G. 
// Therefore its also called as inverse Sum over subset dp (inverse SOS). 
void mobius_tranform(int *H) {
    for(int bit=n-1;bit>=0;--bit) {
        for(int i=(1<<n)-1;i>=0;--i) {
            if((i&(1<<bit)) != 0) {
                H[i] = (H[i] - H[i^(1<<bit)] + mod)%mod;
            }
        }
    }
}

int sos(int *H) {
    for(int bit=0;bit<n;++bit) {
        for(int mask=0;mask<(1<<n);++mask) {
            if(mask&(1<<bit)) H[mask] = (H[mask] + H[mask^(1<<bit)])%mod; 
        }
    }
}

void solve() {
    cin >> n; 
    string s[n]; 
    F0R(i,n) cin >> s[i]; 
    int cnt[n][26];
    F0R(i,n) {
        F0R(j,26) cnt[i][j] = 0; 
        for(char c: s[i]) cnt[i][c-'a']++;
    }
    int H[(1<<n)];
    for(int i=0;i<(1<<n);++i) {
        vi cr(26, 1e9);
        for(int j=0;j<n;++j) {
            if(i&(1<<j)) {
                F0R(k,26) cr[k] = min(cr[k], 1+cnt[j][k]);
            }
        }
        ll r = 1; 
        F0R(k,26) {
            if(cr[k] != 1e9) r = r*1ll*cr[k]%mod;
        }
        H[i] = r;
    }
    flip(H);
    mobius_tranform(H);
    ll sum =  0; 
    F0R(i, (1<<n)) sum = (sum+H[i])%mod;
    flip(H);
    sos(H);
    int t[(1<<n)];
    F0R(i, (1<<n)) t[i] = (sum-H[((1<<n)-1)^i]+mod)%mod;
    F0R(i, (1<<n)) H[i] = t[i]; 
    ll ans = 0; 
    F0R(i, (1<<n)) {
        ll k = 0, s1 = 0; 
        F0R(j,n) {
            if((i&(1<<j))) {
                k++;
                s1 += j+1;
            }
        }
        ll term = H[i]*k*s1;
        ans ^= term;
    }
    cout << ans << '\n';
}


int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); 
    int t=1,Tc=1;
    while(t--){
        solve();
    }
  return 0;
}
