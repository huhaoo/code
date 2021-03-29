/***************************************************************
	File name: H.cpp
	Author: huhao
	Create time: Tue 17 Nov 2020 03:54:33 PM CST
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
const int N=30,M=10010;
#define Real long double
const Real eps=1e-6;
int n,m;
Real p1,p2,p3,p4;
char s[M][N]; int vis[M][N];
Real f[M][N][N];
Real a[N][N],b[N][N];
void dfs(int u,int v)
{
	if(!(u>0&&u<=m&&v>0&&v<=n)) return ;
	if(vis[u][v]||s[u][v]=='X'||s[u][v]=='T') return ;
//	assert(u>0&&u<=m&&v>0&&v<=n);
	vis[u][v]=1; //printf("%d %d\n",u,v);
	dfs(u+1,v); dfs(u-1,v); dfs(u,v+1); dfs(u,v-1);
}
void gauss()
{
	fr(i,1,n)
	{
		int p=i;
		fr(j,i+1,n) if(fabs(a[p][i])<fabs(a[j][i])) p=j;
		fr(j,0,n){ std::swap(a[i][j],a[p][j]); std::swap(b[i][j],b[p][j]); }
		Real t=a[i][i];
		fr(j,1,n) a[i][j]/=t;
		fr(j,0,n) b[i][j]/=t;
		fr(j,i+1,n)
		{
			t=a[j][i];
			fr(k,1,n) a[j][k]-=a[i][k]*t;
			fr(k,0,n) b[j][k]-=b[i][k]*t;
		}
	}
	fd(i,n,1)
	{
		fr(j,1,i-1)
		{
			Real t=a[j][i];
			fr(k,1,n) a[j][k]-=a[i][k]*t;
			fr(k,0,n) b[j][k]-=b[i][k]*t;
		}
	}
}
int main()
{
	n=read(); m=read(); p1=read()*0.01; p2=read()*0.01; p3=read()*0.01; p4=read()*0.01;
	/*
	 2
	4o3
	 1
	 */
	fr(i,0,m+1) fr(j,0,n+1) s[i][j]='X';
	fr(i,1,m){ scanf("%s",s[i]+1); s[i][0]=s[i][n+1]='X'; }
	fr(i,1,m) dfs(1,i);
//	fr(i,1,m) fr(j,1,n) printf("%d%c",vis[i][j],j==n?'\n':' ');
/*	fr(i,1,n) if(s[1][i]=='.')
	{
		Real a=1-p1;
		if(s[1][i+1]!='.') a-=p3;
		if(s[1][i-1]!='.') a-=p4;
		f[1][i][0]=1./a;
	}*/
	int c=0;
	fr(i,1,n) c+=s[1][i]=='.';
	fr(t,1,m)
	{
		memset(a,0,sizeof(a)); memset(b,0,sizeof(b));
		if(t==1) fr(i,1,n) if(s[1][i]=='.') b[i][0]=1.;
		fr(i,1,n)
			if(!vis[t][i]) a[i][i]=1;
			else
			{
				a[i][i]=1;
				if(!vis[t+1][i]){ if(s[t+1][i]!='T') a[i][i]-=p2; }
				else if(s[t+1][i]=='.') b[i][i]+=p1;
				if(!vis[t-1][i]){ if(s[t-1][i]!='T') a[i][i]-=p1; }
				else if(s[t-1][i]=='.')
				{
					b[i][0]+=f[t-1][i][0]*p2; //printf("- %d %d\n",t,i);
					fr(j,1,n) a[i][j]-=f[t-1][i][j]*p2;
				}
				if(!vis[t][i+1]){ if(s[t][i+1]!='T') a[i][i]-=p4; }
				else if(s[t][i+1]=='.') a[i][i+1]-=p3;
				if(!vis[t][i-1]){ if(s[t][i-1]!='T') a[i][i]-=p3; }
				else if(s[t][i-1]=='.') a[i][i-1]-=p4;
			}
		gauss();
/*		if(t==1)
		{
		fr(i,1,n) if(s[t][i]=='T') a[i][i]=1;
		putchar(10);
		fr(i,1,n)
		{
			fr(j,1,n) printf("%.5Lf ",a[i][j]);
			fr(j,0,n) printf(" %.5Lf",b[i][j]);; putchar(10);
		}
		}*/
/*		putchar(10);
		fr(i,1,n)
		{
			fr(j,1,n) printf("%.5lf ",a[i][j]);
			printf(" %.5lf\n",b[i][0]);
		}*/
		fr(i,1,n) fr(j,0,n) f[t][i][j]=b[i][j];
	}
//	printf("   %.5lf %.5lf %.5lf %.5lf\n",p1,p2,p3,p4);
	fd(t,m-1,1) fr(i,1,n) fr(j,1,n) f[t][i][0]+=f[t+1][j][0]*f[t][i][j];
//	fr(i,1,m) fr(j,1,n) printf("%.5Lf%c",f[i][j][0],j==n?'\n':' ');
	fr(i,1,m) fr(j,1,n) if(s[i][j]=='T')
	{
		Real _ans=0;
		if(s[i+1][j]=='.') _ans+=f[i+1][j][0]*p1;
		if(s[i-1][j]=='.') _ans+=f[i-1][j][0]*p2;
		if(s[i][j+1]=='.') _ans+=f[i][j+1][0]*p3;
		if(s[i][j-1]=='.') _ans+=f[i][j-1][0]*p4;
		printf("%.10lf\n",double(_ans/c));
	}
	return 0;
}
