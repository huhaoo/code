/***************************************************************
	File name: 138.cpp
	Author: huhao
	Create time: Tue 24 Sep 2019 08:44:36 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
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
const int N=60,mod=1000000007;
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	a%=p;
	while(b)
	{
		if(b&1)
			r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r;
}
i64 inv(i64 a)
{
	return power(a,mod-2,mod);
}
i64 B[N]={1,1*inv(2)%mod,1*inv(6)%mod,0,(mod-1)*inv(30)%mod,0,1*inv(42)%mod,0,(mod-1)*inv(30)%mod,0,5*inv(66)%mod};
i64 C[N][N];
i64 v[N][N][N],f[N][N][N];
i64 sum(i64 n,i64 k)//求\sum_{i=1}^ni^k
{
	if(!k)
		return n;
	i64 ans=0;
	fr(i,0,k)
		ans=(ans+power(n,k+1-i,mod)*C[k+1][i]%mod*B[i])%mod;
	ans=ans*inv(k+1)%mod;
	return ans;
}
i64 calc(i64 n,i64 a,i64 b,i64 c,i64 k1,i64 k2,i64 m)
{
//	printf("%lld %lld %lld %lld %lld %lld\n",n,a,b,c,k1,k2);
	if(v[k1][k2][m])
		return f[k1][k2][m];
	v[k1][k2][m]=1;
	i64& ans=f[k1][k2][m];
	ans=0;
	if(n<0)
		return ans=0;
	if(!k2)
		return ans=sum(n,k1)+(k1==0);//包括0^0，下同
	if(a*n+b<c)
		return ans=0;
	if(!a)
		return ans=(sum(n,k1)+(k1==0))*power(b/c,k2,mod)%mod;
	if(a>=c||b>=c)
	{
		i64 A=a/c,B=b/c;
		ans=0;
		i64 _A=1,_B=1;
		fr(i,0,k2)
		{
			_B=1;
			fr(j,0,k2-i)
			{
				ans=(ans+_A*_B%mod*C[k2][i]%mod*C[k2-i][j]%mod*calc(n,a%c,b%c,c,k1+i,k2-i-j,m+1))%mod;
				_B=_B*B%mod;
			}
			_A=_A*A%mod;
		}
		return ans;
	}
	i64 _n=(a*n+b-c)/c;
	ans=power(_n+1,k2,mod)*sum(n,k1)%mod;//这个和后面要减去的都没算0^0
	i64 Inv=inv(k1+1);
	fr(i,0,k2-1)
		fr(j,0,k1)
			ans=(ans-calc(_n,c,c-b-1,a,i,k1+1-j,m+1)*C[k2][i]%mod*C[k1+1][j]%mod*B[j]%mod*Inv%mod+mod)%mod;
	return ans;
}
int main()
{
	fr(i,0,20)
		C[i][i]=C[i][0]=1;
	fr(i,1,20)
		fr(j,1,i-1)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	i64 T=read();
	while(T--)
	{
		memset(v,0,sizeof(v));
		i64 n=read(),a=read(),b=read(),c=read(),k1=read(),k2=read();
		printf("%lld\n",calc(n,a,b,c,k1,k2,1));
	}
	return 0;
}
