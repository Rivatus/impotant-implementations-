/* Problem Statement: 
  There are n buildings and n − 1 undirected roads connecting the buildings such that the network of roads forms a tree.
  Outside every building there is a vehicle that you can rent. The cost of the vehicle at building i is ci per unit distance
  travelled, and additionally a base cost of ri to rent. So if you choose to rent the vehicle and travel d units distance, the
  rental costs you a total of dci + ri.

  The problem is to calculate the minimum cost to travel from building 1 to building i for all i. For each travel calculation,
  you should move through the shortest path, i.e. the simple path from building 1 to i.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ftype;
typedef pair<ftype,ftype> point;
#define pb push_back
#define mk make_pair
#define F first
#define S second
#define int ftype

ftype f(point a,  ftype x) {
    return (a.F*x)+a.S;
}
// y = m*x + c kind of. 

const long long maxn = 2e9,mn=1e7;
struct node{
    int lc,rc;
    point p;
    node(){
        lc=rc=0;
        p.F=0;
        p.S=1ll<<62;
    }
};
// p is the line where the mid of node is minimum.
// lc and rc needs to be stored as this is sparse tree. 

vector<node> nodes(mn);
int stx;
void add_line(point nw, int v, long long l = 0, long long r = maxn) {
    int m = (l + r)>>1;
    bool lef = f(nw, l) < f(nodes[v].p, l);
    bool mid = f(nw, m) < f(nodes[v].p, m);
    if(mid)swap(nodes[v].p, nw);
    if(r==l)return;
    else if(lef != mid) {
        // copy node before chaning to maintain persistence.  
        nodes[++stx]=nodes[nodes[v].lc];
        nodes[v].lc=stx;
        add_line(nw, stx, l, m);
    } else {
        // copy node before chaning to maintain persistence.  
        nodes[++stx]=nodes[nodes[v].rc];
        nodes[v].rc=stx;
        add_line(nw, stx, m+1, r);
    }
}

ftype get(int x, int v, int l = 0, int r = maxn) {
    int m = (l + r) >>1;
    if(r==l) return f(nodes[v].p, x);
    if(x <= m)return min(f(nodes[v].p, x), get(x, nodes[v].lc, l, m));
    return min(f(nodes[v].p, x), get(x,nodes[v].rc, m+1, r));
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    int b[n],c[n],r[n],d[n];
    long long ans[n];ans[0]=d[0]=0;
    vector<pair<int,int>> g[n];
    for(int i=1;i<n;++i){
        int u,v,d;
        cin>>u>>v>>d;
        --u;--v;
        g[u].pb(mk(v,d));
        g[v].pb(mk(u,d));
    }
    for(int i=0;i<n;++i)cin>>c[i]>>r[i];
    nodes[0].p.F=0;
    nodes[0].p.S=1ll<<62;
    stx=1;
    b[0]=1;
    point temp;
    bool visit[n]={0};
    queue<int> q;q.push(0);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        visit[u]=1;
        temp.F=c[u];
        temp.S=r[u]-(c[u]*1ll*d[u])+ans[u];
        add_line(temp,b[u]);
        for(auto v:g[u]){
            if(!visit[v.F]){
                d[v.F]=d[u]+v.S;
                ans[v.F]=get(d[v.F],b[u]);
                // Create a copy of the parent node for child. 
                nodes[b[v.F]=++stx]=nodes[b[u]];
                q.push(v.F);
            }
        }
    }
    for(int i=1;i<n;++i)cout<<ans[i]<<" ";
    return 0;
}
