/***************************************************************
	File name: min25.cpp
	Author: huhao
	Create time: Sun 14 Jun 2020 07:48:41 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
i64 read()
{
	i64 r=0,t=1,c=getchar();
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
const int N=200010,w=100000,mod=1000000007;
const i64 i6=(mod+1)/6;
i64 s1[N],s2[N],S1[N],S2[N],n,sp[N],Sp[N],a[N],m;
i64 p[N],lst;
int c,v[N];
i64 &s(i64 m){ return m<=w?s1[m]:s2[n/m]; }
i64 &S(i64 m){ return m<=w?S1[m]:S2[n/m]; }
i64 solve(i64 n,int i)
{
	if(p[i]>n) return 0;
	i64 ans=((S(n)-Sp[i-1])-(s(n)-sp[i-1]))%mod;
#define f(p) ((p%mod)*((p-1)%mod)%mod)
	fr(j,i,c)
		if(p[j]*p[j]<=n)
			for(i64 P=p[j];P*p[j]<=n;P=P*p[j]) ans=(ans+f(P)*solve(n/P,j+1)%mod+f(P*p[j]))%mod;
		else break;
	return ans;
}
int main()
{
	n=read();
	fr(i,2,w)
	{
		if(!v[i]){ p[++c]=i; sp[c]=i; Sp[c]=(i64)i*i%mod; }
		fr(j,1,c)
			if(i*p[j]<=w)
			{
				v[i*p[j]]=1;
				if(i%p[j]==0) break;
			}
			else break;
	}
	fr(i,2,c) sp[i]=(sp[i]+sp[i-1])%mod;
	fr(i,2,c) Sp[i]=(Sp[i]+Sp[i-1])%mod;
	for(i64 i=1;i<=n;i=n/(n/i)+1) a[++m]=n/i;
	fr(i,1,m)
	{
		i64 W=a[i]%mod;
		s(a[i])=W*(W+1)/2%mod-1;
		S(a[i])=W*(W+1)%mod*(W+W+1)%mod*i6%mod-1;
	}
	fr(i,1,c) fr(J,1,m)
	{
		i64 j=a[J];
		if(p[i]*p[i]>j) break;
//		printf("%lld %lld\n",p[i],j);
		s(j)=(s(j)-p[i]*(s(j/p[i])-sp[i-1]))%mod;
		S(j)=(S(j)-p[i]*p[i]%mod*(S(j/p[i])-Sp[i-1]))%mod;
	}
//	fr(i,1,m) printf("%lld %lld %lld\n",a[i],s(a[i]),S(a[i]));
	printf("%lld\n",(solve(n,1)%mod+1+mod)%mod);
	return 0;
}
