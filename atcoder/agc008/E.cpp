/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Tue 26 Jan 2021 03:08:50 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
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
const int N=200010,mod=1000000007;
i64 power(i64 a,i64 b,i64 p=mod)
{
	i64 r=1;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
i64 inv(i64 a){ return power(a,mod-2); }
struct Choose
{
	i64 f[N],F[N];
	Choose(int n)
	{
		f[0]=1; fr(i,1,n) f[i]=f[i-1]*i%mod;
		F[n]=inv(f[n]); fd(i,n,1) F[i-1]=F[i]*i%mod;
	}
	i64 operator()(i64 a,i64 b){ return a>=b&&b>=0?f[a]*F[b]%mod*F[a-b]%mod:0; }
} C(N-10);
int n,a[N],vis[N];
std::vector<int> e[N];
i64 f[N],ans;
i64 A[N],B[N];
void bf(int n,int *a)
{
	static int p[N];
	fr(i,1,n) p[i]=i;
	do
	{
		int flag=1;
		fr(i,1,n) flag&=(p[i]==a[i]||p[p[i]]==a[i]);
		if(flag)
		{
			putchar(10);
			fr(i,1,n)// printf("%d%c",p[i],i==n?'\n':' ');
				printf("%d %d\n",i,p[i]);
		}
	}
	while(std::next_permutation(p+1,p+n+1));
}
int dfs(int u)
{
	if(e[u].size()>1){ printf("0\n"); exit(0); }
	if(e[u].empty()) return 1;
	return 1+dfs(e[u][0]);
}
int main()
{
//	freopen("in","r",stdin);
	n=read();
	fr(i,1,n) e[a[i]=read()].push_back(i);
//	fr(i,1,n) printf("%d %d\n",i,a[i]);
//	bf(n,a); return 0;
	fr(i,1,n) if(e[i].size()>2){ printf("0\n"); return 0; }
	ans=1;
	fr(i,1,n) if(!vis[i])
	{
		int u=i; static int s[N],t,v[N]; t=0; int flag;
		while(!vis[u]){ vis[u]=-1; u=a[u]; }
		if(vis[u]==1)
		{
			u=i; while(vis[u]==-1){ vis[u]=1; u=a[u]; }
			continue;
		}
		while(vis[u]==-1){ s[++t]=u; vis[u]=1; u=a[u]; }
		u=i; while(vis[u]==-1){ vis[u]=1; u=a[u]; }
//		printf("%d  ",t); fr(i,1,t) printf("%d%c",s[i],i==t?'\n':' ');; fflush(stdout);
		s[0]=s[t]; fr(i,1,t) e[s[i]].erase(e[s[i]].begin()+(e[s[i]][0]!=s[i-1]));
		fr(i,1,t) if(!e[s[i]].empty()) v[i]=dfs(e[s[i]][0]); else v[i]=0;
		flag=0;
		fr(i,1,t) if(v[i]) flag=1;
		if(!flag){ f[t]++; continue; }
		std::reverse(v+1,v+t+1); fr(i,1,t) v[i+t]=v[i];
		fr(i,1,t) if(v[i])
		{
			int p=2;
			fr(j,1,v[i]-1) if(v[i+j]){ p--; break; }
			fr(j,1,v[i]) if(v[i+j]){ p--; break; }
//			if(p==2&&t==v[i]) p=1;
			ans=ans*p%mod;
		}
	}
	A[0]=B[0]=1;
	fr(i,1,n) A[i]=A[i-1]*(i+i-1)%mod;
	fr(i,1,n) B[i]=B[i-1]*2%mod;
	fr(i,1,n) if(f[i])
	{
		i64 p=0,x=1;
		fr(j,0,f[i]>>1)
		{
			p=(p+C(f[i],j+j)*A[j]%mod*x%mod*(i>1&&(i&1)?B[f[i]-j-j]:1))%mod;
			x=x*i%mod;
		}
		ans=ans*p%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
