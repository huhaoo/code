/***************************************************************
	File name: D.cpp
	Author: huhao
	Create time: Fri 17 Jan 2020 04:56:43 PM CST
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
#include<assert.h>
const int N=100010;
const i64 inf=1ll<<60;
i64 n,s,x[N],p[N],s1[N],t1,s2[N],t2,ans,a[N],t,a1[N],a2[N];
int main()
{
	n=read(); s=read();
	fr(i,1,n){ x[i]=read(); p[i]=read(); }
	s1[++t1]=s2[++t2]=inf; a1[t1]=a2[t2]=s;
	fd(i,n,1) if(x[i]<s){ s1[++t1]=p[i]; a1[t1]=x[i]; }
	fr(i,1,n) if(x[i]>s){ s2[++t2]=p[i]; a2[t2]=x[i]; }
	fr(i,1,n)
		if(s1[t1]>=s2[t2])
		{
//			printf("1\n");
			a[++t]=a2[t2]; s1[t1]=std::min(s1[t1]+s2[t2],inf); t2--;
		}
		else
		{
//			printf("2\n");
			a[++t]=a1[t1]; s2[t2]=std::min(s1[t1]+s2[t2],inf); t1--;
		}
	a[++t]=s;
//	fr(i,1,n+1) printf("%lld%c",a[i],i==n+1?'\n':' ');
	fr(i,2,n+1) ans+=std::abs(a[i]-a[i-1]);
	printf("%lld\n",ans);
	return 0;
}
