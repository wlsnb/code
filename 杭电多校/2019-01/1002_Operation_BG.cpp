#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int T,n,m,x,lstans,l,r,op;
struct L_B{
    int d[32],pl[32];
    void clear(){
        memset(d,0,sizeof(d));
        memset(pl,0,sizeof(pl));
    }
    void ins(int p,int val){
        for(int i=30;i>=0;i--)
        if((1<<i)&val){
            if(!d[i]){
                d[i]=val;
                pl[i]=p;
                return ;
            }else if(p>pl[i]){
            	swap(d[i],val);
            	swap(p,pl[i]);
            }
            val^=d[i];
        }
    }
    int find(int p){
    	int ans=0;
    	for(int i=30;i>=0;i--)
    		if(pl[i]>=p) ans=max(ans,ans^d[i]);
    	return ans;
    }
}a[N];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++) {
			scanf("%d",&x);
			a[i]=a[i-1];
			a[i].ins(i,x);
		}
		lstans=0;
		for(int i=1;i<=m;i++){
			scanf("%d",&op);
			if(op==0){
				scanf("%d%d",&l,&r);
				l=(l^lstans)%n+1;
				r=(r^lstans)%n+1;
				if(l>r) swap(l,r);
				lstans=a[r].find(l);
				printf("%d\n",lstans);
			}else{
				scanf("%d",&x);
				x^=lstans;
				n++;
				a[n]=a[n-1];
				a[n].ins(n,x);
			}
		}
	}
}
