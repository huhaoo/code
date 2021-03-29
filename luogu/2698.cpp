/**************************************************************
	File name: 2698.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/23/2018, 2:05:59 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
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
#define N 100010
int n,m,x[N],y[N],r[N],ans=(1<<29);
#undef N
#include<set>
multiset<int>s;
int main()
{
	n=read();m=read();
	fr(i,1,n)x[i]=read(),y[i]=read(),r[i]=i;
	sort(r+1,r+n+1,[&](int a,int b)->int{return x[a]<x[b];});
	s.insert(y[r[0]]);
	int j=1;s.insert(y[r[j]]);
	fr(i,1,n)
	{
		s.erase(s.find(y[r[i-1]]));
		while(*s.rbegin()-*s.begin()<m&&j<=n)
			s.insert(y[r[++j]]);
		if(j>n)break;
		ans=min(ans,x[r[j]]-x[r[i]]);
	}
	printf("%d\n",ans==(1<<29)?-1:ans);
	return 0;
}