/***************************************************************
	File name: expression.cpp
	Author: huhao
	Create time: Fri 20 Nov 2020 05:39:36 PM CST
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
const int N=40010,inf=1000000000;
int n,m;
struct DP
{
	int f,p1,p2;
	DP(int F=0){ f=F; p1=p2=0; }
} f[N],F[N];
DP operator+(DP a,int b){ a.f+=b; return a; }
int operator>(DP a,DP b){ return a.f>b.f; }
char S[N],s[N],c[N];
int p[N],P[N];
int Min(DP &a,DP b){ if(a>b){ a=b; return 1; } return 0; }
int Min(int &a,int b){ if(a>b){ a=b; return 1; } return 0; }
void dp_all()
{
	fr(i,1,n)
	{
		if(s[i]=='(')
		{
			int j=p[i];
			if(s[j+1]=='*'||s[j+1]=='|') Min(f[j+2],f[i]);
			Min(f[i+1],f[i]);
		}
		else if(s[i]==')') Min(f[i+1],f[i]);
		else if(s[i]=='|')
		{
			if(s[i+1]=='(') Min(f[p[i+1]+1],f[i]);
			else Min(f[i+2],f[i]);
		}
		else if(s[i]=='*') Min(f[i+1],f[i]);
		else
		{
			if(s[i+1]=='*'||s[i+1]=='|') Min(f[i+2],f[i]);
			Min(f[i+1],f[i]+1);
		}
	}
}
void dp(int c)
{
	fr(t,1,2)
	{
		fr(i,1,n)
		{
			if(s[i]=='(')
			{
				int j=p[i];
				if(s[j+1]=='*'||s[j+1]=='|') Min(f[j+2],f[i]);
				Min(f[i+1],f[i]);
			}
			else if(s[i]==')') Min(f[i+1],f[i]);
			else if(s[i]=='|')
			{
				if(s[i+1]=='(') Min(f[p[i+1]+1],f[i]);
				else Min(f[i+2],f[i]);
			}
			else if(s[i]=='*')
			{
				Min(f[i+1],f[i]);
				int j=i-1; if(s[j]==')') j=p[j];
				Min(f[j],f[i]);
			}
			else
			{
				if(s[i+1]=='*'||s[i+1]=='|') Min(f[i+2],f[i]);
			}
		}
	}
	fr(i,1,n+1){ F[i]=f[i]; f[i]=inf; }
	fr(i,1,n) if(s[i]==c||s[i]=='.') Min(f[i+1],F[i]+1);
}
#include<string>
void print(int l,int r)
{
	static int f[N];
	static std::string g[N];
	fr(i,l,r){ f[i]=inf; g[i]=""; }
	f[l]=0;
	fr(i,l,r-1)
	{
		if(s[i]=='(')
		{
			int j=p[i];
			if(s[j+1]=='*'||s[j+1]=='|'){ if(Min(f[j+2],f[i])) g[j+2]=g[i]; }
			if(Min(f[i+1],f[i])) g[i+1]=g[i];
		}
		else if(s[i]==')'){ if(Min(f[i+1],f[i])) g[i+1]=g[i]; }
		else if(s[i]=='|')
		{
			if(s[i+1]=='('){ if(Min(f[p[i+1]+1],f[i])) g[p[i+1]+1]=g[i]; }
			else{ if(Min(f[i+2],f[i])) g[i+2]=g[i]; }
		}
		else if(s[i]=='*'){ if(Min(f[i+1],f[i])) g[i+1]=g[i]; }
		else
		{
			if(s[i+1]=='*'||s[i+1]=='|'){ if(Min(f[i+2],f[i])) g[i+2]=g[i]; }
			if(Min(f[i+1],f[i]+1)) g[i+1]=g[i]+(s[i]=='.'?'a':s[i]);
		}
	}
	fr(i,0,f[r]-1) putchar(g[r][i]);
}
int main()
{
	freopen("expression.in","r",stdin); freopen("expression.out","w",stdout);
	S[1]='('; scanf("%s%s",S+2,c+1);
	n=strlen(S+1); S[++n]=')'; m=strlen(c+1);
	static int a[N],lst[N],A;
	fr(i,1,n)
	{
		if(S[i]=='('){ A++; lst[A]=a[A]=i; }
		else if(S[i]==')')
		{
			if(i-lst[A]>=2){ P[i-1]=lst[A]+1; P[lst[A]+1]=i-1; }
			p[a[A]]=i; p[i]=a[A]; A--;
		}
		else if(S[i]=='|')
		{
			if(i-lst[A]>=2){ P[i-1]=lst[A]+1; P[lst[A]+1]=i-1; }
			lst[A]=i;
		}
	}
	int _n=n; n=0;
	fr(i,1,_n)
	{
		if(P[i])
		{
			if(P[i]>i) s[++n]='(';
			s[++n]=S[i];
			if(P[i]<i) s[++n]=')';
		}
		else s[++n]=S[i];
		if((S[i]=='('&&S[i+1]=='|')||(S[i]=='|'&&(S[i+1]==')'||S[i+1]=='|')))
		{
			s[++n]='('; s[++n]=')';
		}
	}
	memset(p,0,sizeof(p)); A=0;
	fr(i,1,n)
	{
		if(s[i]=='('){ A++; a[A]=i; }
		else if(s[i]==')'){ p[a[A]]=i; p[i]=a[A]; A--; }
	}
	fr(i,2,n+1) f[i]=inf;
	f[1]=0; dp_all();
	fr(i,1,n+1) f[i].p1=i;
	fr(i,1,m) dp(c[i]);
	fr(i,1,n+1) f[i].p2=i;
	dp_all();
	if(f[n+1].f>inf/2)
	{
		printf("NO\n");
		return 0;
	}
	print(1,f[n+1].p1); printf("%s",c+1); print(f[n+1].p2,n+1);
	return 0;
}
