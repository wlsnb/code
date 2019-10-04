#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5+100;
const int maxm = 6e6+100;
int a[maxn],n,q,k,s,t,p,x;
int T[maxn],lson[maxm],rson[maxm],c[maxm];
int m,tot;

int build(int l,int r){
    int root = tot++; c[root]=0;
    if(l!=r){
    int mid = (l+r)>>1;
        lson[root]=build(l,mid);
        rson[root]=build(mid+1,r);
    }
    return root;
}
int update(int root,int pos,int val){
    int newroot=tot++, tmp=newroot;
    c[newroot]=c[root]+val;
    int l=1,r=m;
    while(l<r){
        int mid = (l+r)>>1;
        if(pos<=mid){
            lson[newroot]=tot++; rson[newroot]=rson[root];
            newroot=lson[newroot]; root=lson[root];
            r=mid;
        }
        else{
            rson[newroot]=tot++; lson[newroot]=lson[root];
            newroot=rson[newroot]; root=rson[root];
            l=mid+1;
        }
        c[newroot]=c[root]+val;
    }
    return tmp;
}
int query(int a,int b,int p,int q,int l,int r){
    if(p==q) return 0;
    if(a>r||b<l) return 0;
    if(a<=l&&r<=b) return c[q]-c[p];
    int mid=(l+r)>>1;
    return query(a,b,lson[p],lson[q],l,mid)+query(a,b,rson[p],rson[q],mid+1,r);
}



int main(){
    int cas; scanf("%d",&cas);
    while(cas--){
        scanf("%d %d",&n,&q); m=0; x=0; tot=0;
        for(int i=1;i<=n;++i){
            scanf("%d",&a[i]); m=max(m,a[i]);
        }

        T[0]=build(1,m);
        for(int i=1;i<=n;++i) T[i]=update(T[i-1],a[i],1);

        while(q--){
            scanf("%d %d %d %d",&s,&t,&p,&k);
            s^=x; t^=x; p^=x; k^=x;
            
            int l=-1,r=m,mid;
            while(r-l>1){
                mid=(l+r)>>1;
                if(query(p-mid,p+mid,T[s-1],T[t],1,m)>=k) r=mid;
                else l=mid;
            }

            printf("%d\n",r); x=r;
        }
    }
}
