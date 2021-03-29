/***************************************************************
	File name: dictionary.cpp
	Author: huhao
	Create time: Sat 31 Oct 2020 05:01:28 PM CST
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
#define pii std::pair<int,int>
#define piii std::pair<int,pii>
#define F first
#define S second
const int N=60,M=N*N*N,inf=1<<20;
int n;
char s[N][N]; int l[N];
pii c[N][N]; int vis[N];
int ans=1; int t[N];
int m,u[M],v[M]; piii w[M];
int r[N][N],q;
int solve(int n,int m,int *u,int *v,piii *w)
{
	static int e[N],p[N],P[N],vis[N]; int _n=0,_m=0; int ans=0;
	fr(i,1,n) e[i]=p[i]=P[i]=0;
	fr(i,1,m) if(!e[u[i]]||w[i].F<w[e[u[i]]].F) e[u[i]]=i;
	fr(i,1,n) if(e[i]) ans+=w[e[i]].F;
	int flag=0;
	fr(i,1,n) if(e[i]&&!p[i])
	{
		int u=i;
		memset(vis,0,sizeof(vis));
		do{ vis[u]=1; u=v[e[u]]; }while(!vis[u]);
		p[i]=++_n;
		if(u==i){ flag=1; P[i]=1; do{ p[u=v[e[u]]]=_n; P[u]=1; }while(u!=i); }
	}
	else if(!e[i]) p[i]=++_n;
	if(!flag) return ans;
	fr(i,1,m) if(p[u[i]]!=p[v[i]]){ _m++; u[_m+m+1]=p[u[i]]; v[_m+m+1]=p[v[i]]; w[_m+m+1]=w[i]; w[_m+m+1].F-=w[e[u[i]]].F; }
	return ans+solve(_n,_m,u+m+1,v+m+1,w+m+1);
}
int main()
{
	freopen("dictionary.in","r",stdin); freopen("dictionary.out","w",stdout);
	n=read();
	fr(i,1,n)
	{
		scanf("%s",s[i]+1); l[i]=strlen(s[i]+1);
	}
	fr(i,1,n) c[i][n+1]=pii(l[i],0);
	fr(i,1,n+1) c[n+1][i]=pii(inf,0);
	fr(i,1,n) fr(j,1,n) if(i!=j)
	{
		c[j][i]=pii(l[j],0);
		fr(k,0,l[i]-1)
		{
			int p=0;
			while(k+p+1<=l[i]&&p+1<=l[j]&&s[i][k+p+1]==s[j][p+1]) p++;
			c[j][i]=std::min(c[j][i],pii(l[j]-p,k));
		}
	}
	else c[i][j]=pii(inf,0);
	fr(i,1,n+1) fr(j,1,n+1) if(c[i][j].F!=inf){ m++; u[m]=i; v[m]=j; w[m]={c[i][j].F,{i,j}}; }
	int Ans=solve(n+1,m,u,v,w);
	fr(x,1,n)
	{
		fr(y,1,n+1) if(c[x][y].F!=inf)
		{
			memset(u,0,sizeof(u)); memset(v,0,sizeof(v)); memset(w,0,sizeof(w));
			c[x][y].F++; m=0;
			fr(i,1,n+1) fr(j,1,n+1) if(c[i][j].F!=inf){ m++; u[m]=i; v[m]=j; w[m]={c[i][j].F,{i,j}}; }
			if(solve(n+1,m,u,v,w)==Ans+1)
			{
				c[x][y].F--;
				fr(i,1,n+1) if(i!=y) c[x][i].F=inf;
				t[x]=y;
			}
			else c[x][y].F=inf;
		}
	}
	printf("%d\n%d\n",Ans+1,0);
	fflush(stdout);
	vis[n+1]=1; r[n+1][0]=q=1;
	fr(T,1,n)
	{
		int u=0;
		fr(i,1,n) if(!vis[i]&&vis[t[i]]){ u=i; break; }
		assert(u); vis[u]=1;
		pii C=c[u][t[u]]; C.F=l[u]-C.F;
		int k=C.F?r[t[u]][C.F+C.S]:r[t[u]][0];
		fr(i,0,C.F) r[u][i]=r[t[u]][i+C.S];
		fr(i,C.F+1,l[u])
		{
			printf("%d %c\n",k,s[u][i]);
			r[u][i]=k=++q;
		}
	}
	return 0;
}
