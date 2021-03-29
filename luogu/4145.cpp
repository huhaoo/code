/***************************************************************
	File name: 4145.cpp
	Author: huhao
	Create time: Fri 31 May 2019 09:08:24 AM CST
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
const i64 N=200010;
i64 n,a[N],s[N],f[N],q,m;
int main()
{
	n=read();
	m=(i64)sqrt(n);
	fr(i,1,n)
	{
		a[i]=read();
		s[(i-1)/m+1]+=a[i];
		f[(i-1)/m+1]|=a[i]>1;
	}
	q=read();
	while(q--)
	{
		if(read()==0)
		{
			i64 l=read(),r=read(),_l,_r;
			if(l>r)
				swap(l,r);
			_l=(l-1)/m+1;
			_r=(r-1)/m+1;
			if(_l==_r)
			{
				fr(i,l,r)
					a[i]=(i64)(sqrt(a[i]));
			}
			else
			{
				fr(i,l,_l*m)
					a[i]=(i64)(sqrt(a[i]));
				fr(i,(_r-1)*m+1,r)
					a[i]=(i64)(sqrt(a[i]));
				fr(i,_l+1,_r-1)
					if(f[i])
					{
						fr(j,(i-1)*m+1,i*m)
							a[j]=(i64)(sqrt(a[j]));
					}
			}
			fr(i,_l,_r)
				if(f[i])
				{
					f[i]=0;
					s[i]=0;
					fr(j,(i-1)*m+1,i*m)
					{
						s[i]+=a[j];
						f[i]|=a[j]>1;
					}
				}
		}
		else
		{
			i64 l=read(),r=read(),_l,_r,ans=0;
			if(l>r)
				swap(l,r);
			_l=(l-1)/m+1;
			_r=(r-1)/m+1;
			if(_l==_r)
			{
				fr(i,l,r)
					ans+=a[i];
			}
			else
			{
				fr(i,_l+1,_r-1)
					ans+=s[i];
				fr(i,l,_l*m)
					ans+=a[i];
				fr(i,(_r-1)*m+1,r)
					ans+=a[i];
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
