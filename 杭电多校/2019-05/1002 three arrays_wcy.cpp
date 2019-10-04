#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 3e6+100;
int a[maxn],b[maxn],c[maxn];
int n,m;

struct Tire01{
    int next[maxn][2],cnt[maxn];
    int root,tot;
    int newnode(){
        next[tot][0]=next[tot][1]=-1;
        cnt[tot++]=0; return tot-1;
    }
    void init(){
        tot=0;
        root=newnode();
    }
    void insert(int x){
        int now=root,y;
        for(int i=29;i>=0;--i){
            y=(x>>i)&1;
            if(next[now][y]==-1) next[now][y]=newnode();
            now=next[now][y];
            cnt[now]++;
        }
    }
}t1,t2;

int dfs(int d,int l,int r,int val){
    //printf("%d %d %d %d %d %d\n",d,l,t1.cnt[l],r,t2.cnt[r],val);
    if(d<0) return val; int res;
    if(~t1.next[l][0]&&~t2.next[r][0]){
        int u=t1.next[l][0],v=t2.next[r][0];
        res=dfs(d-1,u,v,val);
        t1.cnt[u]--; t2.cnt[v]--;
        if(!t1.cnt[u]) t1.next[l][0]=-1;
        if(!t2.cnt[v]) t2.next[r][0]=-1;
    }
    else if(~t1.next[l][1]&&~t2.next[r][1]){
        int u=t1.next[l][1],v=t2.next[r][1];
        res=dfs(d-1,u,v,val);
        t1.cnt[u]--; t2.cnt[v]--;
        if(!t1.cnt[u]) t1.next[l][1]=-1;
        if(!t2.cnt[v]) t2.next[r][1]=-1;
    }
    else if(~t1.next[l][0]&&~t2.next[r][1]){
        int u=t1.next[l][0],v=t2.next[r][1];
        res=dfs(d-1,u,v,val+(1<<d));
        t1.cnt[u]--; t2.cnt[v]--;
        if(!t1.cnt[u]) t1.next[l][0]=-1;
        if(!t2.cnt[v]) t2.next[r][1]=-1;
    }
    else if(~t1.next[l][1]&&~t2.next[r][0]){
        int u=t1.next[l][1],v=t2.next[r][0];
        res=dfs(d-1,u,v,val+(1<<d));
        t1.cnt[u]--; t2.cnt[v]--;
        if(!t1.cnt[u]) t1.next[l][1]=-1;
        if(!t2.cnt[v]) t2.next[r][0]=-1;
    }
    return res;
}

void readin(){
    scanf("%d",&n); t1.init(); t2.init();
    for(int i=1;i<=n;++i){
        scanf("%d",&m); t1.insert(m);
    }
    for(int i=1;i<=n;++i){
        scanf("%d",&m); t2.insert(m);
    }
}

int main(){
    int t; scanf("%d",&t);
    while(t--){
        readin();
        for(int i=1;i<=n;++i) c[i]=dfs(29,t1.root,t2.root,0);
        sort(c+1,c+1+n);
        for(int i=1;i<=n;++i) printf("%d%c",c[i],i==n?'\n':' ');
    }
}
