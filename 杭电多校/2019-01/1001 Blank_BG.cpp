#include<bits/stdc++.h>
#define ll long long
#define MOD 998244353
#define N 105
#define P pair<int,int>
using namespace std;
int T,n,m,k,k1,dp[3][N][N][N],l,r,x;
ll ans;
vector<P> V[N];
bool check(int i,int j,int p,int o){
	for(auto u:V[i]){
		if(u.second==1) if(o>=u.first) return false;
		if(u.second==2) if(p>=u.first||o<u.first) return false;
		if(u.second==3) if(j>=u.first||p<u.first) return false;
		if(u.second==4) if(j<u.first) return false;
	}
	return true;
}
int main(){
//	freopen("1.in","r",stdin);
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++) V[i].clear();
		for(int i=1;i<=m;i++){
			scanf("%d%d%d",&l,&r,&x);
			V[r].push_back(P(l,x));
		}		
		k=0;k1=1;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=n;j++)
				for(int p=0;p<=n;p++)
					dp[0][i][j][p]=dp[1][i][j][p]=0;
		dp[k1][0][0][0]=1;
		for(int i=0;i<n;i++){
			swap(k,k1);
			for(int j=0;j<=(i==0?0:i-1);j++)
				for(int p=(j==0?0:j+1);p<=(i==0?0:i-1);p++)
					for(int o=(p==0?0:p+1);o<=(i==0?0:i-1);o++)
					if(dp[k][j][p][o]){
						dp[k1][j][p][o]+=dp[k][j][p][o];if(dp[k1][j][p][o]>=MOD) dp[k1][j][p][o]-=MOD;
					//	if(o!=i)
						{dp[k1][j][p][i]+=dp[k][j][p][o];if(dp[k1][j][p][i]>=MOD) dp[k1][j][p][i]-=MOD;}
					//	if(p!=o)
						{dp[k1][j][o][i]+=dp[k][j][p][o];if(dp[k1][j][o][i]>=MOD) dp[k1][j][o][i]-=MOD;}
						//if(j!=p)
						{dp[k1][p][o][i]+=dp[k][j][p][o];if(dp[k1][p][o][i]>=MOD) dp[k1][p][o][i]-=MOD;}
					}
			for(int j=0;j<=(i==0?0:i);j++)
				for(int p=(j==0?0:j+1);p<=(i==0?0:i);p++)
					for(int o=(p==0?0:p+1);o<=(i==0?0:i);o++){
						if(!check(i+1,j,p,o))
							dp[k1][j][p][o]=0;
						dp[k][j][p][o]=0;
					}
			
		}
		ans=0;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=n;j++)
				for(int p=0;p<=n;p++){
					ans+=dp[k1][i][j][p];
					if(ans>=MOD)ans-=MOD;
				}
		printf("%lld\n",ans);
	}
}
