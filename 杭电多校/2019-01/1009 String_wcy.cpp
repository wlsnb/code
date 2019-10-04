#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 1e5+100;
int cnt[maxn][26],nex[maxn][26];
int n,k;
char s[maxn],ans[maxn];
int l[27],r[27];

bool check(int nx,int len){
    if(nx==-1) return false;
    bool res=true; int m=0,q=0;
    l[s[nx]-'a']--; r[s[nx]-'a']--;
    for(int i=0;i<26;++i){
        if(l[i]>cnt[nx+1][i]){
            res=false; break;
        }
        m+=max(l[i],0); q+=min(max(0,r[i]),cnt[nx+1][i]);
    }
    l[s[nx]-'a']++; r[s[nx]-'a']++;
    //printf("mmm%d\n",m);
    return res&&(m<=len)&&(q>=len);
}

bool solve(){
    int now=0;
    for(int i=0;i<k;++i){
        bool flg=true;
        for(int j=0;j<26&&flg;++j){
            if(r[j]>0&&check(nex[now][j],k-i-1)){
                now=nex[now][j]; r[j]--; l[j]--;
                flg=false; ans[i]=j+'a';
            }
        }
        if(flg) return false;
    }
    return true;
}

int main(){
    while(scanf("%s",s+1)!=EOF){
        scanf("%d",&k); n=strlen(s+1); l[26]=r[26]=0;
        for(int i=0;i<26;++i) scanf("%d %d",&l[i],&r[i]);
        
        for(int j=0;j<26;++j){
            for(int i=n,p=-1;i>=0;--i){
                nex[i][j]=p;
                if(i>0&&s[i]-'a'==j) p=i;
            }
			
            cnt[n+1][j]=0; cnt[n][j]=((s[n]-'a')==j);
            for(int i=n-1;i>=1;--i)
                cnt[i][j]=((s[i]-'a')==j)+cnt[i+1][j];
        }
        

        if(solve()){
            ans[k]='\0'; printf("%s\n",ans);
        }
        else printf("-1\n");
    }
}
