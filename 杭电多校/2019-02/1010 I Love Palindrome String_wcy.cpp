#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn = 3e5+100;
struct PAM{
    int next[maxn][26],fail[maxn],len[maxn];
    int txt[maxn],cnt[maxn];
    int head[maxn],tol;
    int tot,root0,root1,last,size;
    void init(){
        last=tot=size=0; txt[size]=-1;
        root0=newnode(0); root1=newnode(-1);
        fail[root0]=1; fail[root1]=0;
    }
    int newnode(int l){
        len[tot]=l; cnt[tot]=0;
        memset(next[tot],0,sizeof(next[tot]));
        tot++; return tot-1;
    }
    int getfail(int x){
        while(txt[size-len[x]-1]!=txt[size]) x=fail[x];
        return x;
    }
    void extend(int c){
        txt[++size]=c; int now=getfail(last);
        if(!next[now][c]){
            int tmp=newnode(len[now]+2);
            fail[tmp]=next[getfail(fail[now])][c];
            next[now][c]=tmp;
        }
        last=next[now][c]; cnt[last]++;
    }
    void count(){
        for(int i=tot-1;~i;--i) cnt[fail[i]]+=cnt[i];
    }
    
    bool vis[maxn]; int ans[maxn];
    struct Edge{
        int to,next;
    }edges[maxn];
    void addedge(int from,int to){
        edges[tol].to=to; edges[tol].next=head[from];
        head[from]=tol++;
    }
    void build(){
        for(int i=1;i<=size;++i) ans[i]=0;
        for(int i=0;i<tot;++i) head[i]=-1; tol=0;
        for(int i=2;i<tot;++i) addedge(fail[i],i); 
    }
    void dfs(int u){
        vis[len[u]]=true;
        if(vis[(len[u]+1)>>1]) ans[len[u]]+=cnt[u];
        for(int i=head[u];~i;i=edges[i].next)
            dfs(edges[i].to);
        vis[len[u]]=false;
    }
}pam;

char s[maxn]; int n;

int main(){
    while(scanf("%s",s)!=EOF){
        n=strlen(s); pam.init();
        for(int i=0;i<n;++i) pam.extend(s[i]-'a'); pam.count();
        pam.build(); pam.dfs(pam.root0);
        for(int i=1;i<=n;++i){
            printf("%d",pam.ans[i]);
            if(i!=n) printf(" ");
        }
        printf("\n");
    }
}