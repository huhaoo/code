/***************************************************************
	File name: equal.cpp
	Author: huhao
	Create time: Fri 30 Oct 2020 03:38:49 PM CST
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
const int N=1000010;
int n,c[N],p[N],m=1000000,t,flag;
int ans[N],Ans[N];
int a[N],b[N],x,y;
int main()
{
	freopen("equal.in","r",stdin); freopen("equal.out","w",stdout);
	n=read();
	fr(i,1,n) c[read()]++;
	fr(i,1,m) if(c[i])
	{
		fr(j,2,sqrt(i)) if(i%j==0) p[j]=p[i/j]=1;
		if(i!=1) p[1]=1;
	}
	fr(i,1,m) if(c[i])
	{
		a[++x]=c[i];
		if(p[i]) b[++y]=c[i];
	}
	std::sort(a+1,a+x+1); std::sort(b+1,b+y+1);
	fr(i,1,x) a[i]+=a[i-1];
	fr(i,1,y) b[i]+=b[i-1];
	fr(i,1,x) ans[a[i]]=i;
	fr(i,1,y) Ans[b[i]]=i;
	fr(i,1,n){ ans[i]=std::max(ans[i],ans[i-1]); Ans[i]=std::max(Ans[i],Ans[i-1]); }
	fr(i,0,n) printf("%d%c",x-std::max(ans[i]-1,Ans[i]),i==n?'\n':' ');
	return 0;
}
