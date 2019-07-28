#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1<<20;
const ll mod = 998244353;
ll inv2;
ll fpow(ll x,ll p){
    ll res=1;
    while(p){
        if(p%2) res=res*x%mod;
        x=x*x%mod; p>>=1;
    }
    return res;
}
void FWT_XOR(ll *a,int n,int opt){
    for(int i=1;i<n;i<<=1){
        for(int j=0,p=(i<<1);j<n;j+=p){
            for(int k=0;k<i;++k){
                int X=a[j+k],Y=a[i+j+k];
                a[j+k]=(X+Y)%mod;a[i+j+k]=(X+mod-Y)%mod;
                if(opt==-1)a[j+k]=a[j+k]*inv2%mod,a[i+j+k]=a[i+j+k]*inv2%mod;
            }
        }
    }
}
ll fwt[maxn];

int main(){
    int n,m; inv2 = fpow(2,mod-2);
    while(scanf("%d",&n)!=EOF){
        m=1; while(m<n) m<<=1;
        for(int i=0;i<m;++i) fwt[i]=i<n?1:0;
        FWT_XOR(fwt,m,1);
        for(int i=0;i<m;++i) fwt[i]=fwt[i]*fwt[i]%mod*fwt[i]%mod;
        FWT_XOR(fwt,m,-1);
        ll ans1=0,ans2=0;
        for(int i=0;i<m;++i){
            ans1=(ans1+fwt[i]*i)%mod;
            ans2=(ans2+fwt[i]*i%mod*i)%mod;
        }
        ans1=ans1*ans1%mod;
        printf("%lld\n",(ans1-ans2+mod)%mod*inv2%mod);
    }
}