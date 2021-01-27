// Solution of https://codeforces.com/contest/631/problem/E using convex hull trick(Lichao tree)
// Material : https://robert1003.github.io/2020/02/06/li-chao-segment-tree.html
// Important : Here range l,r denotes [l,r). With this a bug is avoided which is if we take [l,r] then when both l and r are negative the update [l,mid] can result in infinite 
//             recursion. E.g: l = -7, r = -6. mid = (l+r)/2 = -6 so [l,mid] = [-7,-6], resulting in infinite recursion.

#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define F first
#define S second
typedef long long ll;
typedef pair<int, int> pii;
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
const int N = 1000000;
struct line{
    ll m,c;
    ll operator()(ll x) { return m*x + c; }
}Lichao[5*N];

void init() {
    for(int i=0;i<5*N;++i) Lichao[i].m = -1;
}

void insert(int v,int l, int r,line cur) {
    if(Lichao[v].m == -1) {  // No line in this region
        Lichao[v] = cur;
        return ;
    }
    if(l+1==r) {
        if(Lichao[v](l) < cur(l)) Lichao[v] = cur;
        return ;
    }
    int mid = (l+r)/2; 
    if(Lichao[v].m > cur.m) swap(Lichao[v] , cur);
    if(cur(mid) > Lichao[v](mid)) {
        swap(Lichao[v] , cur);
        insert(v<<1, l, mid, cur);
    } else
        insert((v<<1)|1, mid, r, cur);
}


ll query(int v, int l,int r, int pt) {
    if(Lichao[v].m == -1) return -1e18;
    if(l+1==r) return Lichao[v](pt);
    int mid = (l+r)/2;
    if(pt <= mid) return max(Lichao[v](pt), query(v<<1, l, mid, pt));
    else if(pt > mid) return max(Lichao[v](pt), query((v<<1)|1, mid, r, pt));
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); 
    int n;
    cin >> n; 
    int a[n+1];
    ll pre[n+1], S = 0, ans = 0; pre[0] = 0; 
    for(int i = 0; i < n ; ++i ) {
        cin >> a[i+1]; 
        S += (i+1)*1ll*(a[i+1]); 
        pre[i+1] = pre[i] + a[i+1];
    }
    ans = S;
    init();
    for(int i=0;i<n;++i) {
        if(i) {
            ll eval = query(1, -N, N+1, a[i+1]);
            ans = max(ans, S + pre[i] - (i+1)*1ll*a[i+1] + eval);
        }
        line temp; temp.m = (i+1); temp.c = -pre[i];
        if(i!=n-1) insert(1,-N,N+1, temp);
    }
    init();
    for(int i=n-1;i>=0;--i) {
        if(i!=n-1) {
            ll eval = query(1, -N, N+1, a[i+1]);
            ans = max(ans, S+pre[i+1]-(i+1)*1ll*a[i+1] + eval);   
        }
        line temp; temp.m = (i+1); temp.c = -pre[i+1];
        if(i) insert(1,-N,N+1,temp);
    }
    cout << ans ;
  return 0;
}
