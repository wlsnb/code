#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
typedef long long ll;
typedef set<int>::iterator iter;
const int N = 2e5+100;
int n,k;
char s[N];
struct SAM{
    int next[N][26],fa[N],len[N],lp[N],endpos[N];
    int root,tot=0,last;
    int txt[N];
    int newnode(int l,int p){
        fa[tot]=-1; lp[tot]=p; endpos[tot]=-1;
        for(int i=0;i<26;++i)  next[tot][i]=-1;
        len[tot++]=l; return tot-1;
    }
    void init(){
        tot=0; last=root=newnode(0,0);
    }
    void extend(int x,int ep){
        int p=last; int cur=newnode(len[p]+1,0); endpos[cur]=ep; txt[ep]=x;
        while(p!=-1&&next[p][x]==-1){
            next[p][x]=cur; p=fa[p];
        }
        if(p==-1) fa[cur]=root;
        else{
            int q=next[p][x];
            if(len[q]==len[p]+1) fa[cur]=q;
            else{
                int tmp = newnode(len[p]+1,lp[q]+len[q]-len[p]-1);
                memcpy(next[tmp],next[q],sizeof(next[q]));
                fa[tmp]=fa[q]; fa[q]=fa[cur]=tmp;
                while(p!=-1&&next[p][x]==q){
                    next[p][x]=tmp; p=fa[p];
                }
            }
        }
        last=cur;
    }
    int tt[N],c[26],ok[N],head[N],to[N],nex[N],tol;
    void build(){
        for(int i=0;i<26;++i) c[i]=0;
        for(int i=0;i<tot;++i) head[i]=-1; tol=0;
        for(int i=1;i<tot;++i) c[txt[lp[i]+len[i]-len[fa[i]]-1]]++;
        for(int i=1;i<26;++i) c[i]+=c[i-1];
        for(int i=1;i<tot;++i) tt[--c[txt[lp[i]+len[i]-len[fa[i]]-1]]]=i;
        for(int i=tot-2;i>=0;--i){
            nex[tol]=head[fa[tt[i]]]; to[tol]=tt[i];
            head[fa[tt[i]]]=tol; tol++;
        }
    }
    int tr[1<<18]={0,}; set<int> st;
    int query(int q){
        int k=0,l=0,r=n+1;
        while(l!=r){
            if(tr[k*2+2]>=q){
                k=k*2+2; l=((l+r)>>1)+1;
            }
            else{
                q-=tr[k*2+2]; r=(l+r)>>1;
                k=k*2+1;
            }
        }
        return l;
    }
    void add(int p,int v){
        int k=0,l=0,r=n+1;
        while(l!=r){
            tr[k]+=v;
            int mid=(l+r)>>1;
            if(p>mid){
                l=mid+1; k=k*2+2;
            }
            else{
                r=mid; k=k*2+1;
            }
        }
        tr[k]+=v;
    }

    int son[N],sz[N];
    void dfs1(int u){
        son[u]=-1; sz[u]=1;
        for(int i=head[u];~i;i=nex[i]){
            dfs1(to[i]); sz[u]+=sz[to[i]];
            if(son[u]==-1||sz[son[u]]<sz[to[i]]) son[u]=to[i];
        }
    }
    void dfs2(int u){
        if(~endpos[u]){
            iter it=st.upper_bound(endpos[u]); int l,r;
            if(it!=st.end()) r=*it; else r=-1;
            if(it!=st.begin()){ it--; l=*it; } else l=-1;
            if(~l) add(endpos[u]-l,1);
            if(~r) add(r-endpos[u],1);
            if(~l&&~r) add(r-l,-1);
            st.insert(endpos[u]);
        }
        for(int i=head[u];~i;i=nex[i]) dfs2(to[i]);
    }
    void dfs3(int u){
        if(~endpos[u]){
            iter it=st.upper_bound(endpos[u]); int l,r;
            if(it!=st.end()) r=*it; else r=-1; it--;
            if(it!=st.begin()){ it--; l=*it; } else l=-1;
            if(~l) add(endpos[u]-l,-1);
            if(~r) add(r-endpos[u],-1);
            if(~l&&~r) add(r-l,1);
            st.erase(endpos[u]);
        }
        for(int i=head[u];~i;i=nex[i]) dfs3(to[i]);
    }
    void dfs4(int u,bool clean){
        for(int i=head[u];~i;i=nex[i]){
            if(to[i]==son[u]) continue;
            dfs4(to[i],true);
        }
        if(~son[u]) dfs4(son[u],false);
        for(int i=head[u];~i;i=nex[i]){
            if(to[i]==son[u]) continue;
            dfs2(to[i]);
        }
        if(~endpos[u]){
            iter it=st.upper_bound(endpos[u]); int l,r;
            if(it!=st.end()) r=*it; else r=-1;
            if(it!=st.begin()){ it--; l=*it; } else l=-1;
            if(~l) add(endpos[u]-l,1);
            if(~r) add(r-endpos[u],1);
            if(~l&&~r) add(r-l,-1);
            st.insert(endpos[u]);
        }
        int high=min(query(k-1)-1,len[u]);
        int low=max(query(k),(~fa[u])?len[fa[u]]+1:1);
        ok[u]=high>=low?low:-1;
        if(clean) dfs3(u);
    }

    int l,r;
    bool dfs5(int u){
        if(~ok[u]){
            l=lp[u]+len[u]-ok[u]; r=l+ok[u]-1;
            l=n-1-l; r=n-1-r; swap(l,r);
            return true;
        }
        for(int i=head[u];~i;i=nex[i])
            if(dfs5(to[i])) return true;
        return false;
    }
}sam;



int main(){
    int t; scanf("%d",&t);
    while(t--){
        scanf("%s %d",s,&k); n=strlen(s); sam.init();
        for(int i=n-1;i>=0;--i) sam.extend(s[i]-'a',n-1-i);
        sam.build(); sam.dfs1(sam.root); sam.dfs4(sam.root,true);
        if(sam.dfs5(sam.root)){
            s[sam.r+1]='\0';
            printf("%s\n",s+sam.l);
        }
        else printf("-1\n");
    }
}