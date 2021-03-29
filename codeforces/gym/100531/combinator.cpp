/***************************************************************
	File name: combinator.cpp
	Author: huhao
	Create time: Mon 28 Dec 2020 04:41:54 PM CST
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
const int N=30010;
int p[N];
char s[N],c[N];
int n,m;
int ans;
void Solve(int,int);
int solve(int _l,char *s,int &n)
{
	if(n<2) return 0;
	static int a[N],A; A=0;
	fr(i,1,n)
		if(s[i]=='(')
		{
			a[++A]=i;
		}
		else if(s[i]==')')
		{
			p[i]=a[A]; p[a[A]]=i; A--;
		}
		else p[i]=0;
	m=0;
	if(s[1]=='(')
	{
		fr(i,2,p[1]-1) c[++m]=s[i];
		fr(i,p[1]+1,n) c[++m]=s[i];
	}
	else if(s[1]=='I')
	{
		fr(i,2,n) c[++m]=s[i];
		ans++;
	}
	else if(s[1]=='K')
	{
		int l,r;
		if(s[2]=='(') l=p[2]+1;
		else l=3;
		if(n<l)
		{
			Solve(2+_l,l+_l-1);
			return 0;
		}
		if(s[l]=='(') r=p[l];
		else r=l;
		fr(i,2,l-1) c[++m]=s[i];
		fr(i,r+1,n) c[++m]=s[i];
		ans++;
	}
	else
	{
		int q[4]={2,0,0,0};
		fr(i,0,2)
		{
			if(s[q[i]]=='(') q[i+1]=p[q[i]]+1;
			else q[i+1]=q[i]+1;
			if(i!=2&&n<q[i+1])
			{
				fr(j,0,i) Solve(q[j]+_l,q[j+1]+_l-1);
				return 0;
			}
		}
		if(s[1]=='B')
		{
			fr(i,q[0],q[1]-1) c[++m]=s[i];
			c[++m]='(';
			fr(i,q[1],q[2]-1) c[++m]=s[i];
			fr(i,q[2],q[3]-1) c[++m]=s[i];
			c[++m]=')';
			fr(i,q[3],n) c[++m]=s[i];
		}
		else
		{
			fr(i,q[0],q[1]-1) c[++m]=s[i];
			fr(i,q[2],q[3]-1) c[++m]=s[i];
			fr(i,q[1],q[2]-1) c[++m]=s[i];
			fr(i,q[3],n) c[++m]=s[i];
		}
		ans++;
	}
/*	printf("%d %d\n",n,m);
	fr(i,1,n) putchar(s[i]);; putchar(10);
	fr(i,1,m) putchar(c[i]);; putchar(10);*/
	n=m;
	fr(i,1,n) s[i]=c[i];
//	int cnt=100; fflush(stdout); assert(--cnt);
	return 1;
}
void Solve(int l,int r)
{
	if(l>=r) return ;; r=r-l+1;
	while(solve(l-1,s+l-1,r)) ;
}
int main()
{
	freopen("combinator.in","r",stdin); freopen("combinator.out","w",stdout);
	scanf("%s",s+1); n=strlen(s+1); Solve(1,n);
	printf("%d\n",ans);
	return 0;
}
