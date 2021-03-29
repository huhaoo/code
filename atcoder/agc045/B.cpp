/***************************************************************
	File name: B.cpp
	Author: huhao
	Create time: Sun 07 Jun 2020 08:22:30 PM CST
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
const int N=1000010;
int f,g,F,G,n;
char s[N];
void solve(int m,int w,int l,int r)
{
	if(l<0){ f=std::max(f,m); l+=2; }
	if(r>w){ g=std::max(g,m); r-=2; }
	if(l>r) return ;
	if(m>n){ printf("%d\n",w); exit(0); }
	if(s[m]=='0') solve(m+1,w,l+1,r+1);
	else if(s[m]=='1') solve(m+1,w,l-1,r-1);
	else solve(m+1,w,l-1,r+1);
}
int main()
{
	scanf("%s",s+1); n=strlen(s+1);
	f=g=1;
	fr(i,1,n)
	{
		F=f; G=g; f=-1; g=-1;
		if(F!=-1) solve(F,i,0,0);
		if(G!=-1) solve(G,i,i,i);
	}
	return 0;
}
