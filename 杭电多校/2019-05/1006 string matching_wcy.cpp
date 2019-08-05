#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn = 1000100;
char s[maxn],ans[maxn];
int z[maxn],n;

void z_function(char *s){
    int l=0,r=0;
    for(int i=1;i<n;++i){
        z[i] = (i<=r) ? min(z[i-l],r-i+1) : 0;
        while (i+z[i]<n && s[z[i]]==s[z[i]+i]) ++z[i];
        if(i+z[i]-1 > r) l=i, r=i+z[i]-1;
    }
}


int main(){
    int t; scanf("%d",&t);
    while(t--){
        scanf("%s",s); n=strlen(s);
        z_function(s); ll ans=0;
        for(int i=1;i<n;++i){
            ans+=z[i]+(z[i]+i!=n);
        }
        printf("%lld\n",ans);
    }
}