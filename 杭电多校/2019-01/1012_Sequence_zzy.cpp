#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=262144,maxm=2e6+10,mo=998244353;
const LL PN=262144,p=998244353,g=3;

long long Pow(long long x,long long pow)
{
	long long res=1;
	while (pow)
	{
		if (pow&1) (res*=x)%=mo;
		(x*=x)%=mo;
		pow>>=1;
	}
	return res;
}

void FFT(LL *arr,int N,int *rev,LL *W)
{
	for (int i=0;i<N;i++) if (i<rev[i]) swap(arr[i],arr[rev[i]]);
	for (int i=1,ws=N>>1;i<N;i<<=1,ws>>=1)
	for (int j=0;j<N;j+=(i<<1))
	for (int k=0,wk=0;k<i;k++,wk+=ws)
	{
		LL x=arr[j+k],y=W[wk]*arr[j+k+i]%mo;
		arr[j+k]=(x+y)%mo,arr[j+k+i]=(x-y+mo)%mo;
	}
}

int rev[maxn];
long long W[maxn];
int N;

void Init(int n)
{
	N=1;
	while (N<n*2) N<<=1;
	for (int i=1;i<N;i++) rev[i]=(rev[i>>1]>>1)|((i&1)*(N>>1));
	W[0]=1,W[1]=Pow(g,(p-1)/N);
	for (int i=2;i<N;i++) W[i]=W[i-1]*W[1]%mo;
}

long long a[maxn];
long long f[maxn];
long long prod[maxm],inv[maxm],prodinv[maxm];
int cnt[4];
int n,m;

long long C(long long x,long long y) {return x<y?0:prod[x]*prodinv[y]%mo*prodinv[x-y]%mo;}

int main()
{
//	freopen("test.in","r",stdin);
	prod[0]=prodinv[0]=prod[1]=prodinv[1]=inv[1]=1;
	for (int i=2;i<=2000000;i++)
		prod[i]=prod[i-1]*i%mo,
		inv[i]=(mo-mo/i)*inv[mo%i]%mo,
		prodinv[i]=prodinv[i-1]*inv[i]%mo;
	int T;
	scanf("%d",&T);
	while (T--)
	{
		memset(cnt,0,sizeof(cnt));
		scanf("%d%d",&n,&m);
		Init(n);
		for (int i=0;i<n;i++) scanf("%lld",&a[i]);
		for (int i=1,x;i<=m;i++) scanf("%d",&x),cnt[x]++;
		for (int i=n;i<N;i++) a[i]=f[i]=0;
		long long invN=Pow(N,mo-2);

		memset(f,0,sizeof(long long)*N);
		if (cnt[1]==0) f[0]=1;
		else for (int i=0;i<n;i++) f[i]=C(cnt[1]+i-1,i);
		FFT(f,N,rev,W);
		FFT(a,N,rev,W);
		for (int i=0;i<N;i++) (a[i]*=f[i])%=mo;
		reverse(a+1,a+N);
		FFT(a,N,rev,W);
		for (int i=0;i<n;i++) (a[i]*=invN)%=mo;
		for (int i=n;i<N;i++) a[i]=0;

		memset(f,0,sizeof(long long)*N);
		if (cnt[2]==0) f[0]=1;
		else for (int i=0;i*2<n;i++) f[i*2]=C(cnt[2]+i-1,i);
		FFT(f,N,rev,W);
		FFT(a,N,rev,W);
		for (int i=0;i<N;i++) (a[i]*=f[i])%=mo;
		reverse(a+1,a+N);
		FFT(a,N,rev,W);
		for (int i=0;i<n;i++) (a[i]*=invN)%=mo;
		for (int i=n;i<N;i++) a[i]=0;

		memset(f,0,sizeof(long long)*N);
		if (cnt[3]==0) f[0]=1;
		else for (int i=0;i*3<n;i++) f[i*3]=C(cnt[3]+i-1,i);
		FFT(f,N,rev,W);
		FFT(a,N,rev,W);
		for (int i=0;i<N;i++) (a[i]*=f[i])%=mo;
		reverse(a+1,a+N);
		FFT(a,N,rev,W);
		for (int i=0;i<n;i++) (a[i]*=invN)%=mo;
		for (int i=n;i<N;i++) a[i]=0;

		long long ans=0;
		for (int i=0;i<n;i++) ans^=a[i]*(i+1);
		printf("%lld\n",ans);
	}
	return 0;
}

