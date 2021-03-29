/***************************************************************
	File name: fragmentation.cpp
	Author: huhao
	Create time: Thu 03 Dec 2020 11:44:31 AM CST
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
const int N=100010;
int n,a[N];
int p[N],q[N];
int m,b[N],c[N],C[N];
int r[N];
int vis[N];
std::vector<int> t[N];
int f[N],g[N];
int pf[N],pg[N];
int P[N];
int main()
{
	freopen("fragmentation.in","r",stdin); freopen("fragmentation.out","w",stdout);
	n=read();
	fr(i,1,n) a[i]=b[i]=read();
	std::sort(b+1,b+n+1);
	fr(i,1,n) if(a[i]!=a[i-1]) q[a[i]]++;
	fd(i,n,1) r[b[i]]=b[i-1];
	fr(i,1,n) p[b[i]]=b[i+1];
	fr(i,1,n)
		if(a[i]==a[i-1]) c[m]++;
		else{ m++; c[m]=1; b[m]=a[i]; }
	n=m;
	fr(i,1,n) a[i]=b[i];
	std::sort(b+1,b+n+1); m=std::unique(b+1,b+n+1)-b-1;
	fr(i,1,n) a[i]=std::lower_bound(b+1,b+m+1,a[i])-b;
//	fr(i,1,n) printf("%d %d\n",a[i],c[i]);
	fr(i,1,n) t[a[i]].push_back(i);
	fr(i,1,n) f[i]=-N;
	a[n+1]=0;
	fr(i,1,m)
	{
		pii mx=pii(g[i-1],-1),Mx=pii(-N,-1);
		for(auto j:t[i-1])
			if(mx<pii(f[j],j)){ Mx=mx; mx=pii(f[j],j); }
			else Mx=std::max(Mx,pii(f[j],j));
		g[i]=mx.first; pg[i]=mx.second; if(pg[i]==-1) pg[i]=pg[i-1];
		for(auto j:t[i]) if(a[j+1]==i+1)
		{
			if(mx.second+1==j&&t[i].size()>1)
			{
				f[j]=Mx.first+1; pf[j]=Mx.second;
				if(pf[j]==-1) pf[j]=pg[i-1];
			}
			else
			{
				f[j]=mx.first+1; pf[j]=mx.second;
				if(pf[j]==-1) pf[j]=pg[i-1];
			}
//			printf("%d %d %d\n",j,f[j],pf[j]);
		}
	}
	pii mx=pii(0,0);
	fr(i,1,n) mx=std::max(mx,pii(f[i],i));
	int u=mx.second;
	while(u>0){ P[u]=1; u=pf[u]; }
	m=0;
	fr(i,1,n) if(P[i-1]) C[m]+=c[i]; else C[++m]=c[i];
	printf("%d\n",m);
	fr(i,1,m) printf("%d%c",C[i],i==m?'\n':' ');
	return 0;
}
