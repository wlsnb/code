#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
const double eps = 1e-8;
const double INF = 1e16;
const int maxn = 1050;
struct Edge{
    int from,to;double cap,flow;
};

struct Dinic{
    int n,m,s,t;
    vector<Edge> edges;
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

    void add_edge(int from,int to,double cap){
        edges.push_back((Edge){from,to,cap,0.0});
        edges.push_back((Edge){to,from,0.0,0.0});
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
                Edge &e = edges[g[x][i]];
                if(!vis[e.to]&&e.cap>e.flow){
                    vis[e.to]=true;
                    d[e.to]=d[x]+1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    double dfs(int x,double a){
        if(x==t||a==0) return a;
        double flow=0, f;
        for(int &i=cur[x];i<g[x].size();++i){
            Edge &e = edges[g[x][i]];
            if(vis[e.to]&&d[x]+1==d[e.to]&&(f=dfs(e.to,min(a,e.cap-e.flow)))>0){
                e.flow+=f; edges[g[x][i]^1].flow-=f;
                flow+=f; a-=f;
                if(a==0) break;
            }
        }
        return flow;
    }

    double MaxFlow(){
        double flow = 0;
        while(bfs()){
            memset(cur,0,sizeof(cur));
            flow+=dfs(s,INF);
        }
        return flow;
    }
}dinic;

int n,m,u,v; ll a,b,c,ans;
ll win[maxn],wout[maxn];

int main(){
    //freopen("D:\\in.txt","r",stdin);
    while(scanf("%d %d",&n,&m)!=EOF){
        for(int i=1;i<=n;++i) win[i]=wout[i]=0.0;
        dinic.init(n+1,0,n+1); ans=0;
        while(m--){
            scanf("%d %d %lld %lld %lld",&u,&v,&a,&b,&c);
            win[u]+=a+b; win[v]+=a+b;
            wout[u]+=c+b; wout[v]+=c+b;
            dinic.add_edge(u,v,-b+(a+c)/2.0);
            dinic.add_edge(v,u,-b+(a+c)/2.0);
            ans+=a+b+c;
        }
        for(int i=1;i<=n;++i){
            dinic.add_edge(0,i,win[i]/2.0);
            dinic.add_edge(i,n+1,wout[i]/2.0);
        }
        
        ans-=(ll)(dinic.MaxFlow()+0.5);
        printf("%lld\n",ans); dinic.clear();
    }
}