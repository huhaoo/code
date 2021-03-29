/****************************************************************
*	Author: huhao
*	Email: 826538400@qq.com
*	Create time: 2019-10-26 20:09:23
****************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
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
#include<vector>
const int N=1000010;
vector<int> s[N];
int n,w[N],f[N],ans[N],Ans,id[N],p[N];
int main()
{
	n=read();
	f[0]=-1;
	fr(i,1,n-1)
	{
		f[i]=read();
		s[f[i]].push_back(i);
	}
	fd(i,n-1,0)
	{
		w[i]++;
		if(f[i]>=0)
			w[f[i]]+=w[i];
	}
	int u=0;
	while(s[u].size())
	{
		int o=-1;
		for(auto v:s[u])
			if(o==-1||w[v]<w[o])
				o=v;
		for(auto v:s[u])
			if(v!=o)
			{
				f[v]=o;
				s[o].push_back(v);
				ans[++Ans]=v;
			}
		u=o;
	}
	fd(i,n-1,0)
	{
		p[i]=u;
		id[u]=i;
		u=f[u];
	}
	fr(i,0,n-1)
		printf("%d%c",p[i],i==n-1?'\n':' ');
	if(p[1]==0)
		return 1;
	printf("%d\n",Ans);
	fr(i,1,Ans)
		printf("%d%c",ans[i],i==end_i?'\n':' ');
	return 0;
}