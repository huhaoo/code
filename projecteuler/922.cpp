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
const int mod=1000000007;
std::map<std::array<int,3>, int> f;
int dfs(int n, int m, int s, int t)
{
	if(t<-(m-2)*n) t=-(m-2)*n-1;
	if(t>(m-2)*n) t=(m-2)*n+1;
	if(n==0) return t>0||(t==0&&s);
	if(f.count({n,s,t})) return f[{n,s,t}];
	int ans=0;
	fr(i,1,m) fr(j,1,m-i) fr(k,1,m-i-j)
	{
		ans+=dfs(n-1,m,s^(i-1),t+j-k);
		if(ans>=mod) ans-=mod;
	}
	// printf("%d %d %d %d  %d\n",n,m,s,t,ans);
	return f[{n,s,t}]=ans;
}
int main()
{
	printf("%d\n",dfs(8,64,0,0));
	return 0;
}