/**************************************************************
	File name: 4735.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/13/2018, 4:56:52 PM
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
#define N 600010
#define B 25
int n,r[N],s[N*B+N][2],cnt,w[N*B+N],q,x;
char opt[10];
int main()
{
	n=read();q=read();
	fr(i,1,n)
	{
		int v=read()^x;x=v;
		r[i]=++cnt;int a=r[i],b=r[i-1];
		w[a]=w[b]+1;
		fd(j,B,0)
		{
			int o=!!(v&(1<<j));
			s[a][o^1]=s[b][o^1];
			s[a][o]=++cnt;a=s[a][o];b=s[b][o];
			w[a]=w[b]+1;
		}
	}
	while(q--)
	{
		scanf("%s",opt);
		if(*opt=='A')
		{
			int v=read()^x;n++;x=v;
			r[n]=++cnt;int a=r[n],b=r[n-1];
			w[a]=w[b]+1;
			fd(j,B,0)
			{
				int o=!!(v&(1<<j));
				s[a][o^1]=s[b][o^1];
				s[a][o]=++cnt;a=s[a][o];b=s[b][o];
				w[a]=w[b]+1;
			}
		}
		else
		{
			int l=read()-2,rr=read()-1,v=read()^x;
			int a=r[rr],b=r[l],ans=0;
			if(l<0)l=0;
			fd(j,B,0)
			{
				int o=!(v&(1<<j));
				if(w[s[a][o]]>w[s[b][o]])a=s[a][o],b=s[b][o],ans|=1<<j;
				else a=s[a][o^1],b=s[b][o^1];
			}
			if(l==0)ans=max(ans,v);
			printf("%d\n",ans);
		}
	}
	return 0;
}