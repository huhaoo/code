/***************************************************************
	File name: dividing.cpp
	Author: huhao
	Create time: Tue 24 Nov 2020 09:04:47 AM CST
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
const int N=1<<22|10;
int id[N],Id[N],m;
int f[N];
std::vector<std::vector<int> > ans[N];
int main()
{
	freopen("dividing.in","r",stdin); freopen("dividing.out","w",stdout);
	fr(i,1,1<<22) f[i]=N;
	fr(i,1,1<<22) if(__builtin_popcount(i)<=4)
	{
		m++; id[i]=m; Id[m]=i;
		int l=0;
		while((1<<l)<=i) l++;
		f[i]=l-2;
		fr(j,0,l-1) if((i>>j)&1) f[i]++;
		int n=i;
		while(n>1)
		{
			if(n&1) ans[i].push_back({n,n-1,1});
			n/=2; ans[i].push_back({n+n,n,n});
		}
	}
	fr(i,1,1<<22) if(__builtin_popcount(i)==4)
	{
		fr(j,1,m-1) if(Id[j]*Id[j]<=i)
		{
			int u=Id[j];
			if(i%u==0&&f[u]+f[i/u]<f[i])
			{
				int v=i/Id[j]; f[i]=f[u]+f[v];
				ans[i].clear();
				for(auto w:ans[v]) ans[i].push_back({w[0]*u,w[1]*u,w[2]*u});
				for(auto w:ans[u]) ans[i].push_back(w);
			}
		}
		else break;
		int l=0;
		while((1<<l)<=i) l++;
		if(((i>>(l-2))&1)!=0) continue;
		int _i=i-(1<<(l-2));
		fr(j,2,m-1) if(Id[j]*Id[j]<=_i)
		{
			int u=Id[j];
			if(_i%u==0&&f[u]+f[_i/u]+1<f[i])
			{
				int v=_i/Id[j];
				int s=0,T=u;
				for(auto w:ans[u]) if(w[1]==w[2]) s++;
				for(auto w:ans[v]) if(w[1]==w[2]) s++;
				if(s<l-2) continue;
				ans[i].clear(); int n=i; f[i]=f[u]+f[v]+1;
				for(auto w:ans[v])
				{
					if(w[1]==w[2])
					{
						n/=2;
						ans[i].push_back({n+n,n,n});
					}
					else{ ans[i].push_back({n,n-w[2]*T,w[2]*T}); n-=w[2]*T; }
				}
				ans[i].push_back({n,ans[u][0][0],n-ans[u][0][0]});
				for(auto w:ans[u]) ans[i].push_back(w);
			}
		}
		else break;

	}
	fr(T,1,read())
	{
		int n=(1<<read())+(1<<read())+(1<<read())+(1<<read());
		printf("%d\n",ans[n].size());
		for(auto i:ans[n]) printf("%d %d %d\n",i[0],i[1],i[2]);
	}
	return 0;
}
