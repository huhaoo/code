/***************************************************************
	File name: hdu6310.cpp
	Author: huhao
	Create time: Tue 14 Jan 2020 05:25:37 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9')
	{
		t=c=='-'?-1:1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		r=r*10+c-48;
		c=getchar();
	}
	return r*t;
}
#define i64 long long
const int N=210,M=8010;
i64 mod,f[N][M],l[N],n,m,Mod,L[N];
i64 _mod(i64 a){ return a>=Mod?a-Mod:a; }
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	while(b)
	{
		if(b&1) r=r*a%p;
		a=a*a%p; b>>=1;
	}
	return r;
}
namespace C
{
	i64 f[N],F[N];
	void init(int n)
	{
		f[0]=1;
		fr(i,1,n) f[i]=f[i-1]*i%mod;
		F[n]=power(f[n],mod-2,mod);
		fd(i,n,1) F[i-1]=F[i]*i%mod;
	}
	i64 C(i64 a,i64 b){ return f[a]*F[b]%mod*F[a-b]%mod; }
}
int main()
{
	n=200; mod=read();
	C::init(n);
	f[0][0]=1; Mod=mod*mod;
	fr(i,1,n)
	{
		fr(j,1,i) l[i]=std::max(l[i],l[j-1]+l[i-j]+std::min(j,i+1-j));
		fr(j,1,i)
		{
			i64 d=std::min(j,i+1-j);
			fr(k,d+L[j-1]+L[i-j],l[i])
			{
				i64 Ans=0;
				fr(o,std::max(L[j-1],k-d-l[i-j]),std::min(k-d-L[i-j],l[j])) Ans=_mod(Ans+f[j-1][o]*f[i-j][k-d-o]);
				f[i][k]=(f[i][k]+Ans%mod*C::C(i-1,j-1))%mod;
			}
		}
		while(!f[i][L[i]]) L[i]++;
	}
	while(scanf("%lld%lld",&n,&m)!=EOF) printf("%lld\n",m>l[n]?0:f[n][m]);
	return 0;
}
