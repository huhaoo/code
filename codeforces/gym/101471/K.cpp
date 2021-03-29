/***************************************************************
	File name: K.cpp
	Author: huhao
	Create time: Mon 26 Oct 2020 09:06:47 AM CST
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
const int N=1000010,M=20;
char s[M][N];
int a[M][N],_f[M][N];
int n,m,l;
int p[M];
int cmp(int x,int y)
{
	fd(i,n,std::max(1,n-(l-n))) if(a[x][i]!=a[y][i]) return a[x][i]<a[y][i];
	return 0;
}
int main()
{
	l=read(); m=read();
	fr(i,1,m)
	{
		scanf("%s",s[i]+1); int F=0; n=strlen(s[i]+1);
		fr(j,2,n)
		{
			while(F&&s[i][j]!=s[i][F+1]) F=_f[i][F];
			if(s[i][j]==s[i][F+1]) F++;
			_f[i][j]=F;
		}
		int k=n;
		while(k){ a[i][k]=1; k=_f[i][k]; }
	}
	fr(i,1,m) p[i]=i;
	std::stable_sort(p+1,p+m+1,cmp);
	fr(i,1,m) printf("%s\n",s[p[i]]+1);
	return 0;
}
