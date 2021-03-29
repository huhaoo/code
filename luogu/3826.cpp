/***************************************************************
	File name: 3826.cpp
	Author: huhao
	Create time: Tue 28 May 2019 08:59:10 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define i64 long long
#define fr(i,a,b) for(i64 i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(i64 i=(a),end_##i=(b);i>=end_##i;i--)
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
const i64 N=2000010;
i64 f[N],p[N],n,m,k=100000,_n;
long long ans[N];
struct veg
{
	i64 v,s,x;
	veg(i64 _v=0,i64 _s=0,i64 _x=0)
	{
		v=_v;
		s=_s;
		x=_x;
	}
}a[N];
i64 cmp(veg a,veg b)
{
	return a.v>b.v;
}
i64 t,_t,_m;
i64 find(i64 x)
{
	return p[x]?f[x]=find(f[x]):x;
}
int main()
{
	n=read();
	m=read();
	i64 q=read();
	fr(i,1,m*k)
		f[i]=i-1;
	fr(i,1,n)
	{
		i64 b=read(),c=read(),d=read(),e=read();	
		if(e==0)
		{
			a[++_n]=veg(b+c,1,-k);
			if(d!=1)
				a[++_n]=veg(b,d-1,0);
		}
		else
		{
			a[++_n]=veg(b+c,1,-((d-1)/e+1));
			if(d!=1)
				a[++_n]=veg(b,d-1,e);
		}
	}
	sort(a+1,a+_n+1,cmp);
	t=1;
	_t=1;
	_m=1;
	fr(i,1,k)
	{
		ans[i]=ans[i-1];
		for(i64 j=1;j<=m;)
			if(t<=_n)
			{
				if(a[t].x<0)
				{
					i64 x=find(min(k,-a[t].x)*m);
					if(x)
					{
						p[x]=1;
						j++;
						ans[i]+=a[t].v;
					}
					t++;
					_t=1;
				}
				else if(a[t].x==0)
				{
					i64 x=find(k*m);
					p[x]=1;
					j++;
					ans[i]+=a[t].v;
					_t++;
				}
				else
				{
					i64 x=min((_t-1)/a[t].x+1,k);
					if((x=find(x*m)))
					{
						p[x]=1;
						j++;
						ans[i]+=a[t].v;
						_t++;
					}
					else
					{
						while(!(x=find(_m*m)))
							_m++;
						if((_m-1)*a[t].x+1<=a[t].s)
						{
							_t=(_m-1)*a[t].x+2;
							p[x]=1;
							j++;
							ans[i]+=a[t].v;
						}
						else
						{
							_t=1;
							t++;
						}
					}
				}
				if(_t>a[t].s)
				{
					_t=1;
					t++;
				}
			}
			else
				break;
	}
	while(q--)
		printf("%lld\n",ans[read()]);
	return 0;
}
