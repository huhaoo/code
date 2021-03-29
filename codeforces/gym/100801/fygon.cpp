/***************************************************************
	File name: fygon.cpp
	Author: huhao
	Create time: Thu 12 Nov 2020 11:08:54 AM CST
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
int Gets(char *s){ *s=getchar(); if(*s=='\n'||*s==EOF){ int r=(*s=='\n'); *s=0; return r; } return Gets(s+1); }
const int N=256;
int n;
char s[N][N];
int l[N],p[N];
int v[N];
i64 f[N];
int dfs(int u)
{
	int ans=0;
	if(s[u][p[u]*4]=='l') ans=1;
	else for(int &i=(v[s[u][p[u]*4+4]]=0);i<v[s[u][p[u]*4+15]];i++) ans+=dfs(u+1);
	fr(i,u+1,n)
		if(p[u]>p[i]) break;
		else if(p[u]==p[i]) return ans+dfs(i);
	return ans;
}
int main()
{
	freopen("fygon.in","r",stdin); freopen("fygon.out","w",stdout);
	while(Gets(s[++n])) l[n]=strlen(s[n]);
	while(!l[n]) n--;
	fr(i,1,n) while(s[i][p[i]*4]==' ') p[i]++;
	fr(i,0,9) v[i+48]=i;
	fr(i,0,6){ v['n']=i; f[i]=dfs(1); }
	static i64 a[N],b[N];
	putchar('(');
	fr(i,0,6)
	{
		i64 v=f[i];
		fr(j,0,6) b[j]=0;
		if(i==1||i==5) v*=-6;
		if(i==2||i==4) v*=15;
		if(i==3) v*=-20;
		b[0]=v;
		fr(j,0,6) if(i!=j) fd(k,5,0){ b[k+1]+=b[k]; b[k]*=-j; }
		fr(j,0,6) a[j]+=b[j];
	}
	fr(i,0,6)
	{
		printf("(%lld)",a[i]);
		fr(j,1,i) printf("*n");
		if(i!=6) putchar('+');
	}
	printf(")*1/720\n");
	return 0;
}
