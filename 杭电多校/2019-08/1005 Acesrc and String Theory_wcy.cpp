#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int N = 6e5+100;
char s[N];
int n,m,k;
struct SAM{
    int next[N][26],fa[N],len[N],endpos[N];
    int root,tot,last;ll ans;
    int newnode(int l){
        fa[tot]=-1; endpos[tot]=-1;
        for(int i=0;i<26;++i)  next[tot][i]=-1;
        len[tot++]=l; return tot-1;
    }
    void init(){
        tot=ans=0;
        last=root=newnode(0);
    }
    void extend(int x,int ep){
        int p=last; int cur=newnode(len[p]+1); endpos[cur]=ep;
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
    int head[N],nex[N],to[N],tol;
    void build(){
        for(int i=0;i<tot;++i) head[i]=-1; tol=0;
        for(int i=1;i<tot;++i){
            to[tol]=i; nex[tol]=head[fa[i]];
            head[fa[i]]=tol; tol++;
        }
    }
    int bit[N>>1];
    int sum(int i){
        int s=0;
        while(i>0){
            s+=bit[i];
            i-=i&-i;
        }
        return s;
    }
    void add(int i,int x){
        while(i<=n){
            bit[i]+=x;
            i+=i&-i;
        }
    }
    int sz[N],son[N];
    void dfs1(int u){
        sz[u]=1; son[u]=-1;
        for(int i=head[u];~i;i=nex[i]){
            dfs1(to[i]); sz[u]+=sz[to[i]];
            if(son[u]==-1||sz[son[u]]<sz[to[i]]) son[u]=to[i];
        }
    }
    void dfs2(int u,int v){
        if(~endpos[u]) add(endpos[u],v);
        for(int i=head[u];~i;i=nex[i]) dfs2(to[i],v);
    }
    void dfs3(int u,int rt){
        if(~endpos[u]) ans+=sum(min(n,endpos[u]+len[rt]/k))-sum(max(0,endpos[u]-len[rt]/k-1));
        for(int i=head[u];~i;i=nex[i]) dfs3(to[i],rt);
    }
    void dfs4(int u,bool clean){
        for(int i=head[u];~i;i=nex[i]){
            if(to[i]==son[u]) continue;
            dfs4(to[i],true);
        }
        if(~son[u]) dfs4(son[u],false);
        if(~endpos[u]){
            ans+=sum(min(n,endpos[u]+len[u]/k))-sum(max(0,endpos[u]-len[u]/k-1));
            add(endpos[u],1);
        }
        for(int i=head[u];~i;i=nex[i]){
            if(to[i]==son[u]) continue;
            dfs3(to[i],u); dfs2(to[i],1);
        }
        if(clean) dfs2(u,-1);
    }
}sam;



int main(){
    int t; scanf("%d",&t);
    while(t--){
        scanf("%d %s",&k,s); n=strlen(s); k-=1; sam.init();
        if(k==0){
            printf("%lld\n",1LL*n*(n+1)/2); continue;
        }
        for(int i=0;i<n;++i) sam.extend(s[i]-'a',i+1);
        sam.build(); sam.dfs1(sam.root); sam.dfs4(sam.root,true);
        printf("%lld\n",sam.ans);
    }
}