/***************************************************************
	File name: 3195.cpp
	Author: huhao
	Create time: Fri 19 Jun 2020 08:57:12 AM CST
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
const int N=50010;
i64 n,v,s[N],f[N],a[N],b[N],q[N],l,r;
i64 at(i64 a,i64 b,i64 p){ return a*p+b; }
int main()
{
	n=read(); v=read()+1;
	fr(i,1,n) s[i]=s[i-1]+read()+1;
	b[0]=v*v; a[0]=-2*v;
	fr(i,1,n)
	{
		while(l!=r&&a[q[l]]*s[i]+b[q[l]]>a[q[l+1]]*s[i]+b[q[l+1]]) l++;
		f[i]=a[q[l]]*s[i]+b[q[l]]+s[i]*s[i];
		a[i]=-2*(s[i]+v); b[i]=f[i]+(s[i]+v)*(s[i]+v);
		while(r!=l)
		{
			double p=(double)(b[q[r]]-b[q[r-1]])/(a[q[r-1]]-a[q[r]]);
			if(a[q[r]]*p+b[q[r]]>a[i]*p+b[i]) r--;
			else break;
		}
		q[++r]=i;
	}
	printf("%lld\n",f[n]);
	return 0;
}
