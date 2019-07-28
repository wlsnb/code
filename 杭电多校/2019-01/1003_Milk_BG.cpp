#include<bits/stdc++.h>
#define ll long long
#define N 40005
using namespace std;
int T;
ll dp[N],dp1[N],dp2[N],f[N],f1[N],f2[N],g[N],g1[N],g2[N],h[N],lst[N],now,sum,n,m,k,mid;
const ll INF =1e18;
struct he{
	ll r,c,t;
}a[N],b[N],c[N];
bool cmp(he a,he b){
	if(a.r!=b.r)return a.r<b.r;
	return a.c<b.c;
}
int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld%lld",&n,&m,&k);
	//	if(!T){
	//		cerr<<T<<endl;
	//}
		mid=(m+1)/2;
		for(int i=1;i<=k;i++){
			scanf("%lld%lld%lld",&a[i].r,&a[i].c,&a[i].t);
		}
		sort(a+1,a+1+k,cmp);
		for(int i=1;i<=k;i++)
			h[i]=lst[i]=INF;
		h[0]=lst[0]=0;
		now=0;sum=0;
		if(a[1].r!=1)
			a[0].r=1,lst[0]=mid-1;	
		a[k+1].r=a[k].r+1;		
		for(int i=1;i<=k;i++)
		if(a[i].r!=1){
			int cnt1=0,cnt2=0;
			now=a[i].r-a[i-1].r;
			for(int j=i;a[j].r==a[i].r;j++){
				if(a[j].c<mid) b[++cnt1]=a[j];
				else c[++cnt2]=a[j];
				i=j;
			}
			int cnt=cnt1+cnt2;
			for(int j=0;j<=sum;j++)
				lst[j]+=now;
			c[0].c=mid;
			b[cnt1+1].c=mid;
			for(int j=1;j<=cnt1;j++) f1[j]=g1[j]=dp1[j]=INF;f1[0]=g1[0]=dp1[0]=0;
			for(int j=1;j<=cnt1;j++){
				for(int p=j-1;p>=0;p--){
					dp1[p]=dp1[p]+(b[cnt1-j+2].c-b[cnt1-j+1].c);
					dp1[p+1]=min(dp1[p+1],dp1[p]+b[cnt1-j+1].t);
				//	if(T==1111&&i==7) cerr<<p+1<<" "<<dp1[p+1]<<endl;
					f1[p+1]=min(f1[p+1],dp1[p+1]);
					g1[p+1]=min(g1[p+1],dp1[p+1]+abs(mid-b[cnt1-j+1].c));
				}
			}
		//	if(T==1111&&i==7) cerr<<f1[cnt1]<<" "<<f1[2]<<endl;
			for(int j=1;j<=cnt2;j++) f2[j]=g2[j]=dp2[j]=INF;f2[0]=g2[0]=dp2[0]=0;
			for(int j=1;j<=cnt2;j++){
				for(int p=j-1;p>=0;p--){
					dp2[p]=dp2[p]+(c[j].c-c[j-1].c);
					dp2[p+1]=min(dp2[p+1],dp2[p]+c[j].t);
					f2[p+1]=min(f2[p+1],dp2[p+1]);
					g2[p+1]=min(g2[p+1],dp2[p+1]+abs(mid-c[j].c));
				}
			}
			for(int j=1;j<=cnt;j++)	f[j]=g[j]=INF;f[0]=g[0];
			for(int j=0;j<=cnt1;j++)
				for(int p=0;p<=cnt2;p++)
				if((j+p)>0){
					f[j+p]=min(f[j+p],min(f1[j]+g2[p],g1[j]+f2[p]));
					g[j+p]=min(g[j+p],g1[j]+g2[p]);
				}
			for(int j=sum;j>=0;j--){
				for(int p=cnt;p>=1;p--){
				//	if(lst[j]+f[p]>=INF){
				//		cerr<<T<<" "<<i<<endl;
				//		cerr<<cnt1<<" "<<cnt2<<" "<<cnt<<endl;
				//		cerr<<p<<" "<<f[p]<<" "<<f1[cnt1]<<endl;
				//		return 0;
				//	}
					h[j+p]=min(h[j+p],lst[j]+f[p]);
					lst[j+p]=min(lst[j+p],lst[j]+g[p]);
				}
			}
			sum+=cnt;
		}else{
			int cnt=0;
			for(int j=i;a[j].r==a[i].r;j++){
				b[++cnt]=a[j];i=j;
			}
			for(int j=1;j<=cnt;j++)	f[j]=g[j]=dp[j]=INF;f[0]=g[0]=dp[0]=0;
			b[0].c=1;
			for(int j=1;j<=cnt;j++){
				for(int p=j-1;p>=0;p--){
					dp[p]=dp[p]+(b[j].c-b[j-1].c);
					dp[p+1]=min(dp[p+1],dp[p]+b[j].t);
					f[p+1]=min(f[p+1],dp[p+1]);
					g[p+1]=min(g[p+1],dp[p+1]+abs(mid-b[j].c));
				}
			}
			sum+=cnt;
			for(int j=1;j<=cnt;j++){
				h[j]=f[j];
				lst[j]=g[j];
			}
			h[0]=0;
			lst[0]=mid-1;
		}
		for(int i=1;i<=k;i++)
			printf("%lld%c",h[i],i==k?'\n':' ');
	}
}
