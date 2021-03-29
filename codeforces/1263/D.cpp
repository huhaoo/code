/****************************************************************
*	Author: huhao
*	Email: 826538400@qq.com
*	Create time: 2019-11-29 22:56:40
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
const int N=200010;
int n,f[N],p[N],ans;
char s[N];
int getf(int x){ return x==f[x]?x:f[x]=getf(f[x]); }
int main()
{
	n=read();
	fr(i,'a','z') f[i]=i;
	fr(i,1,n)
	{
		scanf("%s",s+1);
		fr(j,2,strlen(s+1)) f[getf(s[j])]=getf(s[1]);
		fr(j,1,strlen(s+1)) p[s[j]]=1;
	}
	fr(i,'a','z') if(p[getf(i)])
	{
		p[getf(i)]=0;
		ans++;
	}
	printf("%d\n",ans);
	return 0;
}