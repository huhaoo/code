/**************************************************************
	File name: 5468.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2019/7/21 上午9:30:37
**************************************************************/
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
struct road
{
	int u,v,x,y;
	road(int _u=0,int _v=0,int _x=0,int _y=0)
	{
		u=_u;
		v=_v;
		x=_x;
		y=_y;
	}
}a[N];
#define i64 long long
struct dp
{
	int t;
	i64 f;
	dp(int _t=0,i64 _f=0)
	{
		t=_t;
		f=_f;
	}
};
#include<vector>
int n,m;
i64 A,B,C;
int cmp(road a,road b)
{
	return a.y<b.y;
}
vector<dp>f[N];
int main()
{
	n=read();
	m=read();
	A=read();
	B=read();
	C=read();
	fr(i,1,m)
	{
		a[i].u=read();
		a[i].v=read();
		a[i].x=read();
		a[i].y=read();
	}
	sort(a+1,a+m+1,cmp);
	f[1].push_back(dp(0,0));
	fr(i,1,m)
	{
		i64 _f=1ll<<40;
		fr(j,0,f[a[i].u].size()-1)
		{
			dp d=f[a[i].u][j];
			if(d.t<=a[i].x)
			{
				i64 dt=a[i].x-d.t;
				_f=min(_f,d.f+(A*dt+B)*dt+C);
			}
			else
				break;
		}
		if(_f>=(1ll<<40))
			continue;
		if(f[a[i].v].size()&&f[a[i].v][f[a[i].v].size()-1].t==a[i].y)
			f[a[i].v][f[a[i].v].size()-1].f=min(f[a[i].v][f[a[i].v].size()-1].f,_f);
		else
			f[a[i].v].push_back(dp(a[i].y,_f));
	}
	i64 ans=1ll<<40;
	fr(i,0,f[n].size()-1)
		ans=min(ans,f[n][i].t+f[n][i].f);
	printf("%lld\n",ans);
	return 0;
}