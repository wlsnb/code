#include<bits/stdc++.h>
#define ll long long
#define MOD 998244353
#define N 105
using namespace std;
int T,p1[N],n,p2[N],a[N],b[N],vis[N],cnt;
ll f[N][N][N],ans;
ll dfs(int x,int l,int r){
	if(f[x][l][r]!=-1) return f[x][l][r];
	if(l==r)
		if((p1[a[x]]&&p2[a[x]]&&a[x]!=b[l])||(p1[b[l]]&&p2[b[l]]&&a[x]!=b[l])||(a[x]&&b[l]&&a[x]!=b[l]))
			return 0;
		else return 1;
	if(l==r+1) return 1;
	if(l>r) return 0;
	f[x][l][r]=0;
	if(p1[a[x]]) {
		if(p2[a[x]]) {
			if(p2[a[x]]>r||p2[a[x]]<l) return 0;
			ll tmp1=dfs(x+1,l,p2[a[x]]-1);
			ll tmp2=dfs(x+1+(p2[a[x]]-1)-l+1,p2[a[x]]+1,r);
			f[x][l][r]=tmp1*tmp2%MOD;
			return f[x][l][r];
		}else{
			for(int i=l;i<=r;i++)
				if(b[i]==0){
					ll tmp1=dfs(x+1,l,i-1);
					ll tmp2=dfs(x+1+(i-1)-l+1,i+1,r);
					(f[x][l][r]+=tmp1*tmp2%MOD)%=MOD;
				}
		}
	}else{
		for(int i=l;i<=r;i++){
			if(!(p2[b[i]]&&p1[b[i]])){
				ll tmp1=dfs(x+1,l,i-1);
					ll tmp2=dfs(x+1+(i-1)-l+1,i+1,r);
					(f[x][l][r]+=tmp1*tmp2%MOD)%=MOD;
			}
		}
	}
	return f[x][l][r];
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=0;i<=n+1;i++)
			for(int j=0;j<=n+1;j++)
				for(int k=0;k<=n+1;k++)
					f[i][j][k]=-1;
		for(int i=0;i<=n;i++) vis[i]=0,p1[i]=p2[i]=0;
		for(int i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			vis[a[i]]++;
			p1[a[i]]=i;
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&b[i]);
			vis[b[i]]++;
			p2[b[i]]=i;
		}
		vis[0]=0;
		p1[0]=p2[0]=0;
		ans=dfs(1,1,n);
		cnt=0;
		for(int i=1;i<=n;i++)
			if(!vis[i]) (ans*=(++cnt))%=MOD;
		printf("%lld\n",ans);
	}
}
