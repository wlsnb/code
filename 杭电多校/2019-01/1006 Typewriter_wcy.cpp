#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn = 5e5+100;
struct SAM{
    int next[maxn][26],fa[maxn],len[maxn];
    int root,tot,last;
    int newnode(int l){
        fa[tot]=-1;
        for(int i=0;i<26;++i)  next[tot][i]=-1;
        len[tot++]=l; return tot-1;
    }
    void init(){
        tot=0;
        last=root=newnode(0);
    }
    void extend(int x){
        int p=last; int cur=newnode(len[p]+1);
        while(p!=-1&&next[p][x]==-1){
            next[p][x]=cur; p=fa[p];
        }
        if(p==-1) fa[cur]=root;
        else{
            int q=next[p][x];
            if(len[q]==len[p]+1) fa[cur]=q;
            else{
                int tmp = newnode(len[p]+1);
                for(int i=0;i<26;++i) next[tmp][i]=next[q][i];
                fa[tmp]=fa[q]; fa[q]=fa[cur]=tmp;
                while(p!=-1&&next[p][x]==q){
                    next[p][x]=tmp; p=fa[p];
                }
            }
        }
        last=cur;
    }
}sam;
char s[maxn];
ll dp[maxn],p,q;
int n,m;

int main(){
    while(scanf("%s",s+1)!=EOF){
        n=strlen(s+1); scanf("%lld %lld",&p,&q);
        for(int i=0;i<=n;++i) dp[i]=i*p; sam.init();
        for(int i=1,j=0,cur=sam.root;i<=n;++i){
            if(j) j--;
            while(sam.fa[cur]!=-1&&sam.len[sam.fa[cur]]>=j) cur=sam.fa[cur];
            dp[i]=min(dp[i-1]+p,dp[i]);
            while(i+j<=n&&sam.next[cur][s[i+j]-'a']!=-1){
                cur=sam.next[cur][s[i+j]-'a']; j++;
                dp[i-1+j]=min(dp[i-1+j],dp[i-1]+q);
            }
            sam.extend(s[i]-'a');
        }
        printf("%lld\n",dp[n]);
    }    
}