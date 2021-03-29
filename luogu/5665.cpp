#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9'){ t=c=='-'?-1:1; c=getchar(); }
	while(c>='0'&&c<='9'){ r=r*10+c-48; c=getchar(); }
	return r*t;
}
const int N=40000010;
int a[N];
i64 n,s[N],type;
#include<assert.h>
#include<deque>
#define pii std::pair<i64,int>
namespace run
{
	const i64 inf=(i64)1e18,w=100000000,M=10000000;
	int g[N];
	i64 ans0,ans1,ans2,ans3,t,P,sz,flag;
	pii tp;
	std::deque<pii> p;
	void print(i64 a,i64 w)
	{
		if(!w) return;
		print(a/10,w-1);
		printf("%lld",a%10);
	}
	int main()
	{
		fr(i,1,n)
		{
			g[i]=1;
			while(sz&&s[i]>=p.back().first)
			{
				tp=p.back();
				p.pop_back();
				sz--; flag=1;
			}
			if(flag) g[i]=tp.second+1;
			pii now=pii(s[i]+s[i]-s[g[i]-1],i);
			while(sz&&now.first<=p.front().first)
			{
				p.pop_front();
				sz--;
			}
			p.push_front(now);
			sz++;
		}
		P=n;
		while(P)
		{
			i64 S=s[P]-s[g[P]-1]; P=g[P]-1;
			i64 s0=S%w,s1=S/w;
			ans0+=s0*s0; ans1+=2*s0*s1; ans2+=s1*s1;
			ans1+=ans0/w; ans0%=w;
			ans2+=ans1/w; ans1%=w;
			ans3+=ans2/w; ans2%=w;
		}
		if(ans3)
		{
			printf("%lld",ans3);
			print(ans2,8); print(ans1,8); print(ans0,8);
		}
		else if(ans2)
		{
			printf("%lld",ans2);
			print(ans1,8); print(ans0,8);
		}
		else if(ans1)
		{
			printf("%lld",ans1);
			print(ans0,8);
		}
		else printf("%lld",ans0);
		putchar(10);
		return 0;
	}
}
namespace type1
{
	const int M=100010;
	int b[N];
	i64 x,y,z,m,p[M],l[M],r[M],mod=(1ll<<30)-1;
	int main()
	{
		x=read(); y=read(); z=read(); b[1]=read(); b[2]=read(); m=read();
		fr(i,1,m){ p[i]=read(); l[i]=read(); r[i]=read(); }
		fr(i,3,n) b[i]=(((x*b[i-1])&mod)+((y*b[i-2])&mod)+z)&mod;
		int j=1;
		fr(i,1,n)
		{
			a[i]=(b[i]%(r[j]-l[j]+1))+l[j];
			while(j<=m&&p[j]==i) j++;
		}
		return 0;
	}
}
int main()
{
	n=read(); type=read();
	if(type==0) fr(i,1,n) a[i]=read();
	else type1::main();
	fr(i,1,n) s[i]=s[i-1]+a[i];
	return run::main();
} 
