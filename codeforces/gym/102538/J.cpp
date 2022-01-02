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
int c[N];
int n,m;
std::vector<int> e[N];
int f;
void dfs(int u)
{
	for(auto v:e[u])
		if(!c[v]){ c[v]=3-c[u]; dfs(v); }
		else if(c[u]==c[v]) f=0;
}
int main()
{
	fr(T,1,read())
	{
		n=read(); m=read();
		fr(i,1,n){ c[i]=0; e[i].clear(); }
		fr(i,1,m)
		{
			int u=read(),v=read(); e[u].push_back(v); e[v].push_back(u);
		}
		int ans=m-n;
		fr(i,1,n) if(!c[i]){ c[i]=f=1; dfs(i); ans+=f; }
		int Ans=1;
		fr(i,1,ans) Ans=Ans*5ll%998244353;
		printf("%d\n",Ans);
	}
	return 0;
}