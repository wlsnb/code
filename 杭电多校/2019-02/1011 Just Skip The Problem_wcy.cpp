#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1e5+100;
const ll mod = 1e6+3;
ll n,dp[mod];

int main(){
    dp[0]=1;
    for(int i=1;i<mod;++i) dp[i]=dp[i-1]*i%mod;
    while(scanf("%lld",&n)!=EOF){
        if(n>=mod) printf("0\n");
        else printf("%lld\n",dp[n]);
    }
}