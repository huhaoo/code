/***************************************************************
	File name: 5548.cpp
	Author: huhao
	Create time: Wed 17 Jun 2020 11:05:24 AM CST
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
//const int mod=19491001;
const int mod=1049874433,s2=380639328;
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1; a%=p;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
i64 inv(i64 a){ return power(a,mod-2,mod); }
i64 Mod(i64 a){ return a>=mod?a-mod:a; }
i64 &Add(i64 &a,i64 b){ return a=(a+b)%mod; }
const int N=4010,g=7;
i64 n,k,d,ans,w;
namespace C
{
	i64 f[N],F[N];
	void init(int n)
	{
		f[0]=1; fr(i,1,n) f[i]=f[i-1]*i%mod;
		F[n]=inv(f[n]); fd(i,n,1) F[i-1]=F[i]*i%mod;
	}
	i64 C(i64 a,i64 b){ return a>=b&&b>=0?f[a]*F[b]%mod*F[a-b]%mod:0; }
}
int main()
{
//	fr(i,1,mod-1) if((i64)i*i%mod==2){ printf("%d\n",i);}
//	return 0;
//	fr(i,1,mod-2) if((mod-1)%i==0&&power(g,i,mod)==1) return 1;
//	return 0;
	n=read(); k=read(); d=read(); i64 I=power(inv(d),k,mod); C::init(k); w=power(g,(mod-1)/d,mod);
	if(d==1){ printf("%lld\n",power(k,n,mod)); return 0; }
	else if(d==2) fr(i,0,k) Add(ans,power(i-(k-i)+mod,n*d,mod)*C::C(k,i));
	else if(d==3) fr(i,0,k) fr(j,0,k-i) Add(ans,power(i+j*w+(k-i-j)*w%mod*w,n*d,mod)*C::C(k,i)%mod*C::C(k-i,j));
	else if(d==4)
	{
		w=power(g,(mod-1)/(d*2),mod); i64 w1=w*inv(s2)%mod,w3=w*w%mod*w%mod*inv(s2)%mod;; I=I%mod;
		fr(i,-k,k) fr(j,-k,k) if((k-i)%2==0&&(k-j)%2==0) Add(ans,power(i*w1+j*w3,n*d,mod)*C::C(k,(k-i)/2)%mod*C::C(k,(k-j)/2));
	}
	else
	{
		static i64 f[N][N],g[N][N];
		f[0][k]=1;
		fr(i,0,k-1) fr(j,1,k+k-1)
		{
			Add(f[i+1][j],f[i][j]);
			Add(f[i+1][j-1],f[i][j]);
			Add(f[i+1][j+1],f[i][j]);
		}
		fr(i,-k,k) fr(j,-k,k)
		{
			g[i+k][j+k]=power(i+j*w,n*d,mod);
		}
		fr(t,0,k) fr(t0,-(k-t),k-t) fr(i,-t+t0,t+t0) fr(j,-t+t0,t+t0)
			Add(ans,f[t][i-t0+k]*f[t][j-t0+k]%mod*f[k-t][t0+k]%mod*((k-t)&1?-1:1)*g[i+k][j+k]%mod*C::C(k,t));
	}
	printf("%lld\n",(ans*I%mod+mod)%mod);
	return 0;
}
