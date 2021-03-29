/**************************************************************
	File name: 4774.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2/10/2019, 1:46:41 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
__int128 read()
{
	__int128 r=0,t=1,c=getchar();
	while(c<'0'||c>'9')
	{
		t=c=='-'?-1:1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#define N 100010
#include<set>
int T,n,m;
__int128 h[N],p[N],b[N],a[N],ans;
multiset<__int128>A;
__int128 exgcd(__int128 a,__int128 b,__int128 &x,__int128 &y)
{
	if(!b)
	{
		x=1;
		y=0;
		return a;
	}
	__int128 g=exgcd(b,a%b,x,y),k;
	k=x;
	x=y;
	y=k-(a/b)*y;
	return g;
}
__int128 gcd(__int128 a,__int128 b)
{
	return b?gcd(b,a%b):a;
}
int main()
{
	T=read();
	while(T--)
	{
		A.clear();
		A.insert(0);
		n=read();
		m=read();
		fr(i,1,n)
			h[i]=read();
		fr(i,1,n)
			p[i]=read();
		fr(i,1,n)
			b[i]=read();
		fr(i,1,m)
			A.insert(-read());
		fr(i,1,n)
		{
			multiset<__int128>::iterator it=A.lower_bound(-h[i]);
			if(*it==0)
				it--;
			a[i]=-*it;
			A.erase(it);
			A.insert(-b[i]);
		}
		ans=0;
		fr(i,1,n)
			ans=max(ans,(h[i]+a[i]-1)/a[i]);
		fr(i,1,n)
		{
			__int128 g=gcd(a[i],p[i]),x,y;
			if(g!=1)
			{
				if(h[i]%g)
				{
					printf("-1\n");
					goto end;
				}
				h[i]/=g;
				a[i]/=g;
				p[i]/=g;
			}
//			printf("%lld %lld\n",a[i],p[i]);
			exgcd(a[i],p[i],x,y);
			a[i]=x;
			a[i]=(a[i]*h[i]%p[i]+p[i])%p[i];
		}
		fr(i,2,n)
		{
			__int128 g=gcd(p[1],p[i]),k1,ki;
			if((a[i]-a[1])%g)
			{
				printf("-1\n");
				goto end;
			}
			exgcd(p[1],p[i],k1,ki);
			k1*=(a[i]-a[1])/g;
			a[1]=k1*p[1]+a[1];
			p[1]*=p[i]/g;
			a[1]=(a[1]%p[1]+p[1])%p[1];
		}
		printf("%lld\n",(long long)(a[1]+p[1]*((ans-a[1]+p[1]-1)/p[1])));
		end:;
	}
	return 0;
}