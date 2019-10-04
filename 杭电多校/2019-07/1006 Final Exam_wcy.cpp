#include <cstdio>
#include <algorithm>
typedef long long ll;
using namespace std;
ll n,m,k,q;
int main(){
    int t; scanf("%d",&t);
    while(t--){
        scanf("%lld %lld %lld",&n,&m,&k); q=n-k+1;
        printf("%lld\n",m+1+(n-q)*(m/q+1));
    }
}