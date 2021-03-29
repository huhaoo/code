/***************************************************************
	File name: integral.cpp
	Author: huhao
	Create time: Thu 19 Nov 2020 02:11:22 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
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
const int N=200010;
int n,x[N],y[N];
#define i64 long long
int calc(int i,int j,int k){ return ((x[i]^x[j])&(y[k]^y[j]))^((x[k]^x[j])&(y[i]^y[j])); }
i64 solve(int l,int r)
{
	if(l+1>=r) return 0;
	int m=(l+r)>>1,s;
//	printf("%d %d   %d\n",l,r,m);
	i64 ans=0;
	static int s1[8],s2[8];
	fr(i,0,7) s1[i]=s2[i]=0;
	s=0;
	fd(i,m-1,l)
	{
		s^=calc(m,i,i+1);
		s1[(x[i]^x[m])|(y[i]^y[m])<<1|s<<2]++;
		if(i!=m-1&&!s)
		{
//			printf("%d %d\n",i,m);
			ans++;
		}
	}
	s=0;
	fr(i,m+1,r)
	{
		s^=calc(m,i,i-1);
		s2[(x[i]^x[m])|(y[i]^y[m])<<1|s<<2]++;
		if(i!=m+1&&!s)
		{
//			printf("%d %d\n",i,m);
			ans++;
		}
	}
	fr(i,0,7) fr(j,0,7) if(!((i>>2)^(j>>2)^((i&1)&((j>>1)&1))^(((i>>1)&1)&(j&1))))
	{
//		printf("%d %d    %d %d\n",i,j,s1[i],s2[j]);
		ans+=(i64)s1[i]*s2[j];
	}
	ans+=solve(l,m-1)+solve(m+1,r);
	return ans;
}
int main()
{
	freopen("integral.in","r",stdin); freopen("integral.out","w",stdout);
	n=read();
	fr(i,1,n){ x[i]=read()&1; y[i]=read()&1; }
	int s=0;
	fr(i,3,n) s+=calc(1,i-1,i);
	if(s&1) printf("0\n");
	else printf("%lld\n",solve(1,n)-1);
	return 0;
}
