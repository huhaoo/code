/**************************************************************
	File name: 1205B.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2019/8/18 下午9:52:42
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(long long i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(long long i=(a),end_##i=(b);i>=end_##i;i--)
long long read()
{
	long long r=0,t=1,c=getchar();
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
const long long N=1010,inf=1ll<<50;
long long n,a[N],f[N][N],ans,d[N],q[N],l,r;
int main()
{
	fr(t,1,read())
	{
		n++;
		a[n]=read();
		if(!a[n])
			n--;
		if(n>=100)
		{
			printf("3\n");
			return 0;
		}
	}
	fr(i,1,n)
		fr(j,1,n)
			if(i!=j&&(a[i]&a[j]))
			{
				f[i][j]=1;
			}
	ans=n+1;
	fr(i,1,n)
		fr(j,1,n)
			if(f[i][j])
			{
				f[i][j]=0;
				fr(k,1,n)
					d[k]=inf;
				d[i]=0;
				q[l=r=1]=i;
				while(l<=r)
				{
					int u=q[l];
					l++;
					fr(v,1,n)
						if(f[u][v]&&d[u]+1<d[v])
						{
							d[v]=d[u]+1;
							q[++r]=v;
						}
				}
				ans=min(ans,d[j]+1);
				f[i][j]=1;
			}
	if(ans==n+1)
		ans=-1;
	printf("%I64d\n",ans);
	return 0;
}