/**************************************************************
	File name: E.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2019/8/24 下午9:22:27
**************************************************************/
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
const int N=200010;
int n,f[N],w[N],a[N],b[N],v[N],m1,m2,m,r[N];
long long ans;
int cmp(int a,int b)
{
	return v[a]>v[b];
}
int getf(int a)
{
	return a==f[a]?a:f[a]=getf(f[a]);
}
int main()
{
	n=read();
	m1=read();
	m2=read();
	m=m1+m2;
	fr(i,1,n)
	{
		a[i]=read();
		b[i]=read()+m1;
		v[i]=read();
	}
	fr(i,1,m)
	{
		f[i]=i;
		w[i]=1;
	}
	fr(i,1,n)
		r[i]=i;
	sort(r+1,r+n+1,cmp);
	fr(i,1,n)
	{
		int A=getf(a[r[i]]),B=getf(b[r[i]]);
		if(w[A]||w[B])
		{
			if(A!=B)
			{
				w[A]+=w[B];
				f[B]=A;
			}
			w[A]--;
			ans+=v[r[i]];
		}
	}
	printf("%lld\n",ans);
	return 0;
}