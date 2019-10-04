#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5+100;
const int M = 58;
const int D = 18;
char s[N>>1]; ll w[N>>1]; int n,m,l,r;

struct LB{
    ll x[M],y[M];
    void clear(){
        for(int i=0;i<M;++i) x[i]=0,y[i]=0;
    }
    void insert(ll p){
    	ll tmp=p;
    	for(int i=M-1;i>=0;i--){
		    if((1ll<<i)&p){
			    if(!x[i]){
                    x[i]=p; y[i]=tmp; return;
                }
			    else if(tmp>y[i]){
                    swap(y[i],tmp); swap(x[i],p);
			    }
			    p^=x[i];
    	    }
        }
    }
}lb[N];

struct SAM{
    int next[N][26],fa[N],len[N],cnt[N];
    int root,tot,last; int pos[N>>1];
    int newnode(int l){
        fa[tot]=-1; cnt[tot]=0;
        for(int i=0;i<26;++i)  next[tot][i]=-1;
        len[tot++]=l; return tot-1;
    }
    void init(){
        tot=0;
        last=root=newnode(0);
    }
    void extend(int x,int ep){
        int p=last; int cur=newnode(len[p]+1);
        cnt[cur]=1; pos[ep]=cur;
        while(p!=-1&&next[p][x]==-1){
            next[p][x]=cur; p=fa[p];
        }
        if(p==-1) fa[cur]=root;
        else{
            int q=next[p][x];
            if(len[q]==len[p]+1) fa[cur]=q;
            else{
                int tmp = newnode(len[p]+1);
                memcpy(next[tmp],next[q],sizeof(next[q]));
                fa[tmp]=fa[q]; fa[q]=fa[cur]=tmp;
                while(p!=-1&&next[p][x]==q){
                    next[p][x]=tmp; p=fa[p];
                }
            }
        }
        last=cur;
    }
    int head[N],nex[N],to[N],tol,f[N][D];
    ull ans[N];
    void build(){
        for(int i=0;i<tot;++i) head[i]=-1; fa[0]=tol=0;
        for(int i=1;i<tot;++i){
            to[tol]=i; nex[tol]=head[fa[i]];
            head[fa[i]]=tol++;
        }
    }
    void dfs(int u){
        f[u][0]=fa[u]; lb[u].clear();
        for(int i=1;i<D;++i) f[u][i]=f[f[u][i-1]][i-1];
        for(int i=head[u];~i;i=nex[i]){
            dfs(to[i]); cnt[u]+=cnt[to[i]];
            for(int j=M-1;j>=0;--j){
                if(!lb[to[i]].x[j]) continue;
                lb[u].insert(lb[to[i]].y[j]);
            }
        }
        lb[u].insert(w[cnt[u]]); ans[u]=0;
        for(int i=0;i<M;++i) ans[u]+=lb[u].y[i];
    }
    int query(int l,int r){
        int u=pos[r];
        for(int i=D-1;i>=0;--i){
            if(len[f[u][i]]>=r-l+1) u=f[u][i];
        }
        return u;
    }
}sam;


int main(){
    int t; scanf("%d",&t);
    while(t--){
        scanf("%d %s",&n,s); sam.init();
        for(int i=1;i<=n;++i) scanf("%lld",&w[i]);
        for(int i=0;i<n;++i) sam.extend(s[i]-'a',i+1);
        sam.build(); sam.dfs(sam.root);
		scanf("%d",&m);
        while(m--){
            scanf("%d %d",&l,&r);
            printf("%llu\n",sam.ans[sam.query(l,r)]);
        }
    }
}