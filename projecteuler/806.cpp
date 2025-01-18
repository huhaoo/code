#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9'){ t=c=='-'?-1:1; c=getchar(); }
	while(c>='0'&&c<='9'){ r=(r<<3)+(r<<1)+(c^48); c=getchar(); }
	return r*t;
}
const int N=1000010,mod=1000000007;
int n;
i64 f[N],F[N],p[N]; i64 ans;
void calc(int a,int b,int c,int p)
{
	fr(i,0,std::min({a,b,c}))
	{
		if((a-i)%2||(b-i)%2||(c-i)%2) continue;
		int A=(a-i)/2,B=(b-i)/2,C=(c-i)/2;
		ans=(ans+p*f[A+B+C+i]%mod*F[A]%mod*F[B]%mod*F[C]%mod*F[i]%mod*::p[i]%mod)%mod;
	}
}
int main()
{
	n=1000000;
	f[0]=1; fr(i,1,n) f[i]=f[i-1]*i%mod;
	fr(i,1,mod-1) if(i*f[n]%mod==1){ F[n]=i; break; }
	fd(i,n,1) F[i-1]=F[i]*i%mod;
	p[0]=1; fr(i,1,n) p[i]=p[i-1]*2%mod;

	n=100000;
	fr(i,0,n) fr(j,0,n-i)
	{
		int k=n-i-j; if((i^j^k)!=0) continue;
		calc(i,j,k,1);
		calc(i,j-1,k,1);
		calc(i,j,k-1,1);
		calc(i-2,j,k,mod-1);
		calc(i-1,j-1,k,1);
		calc(i-1,j,k-1,1);
//		ans++;
	}
	printf("%lld\n",ans*((mod+1)/2)%mod*(p[n]-1)%mod);
	return 0;
}