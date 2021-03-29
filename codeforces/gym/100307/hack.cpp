/***************************************************************
	File name: hack.cpp
	Author: huhao
	Create time: Sun 01 Nov 2020 03:03:55 PM CST
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
#include<vector>
#define pii std::pair<int,int>
#include<map>
const int N=100010;
int n,a[N],s[N];
int t[N][31];
i64 ans;
std::vector<pii> q[N];
std::map<int,int> S;
int main()
{
	freopen("hack.in","r",stdin); freopen("hack.out","w",stdout);
	n=read();
	fr(i,1,n) s[i]=s[i-1]^(a[i]=read());
	fr(i,0,30) t[n+1][i]=n+1;
	fd(i,n,1) fr(j,0,30) if(!((a[i]>>j)&1)) t[i][j]=i; else t[i][j]=t[i+1][j];
//	fr(i,1,n) fr(j,0,30) printf("%d%c",t[i][j],j==end_j?'\n':' ');
	fr(i,1,n)
	{
		int u=i,x=a[i];
		while(u<=n)
		{
			int p=n+1;
			fr(i,0,30) if((x>>i)&1) p=std::min(p,t[u][i]);
			q[u-1].push_back(pii(x^s[i-1],-1)); q[p-1].push_back(pii(x^s[i-1],1));
//			printf("%d  %d %d   %d\n",i,u,p-1,x^s[i-1]);
			if(p<=n) x&=a[p];
			u=p;
		}
	}
//	fr(i,0,n) for(auto j:q[i]) printf("%d %d  %d\n",i,j.first,j.second);
	fr(i,0,n)
	{
		S[s[i]]++;
		for(auto j:q[i]) ans+=(i64)S[j.first]*j.second;
	}
	printf("%lld\n",ans);
	return 0;
}
