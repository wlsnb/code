#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn = 6561;
const int maxm = 8;
const ll mod = 1e9+9;
ll w1,w2;

ll fpow(ll x,ll p){
    ll res=1;
    while(p){
        if(p&1LL) res=res*x%mod;
        x=x*x%mod; p>>=1;
    }
    return res;
}

void FWT(ll *a,int limit){
    for(int i=1;i<limit;i*=3){
        for(int j=0,p=i*3;j<limit;j+=p){
            for(int k=0;k<i;++k){
                ll x=a[j+k], y=a[j+k+i], z=a[j+k+(i<<1)];
                a[j+k]=(x+y+z)%mod;
                a[j+k+i]=(x+w1*y+w2*z)%mod;
                a[j+k+(i<<1)]=(x+w2*y+w1*z)%mod;
            }
        }
    }
}

void IFWT(ll *a,int limit){
    for(int i=1;i<limit;i*=3){
        for(int j=0,p=i*3;j<limit;j+=p){
            for(int k=0;k<i;++k){
                ll x=a[j+k], y=a[j+k+i], z=a[j+k+(i<<1)];
                a[j+k]=(x+y+z)%mod;
                a[j+k+i]=(x+w2*y+w1*z)%mod;
                a[j+k+(i<<1)]=(x+w1*y+w2*z)%mod;
            }
        }
    }
    ll inv = fpow(limit,mod-2);
    for(int i=0;i<limit;++i) a[i]=a[i]*inv%mod;
}

int p;
ll a[8][maxn],b[8][maxn],c[8][maxn],k;

void fast_matrix(){
    int tp=8%p; k-=1;
    while(k){
        if(k%2==1){
            for(int i=0;i<p;++i) memset(c[i],0,sizeof(c[i]));
            for(int i=0;i<p;++i){
                for(int j=0;j<p;++j){
                    int s=(i*tp+j)%p;
                    for(int t=0;t<maxn;++t)
                        c[s][t]=(c[s][t]+a[i][t]*b[j][t])%mod;
                }
            }
            for(int i=0;i<p;++i) memcpy(a[i],c[i],sizeof(c[i]));
        }


        for(int i=0;i<p;++i) memset(c[i],0,sizeof(c[i]));
        for(int i=0;i<p;++i){
            for(int j=0;j<p;++j){
                int s=(i*tp+j)%p;
                for(int t=0;t<maxn;++t)
                    c[s][t]=(c[s][t]+b[i][t]*b[j][t])%mod;
            }
        }
        for(int i=0;i<p;++i) memcpy(b[i],c[i],sizeof(c[i]));
        
        k>>=1; tp=tp*tp%p;
    }
}

int main(){
    w1=fpow(2,(mod-1)/3); w2=w1*w1%mod;
    while(scanf("%lld %d",&k,&p)!=EOF){
        for(int i=0;i<p;++i){
            memset(a[i],0,sizeof(a[i]));
            memset(b[i],0,sizeof(b[i]));
        }
        for(int i=1,q=3;i<8;++i,q*=3) a[i%p][q]+=1;
        for(int i=0,q=1;i<8;++i,q*=3) b[i%p][q]+=1;
        for(int i=0;i<p;++i) FWT(a[i],maxn),FWT(b[i],maxn);
        fast_matrix(); IFWT(a[0],maxn);
        printf("%lld\n",a[0][0]);
    }
}
