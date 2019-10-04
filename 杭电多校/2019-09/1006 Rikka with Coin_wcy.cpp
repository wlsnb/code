#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 110;
int n,x[N],a[N];
bool vis[N];

int solve(int i,int j,int k){
	int cnt=0,res=0;
	for(int o=1;o<=i;o++) a[++cnt]=1;
	for(int o=1;o<=j;o++) a[++cnt]=2;
	for(int o=1;o<=k;o++) a[++cnt]=5;

    memset(vis,false,sizeof(vis)); vis[0]=true;
	for(int o=1;o<=cnt;o++){
		for(int q=N-1;q>=a[o];q--)
			vis[q]|=vis[q-a[o]];
	}

	for(int o=1;o<=n;o++){
        int q=min(x[o],90+x[o]%10);
        int tt=(x[o]-q)/10; bool flg=false;
        for(;q>=0;q-=10){
            if(vis[q]){
                res=max(res,tt);
                flg=true;
                break;
            }
            tt++;
        }
        if(!flg) return -1;
        res=max(res,tt);
    }
	return res+i+j+k;
}

bool check(){
    for(int i=1;i<=n;++i){
        if(x[i]%10) return false;
        x[i]/=10;
    }
    return true;
}

int main(){
    int t; scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;++i) scanf("%d",&x[i]);
        if(!check()){
            printf("-1\n"); continue;
        }
        int ans=-1;
        for(int i=0;i<=1;++i){
            for(int j=0;j<=10;++j){
                for(int k=0;k<=1;++k){
                    int q=solve(i,j,k);
                    if(q==-1) continue;
                    if(ans==-1||ans>q) ans=q;
                }
            }
        }
        printf("%d\n",ans);
    }
}


/*
1
11
1010 1020 1030 1040 1050 1060 1070 1080 1090 1200 3010

11
10 20 30 40 50 60 70 80 90 200 3000

3
90 110 210
*/