/***************************************************************
	File name: B.cpp
	Author: huhao
	Create time: Mon 23 Nov 2020 02:41:17 PM CST
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
#define pii std::pair<i64,i64>
#define F first
#define S second
#include<vector>
const int N=100010;
int n,ans[N]; pii p[N];
pii operator-(pii a,pii b){ return pii(a.F-b.F,a.S-b.S); }
i64 operator*(pii a,pii b){ return a.F*b.S-a.S*b.F; }
void solve(std::vector<int> a,int l,int r)
{
	if(r-l<=10)
	{
		for(;l<=r;l++) for(auto i:a) if((p[i]-p[i-1])*(p[l]-p[i-1])>0) ans[i]=std::min(ans[i],l);
		return ;
	}
	int m=(l+r)>>1;
	static int s[N],t; s[t=1]=l;
	fr(i,l+1,m)
	{
		while(t>1&&(p[s[t]]-p[s[t-1]])*(p[i]-p[s[t-1]])>=0) t--;
		s[++t]=i;
	}
	int j=t; std::vector<int> b,c;
	for(auto i:a)
	{
		while(j>1&&(p[s[j]]-p[s[j-1]])*(p[i]-p[i-1])>0) j--;
		((p[i]-p[i-1])*(p[s[j]]-p[i-1])>0?b:c).push_back(i);
	}
	solve(b,l,m); solve(c,m+1,r);
}
void solve(int l,int r)
{
	if(l==r) return ;
	int m=(l+r)>>1;
	std::vector<int> a;
	fr(i,l,m) a.push_back(i);
	std::sort(a.begin(),a.end(),[&](int u,int v){ return (p[u]-p[u-1])*(p[v]-p[v-1])>0; });
	solve(a,m+1,r); solve(l,m); solve(m+1,r);
}
int main()
{
	fr(T,1,read())
	{
		n=read();
		fr(i,1,n){ p[i].F=read(); p[i].S=read(); ans[i]=n+1; }
		solve(2,n);
		fr(i,2,n) printf("%d%c",ans[i]==n+1?0:ans[i]-1,i==n?'\n':' ');
	}
	return 0;
}
