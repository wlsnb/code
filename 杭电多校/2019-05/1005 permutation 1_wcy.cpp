#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 25;
int a[maxn],vis[maxn<<1],n,k,cnt;
int ans[maxn];
void dfs(int d,int mn,int sm,int mx){
    if(d==n){
        cnt++; return;
    }
    for(int i=mx-n-sm+1;i<mn+n-sm;++i){
        if(vis[sm+i+25]) continue;
        a[d]=i; vis[sm+i+25]=1;
        dfs(d+1,min(mn,sm+i),sm+i,max(mx,sm+i));
        vis[sm+i+25]=0; if(cnt==k) return;
    }
}

int main(){
    int t; scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&k); cnt=0; 
        memset(vis,0,sizeof(vis)); vis[25]=1;
        dfs(1,0,0,0);
        for(int i=1;i<n;++i) a[i]+=a[i-1]; ans[0]=0;
        for(int i=1;i<n;++i) ans[0]=min(ans[0],a[i]); ans[0]=-ans[0]+1;
        for(int i=1;i<n;++i) ans[i]=ans[0]+a[i];
        for(int i=0;i<n;++i) printf("%d%c",ans[i],i==n-1?'\n':' ');
    }
}