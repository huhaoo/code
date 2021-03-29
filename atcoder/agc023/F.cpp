/***************************************************************
	File name: F.cpp
	Author: huhao
	Create time: Thu 16 Jan 2020 07:02:36 PM CST
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
#include<set>
#define i64 long long
const int N=200010;
int n,F[N],f[N];
i64 ans[N],a[N],b[N];
struct cmp{ int operator()(int x,int y){ return b[x]*a[y]==b[y]*a[x]?x<y:b[x]*a[y]<b[y]*a[x]; } };
std::set<int,cmp> s;
int getf(int u){ return u==f[u]?u:f[u]=getf(f[u]); }
int main()
{
	n=read();
	fr(i,2,n) F[i]=read();
	fr(i,1,n) f[i]=i;
	fr(i,1,n)
		if(read()) b[i]++;
		else a[i]++;
	fr(i,2,n) s.insert(i);
	while(!s.empty())
	{
		int u=*s.begin(),_f=getf(F[u]);
//		printf("%d %d\n",u,_f);
		f[u]=_f; s.erase(u); if(_f!=1) s.erase(_f);
		ans[_f]+=ans[u]+b[_f]*a[u]; a[_f]+=a[u]; b[_f]+=b[u]; if(_f!=1) s.insert(_f);
	}
	printf("%lld\n",ans[1]);
	return 0;
}
