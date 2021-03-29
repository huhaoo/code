/****************************************************************
*	Author: huhao
*	Email: 826538400@qq.com
*	Create time: 2019-09-23 22:18:57
****************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
using namespace std;
#define int long long
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
const int N=100010,mod=1000000007;
int n,a[N],s[N][50],t,S[N],T,ans,d[N],f[N];
vector<int>e[N];
int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}
void dfs(int u,int t)
{
	t++;
	s[u][t]=u;
//	fr(i,1,t)	
//		printf("%I64d%c",s[i],i==t?'\n':' ');
	fr(i,1,t)
		S[i]=s[u][i];
	T=t;
	t=0;
	int pg=0;
	fd(i,T,1)
	{
		if(i==T||gcd(pg,a[S[i]])!=pg)
		{
			t++;
			s[u][t]=S[i];
			pg=gcd(pg,a[S[i]]);
		}
	}
	fr(i,1,t/2)
		swap(s[u][i],s[u][t-i+1]);
//	printf("%I64d\n",u);
	pg=0;
	fd(i,t,1)
	{
		pg=gcd(pg,a[s[u][i]]);
//		printf("%I64d %I64d %I64d\n",pg,d[s[i]],s[i]);
		ans=(ans+pg*(d[s[u][i]]-d[s[u][i-1]]))%mod;
	}
	for(auto i:e[u])
		if(!d[i])
		{
			d[i]=d[u]+1;
			f[i]=u;
			fr(j,1,t)
				s[i][j]=s[u][j];
			dfs(i,t);
		}
}
signed main()
{
	n=read();
	fr(i,1,n)
		a[i]=read();
	fr(i,1,n-1)
	{
		int u=read(),v=read();
		e[u].push_back(v);
		e[v].push_back(u);
	}
	d[1]=1;
	dfs(1,0);
	printf("%I64d\n",ans);
	return 0;
}