#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long ll;
using namespace std;
const int N = 2e5+100;
const int M = 1<<19;
const ll INF = 1e16;
ll a[N],tr[M],lz[M]; //维护区间最小值+单点取min
int dp[N];
int n,m;

void down(int k){
    if(lz[k]==0) return;
    int lk=k*2+1,rk=k*2+2;
    lz[lk]+=lz[k]; lz[rk]+=lz[k];
    tr[lk]+=lz[k]; tr[rk]+=lz[k];
}

void up(int k){
    tr[k]=min(tr[k*2+1],tr[k*2+2]);
    lz[k]=0;
}

int query(ll q,int k,int l,int r){
    if(l==r) return tr[k]<=q ? l : -1;
    int lk=k*2+1,rk=k*2+2,mid=(l+r)>>1;
    down(k); int res;
    if(tr[rk]<=q) res=query(q,rk,mid+1,r);
    else res=query(q,lk,l,mid);
    up(k); return res;
}

void add(int a,int b,ll q,int k,int l,int r){
    if(a>r||b<l) return;
    if(a<=l&&r<=b){
        lz[k]+=q; tr[k]+=q;
        return;
    }
    down(k);
    int lk=k*2+1,rk=k*2+2,mid=(l+r)>>1;
    add(a,b,q,lk,l,mid); add(a,b,q,rk,mid+1,r);
    up(k);
}

void modify(int i,ll q,int k,int l,int r){
    if(l==r){
        tr[k]=min(tr[k],q);
        return;
    }
    down(k);
    int mid=(l+r)>>1;
    if(i<=mid) modify(i,q,k*2+1,l,mid);
    else modify(i,q,k*2+2,mid+1,r);
    up(k);
}

void init(int k,int l,int r){
    lz[k]=0; tr[k]=INF;
    if(l==r) return;
    int lk=k*2+1,rk=k*2+2,mid=(l+r)>>1;
    init(lk,l,mid); init(rk,mid+1,r);
}

bool check(ll k){
    init(0,0,n); modify(0,0,0,0,n);
    for(int i=1;i<=n;++i){
        add(0,n,a[i],0,0,n);
        int q=query(k,0,0,n);
        if(q==-1) continue; dp[i]=q+1;
        if(dp[i]>=m) return true;
        modify(dp[i],0,0,0,n);
    }
    return false;
}

int main(){
    int t; scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&m); ll l=-INF,r=-INF,mid;
        for(int i=1;i<=n;++i){
            scanf("%lld",&a[i]); r=max(r,a[i]);
        }
        while(r-l>1){
            mid=(l+r)>>1;
            if(check(mid)) r=mid;
            else l=mid;
        }
        printf("%lld\n",r);
    }
}