/****************************************************************
	File name: 3231.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/14/2018, 8:05:41 PM
****************************************************************/
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
#define N 5010
#define M 110
int t[N][N],p[N],ans,T,x[N],y[N],n,z[N],a,b,c,vis[N];
int check(int u)
{
	if(vis[u])return 0;vis[u]=1;
	fr(v,1,c)if(t[u][v]&&!p[v]){p[v]=u;return 1;}
	fr(v,1,c)if(t[u][v]&&check(p[v])){p[v]=u;return 1;}
	return 0;
}
int main()
{
	T=read();
	while(T--)
	{
		a=read();b=read();c=read();n=0;ans=(1<<20);
		fr(i,1,a)fr(j,1,b)fr(k,1,c)
			if(read()){n++;x[n]=i;y[n]=j;z[n]=k;}
		if(a>b||a>c)
		{
			if(b<c)
			{
				swap(a,b);
				fr(i,1,n)swap(x[i],y[i]);
			}
			else
			{
				swap(a,c);
				fr(i,1,n)swap(x[i],z[i]);
			}
		}
		if(b>c)
		{
			swap(b,c);
			fr(i,1,n)swap(y[i],z[i]);
		}
//		fr(i,1,n)printf("%d %d %d\n",x[i],y[i],z[i]);
		fr(i,0,(1<<a)-1)
		{
			int m=0,j=i;while(j)m++,j-=j&(-j);
			fr(j,1,b)fr(k,1,c)t[j][k]=0;
			fr(j,1,n)if(!((1<<(x[j]-1))&i))t[y[j]][z[j]]=1;
			fr(j,1,c)p[j]=0;
			fr(j,1,b)
			{
				fr(k,1,b)vis[k]=0;
				m+=check(j);
			}
			ans=min(ans,m);
//			printf("%d %d\n",i,m);
		}
		printf("%d\n",ans);
	}
	return 0;
}