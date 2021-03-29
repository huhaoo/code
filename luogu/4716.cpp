/**************************************************************
	File name: 4716.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/8/2018, 4:04:41 PM
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
#define N 110
#define E 10010
#define inf (1<<29)
int n,e,r,vis[N],ans,f[N],pre[N],u[E],v[E],w[E],l[N];
int main()
{
	n=read();
	e=read();
	r=read();
	fr(i,1,e)
	{
		u[i]=read();u[i]=u[i]==1?r:u[i]==r?1:u[i];
		v[i]=read();v[i]=v[i]==1?r:v[i]==r?1:v[i];
		w[i]=read();
	}
	while(1)
	{
		fr(i,2,n)l[i]=inf;
		fr(i,1,e)
			if(w[i]<l[v[i]])
			{
				pre[v[i]]=u[i];
				l[v[i]]=w[i];
			}
		fr(i,2,n)
			if(l[i]==inf)
			{
				printf("-1\n");
				return 0;
			}
			else ans+=l[i];
		fr(i,1,n)vis[i]=0;
		vis[1]=1;
		int nn=1;
		fr(i,1,n)f[i]=0;
		f[1]=1;
		fr(i,2,n)
			if(!vis[i])
			{
				int k=i;
				while(!vis[k])
				{
					vis[k]=i;
					k=pre[k];
				}
				if(vis[k]==i)
				{
					f[k]=++nn;
					int kk=pre[k];
					while(kk!=k)
					{
						f[kk]=nn;
						kk=pre[kk];
					}
				}
			}
		if(nn==1)break;
		fr(i,1,n)if(!f[i])f[i]=++nn;
//		printf("%d\n",nn);
//		fr(i,1,n)
//			printf("%d%c",f[i],i==n?'\n':' ');
		n=nn;
		int ee=0;
		fr(i,1,e)
		{
			int ll=l[v[i]];
			u[i]=f[u[i]];v[i]=f[v[i]];
			if(u[i]!=v[i])
			{
				ee++;
				u[ee]=u[i];v[ee]=v[i];w[ee]=w[i]-ll;
			}
		}
		e=ee;
	}
	printf("%d\n",ans);
	return 0;
}