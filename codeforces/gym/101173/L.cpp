/***************************************************************
	File name: L.cpp
	Author: huhao
	Create time: Mon 12 Oct 2020 09:03:10 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
const int N=10010;
int n,s[N],vis[N];
int id[N],c;
int U[N],V[N],M;
int u[N],v[N],m;
int cnt;
int p[N];
void print(int x)
{
	if(x<0) putchar('!');
	printf("x%d",std::abs(x));
}
void Print(int x)
{
	if(x<0) putchar('!');
	printf("x%d",id[std::abs(x)]);
}
void Dfs(int x)
{
	if(x==c+1)
	{
		fr(i,1,m) if((u[i]<0?!p[-u[i]]:p[u[i]])>(v[i]<0?!p[-v[i]]:p[v[i]])) return ;
		fr(i,0,2)
		{
			int flag=1;
			fr(j,1,c) if(p[j]!=((s[id[j]]>>i)&1)) flag=0;
			if(flag){ cnt&=15^(1<<i); return ; }
		}
		cnt&=7;
		return ;
	}
	p[x]=0; Dfs(x+1); p[x]=1; Dfs(x+1);
}
void dfs(int x,int y)
{
	if(x==c+1)
	{
		cnt=15; Dfs(1);
		if(cnt==8)
		{
			printf("%d\n",M+m);
			fr(i,1,M){ print(U[i]); printf(" -> "); print(V[i]); putchar(10); }
			fr(i,1,m){ Print(u[i]); printf(" -> "); Print(v[i]); putchar(10); }
			exit(0);
		}
		return ;
	}
	if(y==c+1){ dfs(x+1,x+2); return ; }
	fr(i,0,15)
	{
		if(i&1){ m++; u[m]=x; v[m]=y; }
		if(i&2){ m++; u[m]=-x; v[m]=y; }
		if(i&4){ m++; u[m]=x; v[m]=-y; }
		if(i&8){ m++; u[m]=-x; v[m]=-y; }
		dfs(x,y+1);
		if(i&1) m--;
		if(i&2) m--;
		if(i&4) m--;
		if(i&8) m--;
	}
}
int main()
{
	n=read();
	fr(j,0,2) fr(i,1,n) s[i]|=read()<<j;
	fr(i,1,n)
	{
		if(s[i]==0){ M++; U[M]=i; V[M]=-i; }
		else if(s[i]==7){ M++; U[M]=-i; V[M]=i; }
		else if(vis[s[i]])
		{
			int j=vis[s[i]];
			M++; U[M]=i; V[M]=j;
			M++; U[M]=-i; V[M]=-j;
		}
		else if(vis[s[i]^7])
		{
			int j=vis[s[i]^7];
			M++; U[M]=i; V[M]=-j;
			M++; U[M]=-i; V[M]=j;
		}
		else
		{
			id[++c]=i; vis[s[i]]=i;
		}
	}
	if(c>0) dfs(1,2);
	printf("-1\n");
	return 0;
}
