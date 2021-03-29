/**************************************************************
	File name: 1973.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/7/2018, 8:37:25 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
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
#define N 1010
#define inf (1<<29)
int n,u[N],v[N],q[N],num[N][N],pre[N][N],suf[N][N],f[N][N],cnt;
int main()
{
	n=read();
	fr(i,1,n)
	{
		q[i*2-1]=u[i]=read();
		q[i*2]=v[i]=u[i]+read();
	}
	q[0]=-1;
	sort(q+1,q+n*2+1);
	fr(i,1,n*2)
		if(q[i]!=q[i-1])
			q[++cnt]=q[i];
//	fr(i,1,cnt)printf("%d%c",q[i],i==cnt?'\n':' ');
//	fr(i,1,n)printf("%d %d\n",u[i],v[i]);
//	putchar(10);
	fr(i,1,n)fr(j,1,cnt)if(u[i]==q[j]){u[i]=j;break;}
	fr(i,1,n)fr(j,1,cnt)if(v[i]==q[j]){v[i]=j;break;}
//	fr(i,1,n)printf("%d %d\n",u[i],v[i]);
	fr(i,1,n)
		fd(j,u[i],1)
			fr(k,v[i],cnt)
				num[j][k]++;
//	fr(i,1,cnt)
//		fr(j,1,cnt)
//			printf("%d%c",num[i][j],j==cnt?'\n':' ');
	fr(i,1,cnt)fr(j,1,n)pre[i][j]=suf[i][j]=-inf;
	fr(i,1,cnt)
	{
		fr(j,0,num[1][i])pre[i][j]=pre[i-1][j];
		fr(j,0,num[1][i])
			fr(k,1,i)
			{
				pre[i][j]=max(pre[i][j],pre[k][j]+num[k][i]);
				if(j>=num[k][i])pre[i][j]=max(pre[i][j],pre[k][j-num[k][i]]);
			}
	}
//	fr(i,1,cnt)fr(j,0,n)printf("%d%c",pre[i][j],j==n?'\n':' ');
	fd(i,cnt,1)
	{
		fr(j,0,num[i][cnt])suf[i][j]=suf[i+1][j];
		fr(j,0,num[i][cnt])
			fr(k,i+1,cnt)
			{
				suf[i][j]=max(suf[i][j],suf[k][j]+num[i][k]);
				if(j>=num[i][k])suf[i][j]=max(suf[i][j],suf[k][j-num[i][k]]);
			}
	}
	int ans=0;
	fr(i,1,n)ans=max(ans,min(i,pre[cnt][i]));
	printf("%d\n",ans);
	fr(i,1,cnt)
		fr(j,i+1,cnt)
		{
			int y=n;
			fr(x,0,n)
			{
				while(y)
				{
					if(min(x+y,pre[i][x]+num[i][j]+suf[j][y])<=min(x+y-1,pre[i][x]+num[i][j]+suf[j][y-1]))y--;
					else break;
				}
				f[i][j]=max(f[i][j],min(x+y,pre[i][x]+num[i][j]+suf[j][y]));
			}
		}
	fr(i,1,n)
	{
		ans=0;
		fd(j,u[i],1)
			fr(k,v[i],cnt)
				ans=max(ans,f[j][k]);
		printf("%d\n",ans);
	}
	return 0;
}