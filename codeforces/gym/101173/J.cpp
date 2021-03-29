/***************************************************************
	File name: J.cpp
	Author: huhao
	Create time: Thu 24 Dec 2020 08:49:24 PM CST
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
#define i64 long long
#define pii std::pair<int,int>
#include<set>
#include<map>
#include<vector>
std::set<pii> s;
std::map<pii,std::vector<int> > c;
std::map<pii,int> w[4];
int n,m,a[300010];
i64 ans;
i64 solve(std::vector<int> a,i64 w[4])
{
	i64 ans=1ll<<60; std::vector<int> b,c; int n=a.size();
	fr(i,0,n-1) (!a[i]?b:c).push_back(i);
	int s1=0,s2=0,n1=b.size(),n2=c.size(),m1=n1,m2=n2;
	fr(i,0,n-1)
		if(!a[i]){ m1=std::min(m1,s1+(n2-s2)); s1++; }
		else{ m2=std::min(m2,s2+(n1-s1)); s2++; }
	fr(i,0,m1)
	{
		int j=std::min(std::min(n1,n2)-i,m2);
		ans=std::min(ans,w[0]*(n1-i-j)+w[1]*(n2-i-j)+w[2]*i+w[3]*j);
	}
/*	if(ans>10000)
	{
		printf("%lld %lld %lld %lld     %lld\n",w[0],w[1],w[2],w[3],ans);
		fr(i,0,n-1) printf("%d%c",a[i],i==end_i?'\n':' ');
	}*/
	return ans;
}
int main()
{
	read(); m=read();
	fr(i,1,m) a[i]=read();
	fr(i,2,m)
	{
		int u=a[i-1],v=a[i],op=0;
		if(u>v){ std::swap(u,v); op=1; }
		s.insert({u,v});
		c[{u,v}].push_back(op);
	}
	n=read();
	fr(i,1,n)
	{
		int u,v; char op; int w;
		scanf("%d %d %c %d",&u,&v,&op,&w);
		if(op=='O') op=0;
		else op=2;
		if(u>v){ std::swap(u,v); op|=1; }
		if(!::w[op].count({u,v})) ::w[op][{u,v}]=w;
		::w[op][{u,v}]=std::min(::w[op][{u,v}],w);
	}
	for(auto i:s)
	{
		i64 W[4];
		fr(j,0,3) if(w[j].count(i)) W[j]=w[j][i]; else W[j]=1ll<<45;
		W[0]=std::min(W[0],W[2]); W[1]=std::min(W[1],W[3]);
		W[2]=std::min(W[2],W[0]+W[1]); W[3]=std::min(W[3],W[0]+W[1]);
		ans+=solve(c[i],W);
	}
	printf("%lld\n",ans);
	return 0;
}
