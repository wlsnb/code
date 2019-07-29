#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 4e3+100;
const int maxm = 1e7;
const int INF = 0x3f3f3f3f;
struct Edge{
    int to,next,cap,flow,cost;
}edge[maxm];
int head[maxn],tol;
int pre[maxn],dis[maxn];
bool vis[maxn];
int N;
void init(int n){
    N=n; tol=0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v,int cap,int cost){
    edge[tol].to=v;
    edge[tol].cap=cap;
    edge[tol].cost=cost;
    edge[tol].flow=0;
    edge[tol].next=head[u];
    head[u] = tol++;
    edge[tol].to=u;
    edge[tol].cap=0;
    edge[tol].cost=-cost;
    edge[tol].flow=0;
    edge[tol].next=head[v];
    head[v] = tol++;
}
bool spfa(int s,int t){
    queue<int> q;
    for(int i=0;i<N;++i){
        dis[i]=INF; vis[i]=false; pre[i]=-1;
    }
    dis[s]=0; vis[s]=true;
    q.push(s);
    while (!q.empty()){
        int u = q.front(); q.pop(); vis[u]=false;
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].to;
            if(edge[i].cap>edge[i].flow&&(dis[v]>dis[u]+edge[i].cost)){
                dis[v]=dis[u]+edge[i].cost;
                pre[v]=i;
                if(!vis[v]){
                    vis[v]=true;
                    q.push(v);
                }
            }
        }
    }
    if(pre[t]==-1) return false;
    else return true;
}
int minCostMaxflow(int s,int t,int &cost){
    int flow = 0; cost = 0;
    while (spfa(s,t)){
        int Min = INF;
        for(int i=pre[t];i!=-1;i=pre[edge[i^1].to]){
            if(Min>edge[i].cap-edge[i].flow)
                Min=edge[i].cap-edge[i].flow;
        }
        for(int i=pre[t];i!=-1;i=pre[edge[i^1].to]){
            edge[i].flow+=Min;
            edge[i^1].flow-=Min;
            cost+=edge[i].cost*Min;
        }
        flow+=Min;
    }
    return flow;
}

int a[maxn];

int n,k;
int main(){
    int t; scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&k);
        init(n*2+3); addedge(n*2+1,0,k,0);
        
        for(int i=1;i<=n;++i) scanf("%d",&a[i]); a[0]=0;

        for(int i=1;i<=n;++i){
            addedge(i+n,n*2+2,1,0);
            addedge(i,i+n,1,-a[i]);
        }

        for(int i=0;i<=n;++i){
            int q=INF;
            for(int j=i+1;j<=n;++j){
                if(a[i]<=a[j]&&a[j]<q){
                    addedge(i,j,INF,0);
                    if(i) addedge(i+n,j,1,0);
                    q=a[j];
                }
            }
        }

        int cost; minCostMaxflow(n*2+1,n*2+2,cost);
        printf("%d\n",-cost);
    }
}