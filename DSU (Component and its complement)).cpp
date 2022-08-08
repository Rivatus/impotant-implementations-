// Solution to problem: https://codeforces.com/contest/1713/problem/E

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
 
ll powmod(ll a,ll b) {ll res=1; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a;a=a*a;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}

// dsu struct (supports enemy if the components are 0-1, i.e, there are only two types of components):
// find(v): Find group head of v's component.
// unite(a,b): Unite components a and b: Return 1 if it was possible, else return 0.
// createE(int a,int b): Make sure that a and b doesn't belong to same component (are complement component of each other), return 1 if that is possible else return 0.

struct dsu{
    int n;
    vi p,s,e;
   
    dsu(int N): n(N){
        p.resize(n); s.resize(n, 1); 
        e.resize(n, -1); iota(all(p), 0);
    }

    int find(int v) {
        return p[v] = (p[v]!=v)?find(p[v]):v;
    }

    bool createE(int a,int b) {
        a = find(a); b = find(b);
        if(a==b) return 0;
        if(e[a] == b) return 1;
        int u = e[a], v = e[b];
        if(u!=-1) {
            assert(unite(u,b));
            assert((e[e[find(u)]]==find(u)));
        }
        else if(v!=-1) {
            assert(unite(v,a));
            assert((e[e[find(v)]]==find(v)));
        }
        else e[a] = b, e[b] = a;
        return 1;
    }

    bool unite(int a,int b) {
        a = find(a); b = find(b);
        if(a==b){ return 1;}
        if(s[a] < s[b]) swap(a, b);
        if(e[b] == a) return 0;
        p[b] = a; s[a]+=s[b];
        if(e[b] != -1) {
            if(e[a] == -1) {
                e[a] = e[b];
                e[e[b]] = a;
            }
            else {
                int u = e[a], v = e[b];
                if(s[u] < s[v]) swap(u, v);
                p[v] = u; s[u]+=s[v];
                e[u] = a;
                e[a] = u;
            }
        }
        return 1;
    }
};

void solve() {
    int n; cin >> n;
    int a[n][n];
    vector<bool> apply(n, 0), assign(n, 0);

    F0R(i,n) F0R(j,n) cin >> a[i][j];
    dsu D(n);

    for(int i=0;i<n;++i) {
        for(int j=i+1;j<n;++j) {
            if(a[i][j] > a[j][i]) {
                // Want to swap: Contraint: apply[i]^apply[j] = 1
                if(D.createE(i,j));
                // cout << i << ' ' << j << ' ' << " Diff\n";
            } else if(a[i][j] < a[j][i]) {
                // Contraint: apply[i]^apply[j] = 0
                if(D.unite(i,j));
                // cout << i << ' ' << j << ' '  << " Same\n";
            }
        }
    }

    for(int i=0;i<n;++i)
        if(!assign[i] and D.p[i] == i) {
            assign[i] = 1; apply[i] = 1;
            if(D.e[i]!=-1) assign[D.e[i]] = 1, apply[D.e[i]] = 0;
        }

    for(int i=0;i<n;++i) {
        apply[i] = apply[D.find(i)];
    }

    F0R(i,n) {
        F0R(j,n) {
            int s = apply[i]^apply[j];
            if(s) cout << a[j][i] << ' ';
            else cout << a[i][j] << ' ';
        }
        cout << '\n'; 
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t=1,Tc=1;
    cin>>t;
    while(t--){
        solve();
    }
  return 0;
}
