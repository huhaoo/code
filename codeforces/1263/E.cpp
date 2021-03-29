/****************************************************************
*	Author: huhao
*	Email: 826538400@qq.com
*	Create time: 2019-11-29 22:42:23
****************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
const int N=4000010;
int n,p,a[N],m[N],M[N],s[N];
char opt[N];
void update(int k)
{
	m[k]=min(m[k<<1],m[k<<1|1]+s[k<<1]);
	M[k]=max(M[k<<1],M[k<<1|1]+s[k<<1]);
	s[k]=s[k<<1]+s[k<<1|1];
}
void modify(int k,int l,int r,int p,int opt)
{
	if(l==r)
	{
		s[k]=opt; m[k]=min(s[k],0); M[k]=max(s[k],0);
		return;
	}
	int mid=(l+r)>>1;
	if(p<=mid) modify(k<<1,l,mid,p,opt);
	else modify(k<<1|1,mid+1,r,p,opt);
	update(k);
}
int main()
{
	n=read(); p=1;
	scanf("%s",opt+1);
	fr(i,1,n)
	{
		if(opt[i]=='L'||opt[i]=='R')
		{
			p+=opt[i]=='L'?-1:1;
			if(p==0) p=1;
		}
		else
		{
			modify(1,1,n,p,-a[i]);
			if(opt[i]=='(') a[i]=1;
			else if(opt[i]==')') a[i]=-1;
			else a[i]=0;
			modify(1,1,n,p,a[i]);
		}
		if(s[1]!=0||m[1]<0) printf("-1");
		else printf("%d",M[1]);
		putchar(i==n?'\n':' ');
	}
	return 0;
}