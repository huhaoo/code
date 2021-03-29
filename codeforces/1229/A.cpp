/****************************************************************
*	Author: huhao
*	Email: 826538400@qq.com
*	Create time: 2019-09-23 22:13:04
****************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define int long long
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
const int N=7010;
int n,a[N],b[N],ans,r[N];
signed main()
{
	n=read();
	fr(i,1,n)
		a[i]=read();
	fr(i,1,n)
		b[i]=read();
	fr(i,1,n)
		r[i]=i;
	sort(r+1,r+n+1,[&](int A,int B){return a[A]>a[B];});
	a[0]=a[n+1]=-1;
	fr(i,1,n)
	{
		int flag=a[r[i]]==a[r[i-1]]||a[r[i]]==a[r[i+1]];
		fr(j,2,i)
			if(a[r[j]]==a[r[j-1]]&&(a[r[i]]&a[r[j]])==a[r[i]])
				flag=1;
		if(flag)
			ans+=b[r[i]];
	}
	printf("%I64d\n",ans);
	return 0;
}