/***************************************************************
	File name: 1244D.cpp
	Author: huhao
	Create time: Sun 13 Oct 2019 05:28:05 PM CST
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
const int N=100010;
i64 n,a[N][10],A[N],p[N],m,c[10][N],r,ans,Ans,col[N];
int main()
{
	n=read();
	fr(i,1,3)
		fr(j,1,n)
			c[i][j]=read();
	fr(i,1,n-1)
	{
		int u=read(),v=read();
		A[u]++;
		A[v]++;
		if(A[u]>2||A[v]>2)
		{
			printf("-1\n");
			return 0;
		}
		a[u][A[u]]=v;
		a[v][A[v]]=u;
	}
	fr(i,1,n)
		if(A[i]==1)
		{
			r=i;
			break;
		}
	p[1]=r;
	fr(i,1,n-1)
		p[i+1]=a[p[i]][1]^a[p[i]][2]^p[i-1];
	ans=1ll<<50;
	fr(i,1,3)
		fr(j,1,3)
			fr(k,1,3)
				if(i!=j&&i!=k&&j!=k)
				{
					i64 t=0;
					col[1]=i;
					col[2]=j;
					col[3]=k;
					fr(l,4,n)
						col[l]=col[l-3];
					fr(l,1,n)
						t+=c[col[l]][p[l]];					
					if(t<ans)
					{
						ans=t;
						Ans=i*100+j*10+k;
					}
				}
	int i,j,k;
	i=Ans/100;
	j=(Ans/10)%10;
	k=Ans%10;
	col[p[1]]=i;
	col[p[2]]=j;
	col[p[3]]=k;
	fr(l,4,n)
		col[p[l]]=col[p[l-3]];
	printf("%I64d\n",ans);
	fr(l,1,n)
		printf("%d%c",(int)col[l],l==n?'\n':' ');
	return 0;
}
