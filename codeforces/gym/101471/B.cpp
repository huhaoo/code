/***************************************************************
	File name: B.cpp
	Author: huhao
	Create time: Tue 10 Nov 2020 11:35:37 AM CST
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
const int N=100;
int a[4],b;
int n,op[N][N],l[N],vis,c[N],x[N],y[N];
char getc(){ char c=getchar(); while((c<'A'||c>'U')&&c!='-'&&c!='*') c=getchar(); return c; }
inline bool at(int u,int v){ return (u>>v)&1; }
int dfs(int u,int v,int lst=-1)
{
	if(!v) return dfs(u+1,4);
	if(u==3)
	{
		a[3]=2097151^b^a[0]^a[1]^a[2];
//		static int cnt=0;
		fr(i,0,3) if((a[i]&x[i])||((~a[i])&y[i])) return 0;
		fr(i,1,n) fr(j,1,l[i])
			if(op[i][j]=='-'?(a[(i-1+j)&3]&op[i][0])==0:(a[(i-1+j)&3]&op[i][0]&(op[i][j]=='*'?2097151:1<<(op[i][j]-'A')))!=0) ;
			else return 0;
		return 1;
	}
	fr(i,lst+1,20) if(!at(vis,i))
	{
		a[u]^=1<<i; vis^=1<<i; int p=dfs(u,v-1,i);
		a[u]^=1<<i; vis^=1<<i; if(p) return 1;
	}
	return 0;
}
int main()
{
	n=read();
	fr(i,1,5) a[0]|=1<<(getc()-'A');
	vis=a[0];
	fr(i,1,n)
	{
		fr(j,1,3) op[i][0]|=1<<(getc()-'A');
		do op[i][++l[i]]=getc(); while(op[i][l[i]]=='-'&&l[i]!=3);
	}
	fr(i,1,n) fr(j,1,l[i])
		if(op[i][j]=='-') x[(i+j-1)&3]|=op[i][0];
		else if(op[i][j]>='A'&&op[i][j]<='U') y[(i+j-1)&3]|=1<<(op[i][j]-'A');
	fr(i,0,5) if(!at(vis,i)) fr(j,6,11) if(!at(vis,j)) fr(k,12,20) if(!at(vis,k))
	{
		b=(1<<i)|(1<<j)|(1<<k); vis=a[0]|b;
		if(dfs(1,5)) c[i]=c[j]=c[k]=1;
		vis=a[0];
	}
	int flag=-1;
	fr(i,0,5) if(c[i])
	{
		if(flag==-1) flag=i;
		else flag=-2;
	}
	putchar(flag>=0?flag+'A':'?');
	flag=-1;
	fr(i,6,11) if(c[i])
	{
		if(flag==-1) flag=i;
		else flag=-2;
	}
	putchar(flag>=0?flag+'A':'?');
	flag=-1;
	fr(i,12,20) if(c[i])
	{
		if(flag==-1) flag=i;
		else flag=-2;
	}
	putchar(flag>=0?flag+'A':'?'); putchar(10);
	return 0;
}
