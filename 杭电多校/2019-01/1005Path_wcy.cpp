#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn = 2e4+100;
const ll INF = 1e18;
struct HeapNode{
    ll d;int u;
    bool operator < (const HeapNode& rhs) const {
        return d>rhs.d;
    }
};
struct Edge1{
    int from,to; ll dist;
};
struct Dijkstra{
    int n,m;
    vector<Edge1> edges;
    vector<int> g[maxn];
    bool done[maxn];
    ll d[maxn]; vector<int> p[maxn];
    void init(int n){
        this->n=n;
    }
    void addedge(int from,int to,ll dist){
        edges.push_back((Edge1){from,to,dist});
        m=edges.size(); g[from].push_back(m-1);
    }
    void dijkstra(int s){
        priority_queue<HeapNode> Q;
        for(int i=1;i<=n;++i) d[i]=INF;
        d[s]=0;
        memset(done,false,sizeof(done));
        Q.push((HeapNode){0,s});
        while(!Q.empty()){
            HeapNode x=Q.top(); Q.pop();
            int u=x.u;
            if(done[u]) continue;
            done[u]=true;
            for(int i=0;i<g[u].size();++i){
                Edge1& e=edges[g[u][i]];
                if(d[e.to]>d[u]+e.dist){
                    d[e.to]=d[u]+e.dist; p[e.to].clear();
                    p[e.to].push_back(g[u][i]);
                    Q.push((HeapNode){d[e.to],e.to});
                }
                else if(d[e.to]==d[u]+e.dist){
                    p[e.to].push_back(g[u][i]);
                }
            }
        }
    }
    void clean(){
        for(int i=1;i<=n;++i){
            p[i].clear(); g[i].clear();
        }
        edges.clear();
    }
}dijk;

struct Edge2{
    int from,to;ll cap,flow;
};

struct Dinic{
    int n,m,s,t;
    vector<Edge2> edges;
    vector<int> g[maxn];
    bool vis[maxn];
    int d[maxn],cur[maxn];

    void init(int n,int s,int t){
        this->n=n; this->s=s; this->t=t;
    }

    void clear(){
        for(int i=0;i<=n;++i) g[i].clear();
        edges.clear();
    }

    void add_edge(int from,int to,ll cap){
        edges.push_back((Edge2){from,to,cap,0LL});
        edges.push_back((Edge2){to,from,0LL,0LL});
        m=edges.size();
        g[from].push_back(m-2);
        g[to].push_back(m-1);
    }

    bool bfs(){
        memset(vis,false,sizeof(vis));
        queue<int> Q;
        Q.push(s);
        d[s]=0; vis[s]=true;
        while(!Q.empty()){
            int x = Q.front(); Q.pop();
            for(int i=0;i<g[x].size();++i){
                Edge2 &e = edges[g[x][i]];
                if(!vis[e.to]&&e.cap>e.flow){
                    vis[e.to]=true;
                    d[e.to]=d[x]+1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    ll dfs(int x,ll a){
        if(x==t||a==0) return a;
        ll flow=0, f;
        for(int &i=cur[x];i<g[x].size();++i){
            Edge2 &e = edges[g[x][i]];
            if(vis[e.to]&&d[x]+1==d[e.to]&&(f=dfs(e.to,min(a,e.cap-e.flow)))>0){
                e.flow+=f; edges[g[x][i]^1].flow-=f;
                flow+=f; a-=f;
                if(a==0) break;
            }
        }
        return flow;
    }

    ll MaxFlow(){
        ll flow = 0;
        while(bfs()){
            memset(cur,0,sizeof(cur));
            flow+=dfs(s,INF);
        }
        return flow;
    }
}dinic;

int main(){
    int n,m,u,v; ll w;
    int t; scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&m); dijk.init(n); dinic.init(n,1,n);
        while(m--){
            scanf("%d %d %lld",&u,&v,&w);
            dijk.addedge(u,v,w);
        }
        dijk.dijkstra(1); 
        for(int i=1;i<=n;++i){
            for(int j=0;j<dijk.p[i].size();++j){
                dinic.add_edge(dijk.edges[dijk.p[i][j]].from,dijk.edges[dijk.p[i][j]].to,dijk.edges[dijk.p[i][j]].dist);
            }
        }
        printf("%lld\n",dinic.MaxFlow());
        dinic.clear(); dijk.clean();
    }
}