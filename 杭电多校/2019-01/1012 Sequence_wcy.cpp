#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll P = 998244353, G = 3, Gi = 332748118;
const int maxn = 1<<18;
const int maxm = 1200000;

ll fpow(ll x,ll p){
    ll res=1;
    while(p){
        if(p&1LL) res=res*x%P;
        x=x*x%P; p>>=1;
    }
    return res;
}
int l,r[maxn];

void NTT(ll *A,int limit,int opt){
    for(int i=0;i<limit;i++)
        if(i<r[i]) swap(A[i],A[r[i]]);
    for(int i=1;i<limit;i<<=1){
        ll wn=fpow((opt==1)?G:Gi,(P-1)/(i<<1));   //单位元
        for(int p=i<<1,j=0;j<limit;j+=p){
            ll w=1;
            for(int k=0;k<i;k++,w=w*wn%P){
                ll x=A[j+k],y=w*A[j+i+k]%P;
                A[j+k]=(x+y)%P; A[j+i+k]=(x-y+P)%P;
            }
        }
    }
}

int n,m,limit,cnt[4],op;
ll a[maxn],b[maxn];
ll inv[maxm],fac[maxm];

ll C(int m,int n){
    if(n<m) return 0;
    return fac[n]*inv[n-m]%P*inv[m]%P;
}

int main(){
    fac[0]=inv[0]=1;
    for(int i=1;i<maxm;++i){
        fac[i]=fac[i-1]*i%P;
        inv[i]=fpow(fac[i],P-2);
    }
    int t; scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&m); limit=1; l=0;
        for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
        while(limit<=(n*2)) limit<<=1,l++; ll nv=fpow(limit,P-2);
        for(int i=n+1;i<limit;++i) a[i]=0; a[0]=0;
        for(int i=0;i<limit;++i)
            r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
        cnt[1]=cnt[2]=cnt[3]=0;
        while(m--){
            scanf("%d",&op); cnt[op]++;
        }
    
        for(int i=1;i<=3;++i){
            if(!cnt[i]) continue;
            for(int j=0;j<limit;++j) b[j]=(j%i==0&&j<(limit>>1))?C(j/i,cnt[i]+j/i-1):0;
            NTT(a,limit,1); NTT(b,limit,1);
            for(int j=0;j<limit;++j) a[j]=a[j]*b[j]%P;
            NTT(a,limit,-1);
            for(int j=0;j<limit;++j) a[j]=(j<=n)?a[j]*nv%P:0;
        }
        ll ans=0;
        for(int j=1;j<=n;++j) ans^=j*a[j];
        printf("%lld\n",ans);
    }
}