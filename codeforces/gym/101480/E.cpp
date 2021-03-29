/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Tue 10 Nov 2020 11:01:02 AM CST
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
#include<vector>
#define pii std::pair<int,int>
const int N=300010;
int n,m,d[N],x[N],y[N],X,Y,f[N],w[N];
std::vector<pii> e[N];
void add(int u){ Y++; if(u==0||u==2) Y--; if(u==2) X--; }
void del(int u){ Y--; if(u==0||u==2) Y++; if(u==2) X++; }
int getf(int u){ return u==f[u]?u:f[u]=getf(f[u]); }
int main()
{
	n=read(); m=read();
	fr(i,1,m){ int u=read(),v=read(),w=read(); e[w].push_back(pii(u,v)); }
	fr(i,1,n) add(0);
	fr(i,1,n){ f[i]=i; w[i]=1; }
	fd(i,300000,0)
	{
		for(auto j:e[i])
		{
			int u=j.first,v=j.second,du=d[u],dv=d[v];
			del(d[u]); del(d[v]); d[u]++; d[v]++; add(d[u]); add(d[v]); X++;
			u=getf(u); v=getf(v);
			if(du==2){ if(w[u]==0){ X--; Y--; } w[u]++; }
			if(du==1) w[u]--;
			if(dv==2){ if(w[v]==0){ X--; Y--; } w[v]++; }
			if(dv==1) w[v]--;
			if(u!=v){ f[v]=u; w[u]+=w[v]; }
			if(w[u]==0){ X++; Y++; }
		}
		x[i]=X; y[i]=Y;
	}
	fr(q,1,read()){ int u=read(); printf("%d %d\n",y[u],x[u]); }
	return 0;
}
