/***************************************************************
	File name: 3188.cpp
	Author: huhao
	Create time: Mon 04 Nov 2019 03:29:47 PM CST
***************************************************************/
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
		r=r*10+c-48;
		c=getchar();
	}
	return r*t;
}
#define i64 long long
const int N=1010,L=40;
int n,a[N],b[N],v[N],m;
const i64 inf=1ll<<50;
i64 w,f[L+5][N],ans;
int main()
{
	while(1)
	{
		n=m=w=ans=0;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(v,0,sizeof(v));
		memset(f,0,sizeof(f));
		n=read();
		w=read();
		if(n==-1||w==-1)
			break;
		m=n*5;
		fr(i,1,n)
		{
			a[i]=read();
			v[i]=read();
			while(a[i]%2==0)
			{
				b[i]++;
				a[i]/=2;
			}
		}
		fr(i,0,L)
			fr(j,0,m)
				f[i][j]=-inf;
		f[L][0]=0;
		fd(i,L-1,0)
		{
			fr(j,0,m)
			{
				i64 J=min(j*2+((w>>i)&1),(i64)m);
				f[i][J]=max(f[i][J],f[i+1][j]);
			}
			fr(j,1,n)
				if(b[j]==i)
					fr(k,0,m-a[j])
						f[i][k]=max(f[i][k],f[i][k+a[j]]+v[j]);
		}
/*		fd(i,L,0)
			fr(j,0,m)
				printf("%lld%c",f[i][j]<0?-1:f[i][j],j==m?'\n':' ');*/
		fr(i,0,m)
			ans=max(ans,f[0][i]);
		printf("%lld\n",ans);
	}
	return 0;
}
