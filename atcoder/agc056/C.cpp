#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9'){ t=c=='-'?-1:1; c=getchar(); }
	while(c>='0'&&c<='9'){ r=(r<<3)+(r<<1)+(c^48); c=getchar(); }
	return r*t;
}
const int N=1000010;
int n,m,d[N];
std::vector<int> e0[N],e1[N],D[N];
int main()
{
	n=read(); m=read();
	fr(i,1,n){ e1[i].push_back(i+1); e1[i+1].push_back(i); }
	fr(i,1,n+1) d[i]=n+1;
	fr(i,1,m){ int u=read(),v=read(); e0[u].push_back(v+1); e0[v+1].push_back(u); }
	d[1]=0; D[0].push_back(1);
	fr(i,0,n+1) while(!D[i].empty())
	{
		int u=D[i].back(); D[i].pop_back();
		for(auto v:e0[u]) if(d[v]>i){ d[v]=i; D[i].push_back(v); }
		for(auto v:e1[u]) if(d[v]>i+1){ d[v]=i+1; D[i+1].push_back(v); }
	}
//	fr(i,1,n+1) printf("%d%c",d[i],i==n+1?'\n':' ');
	fr(i,2,n+1) putchar(d[i]>d[i-1]?'0':'1');
	putchar(10);
	return 0;
}