/***************************************************************
	File name: 1214D.cpp
	Author: huhao
	Create time: Wed 04 Sep 2019 07:23:23 PM CST
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
#define N 4000015
int n,m,c[N],v[N],p[N],l,r;
inline int id(int x,int y)
{
    return x*m+y;
}
struct point
{
    int x,y;
    point(int X=0,int Y=0)
	{
		x=X;
		y=Y;
	}
};
point Q[N];
void bfs(){
    Q[l=r=1]=point(n,m);
    p[id(n,m)]=1;
    while(l<=r)
	{
        point w=Q[l++];
        int x=w.x,y=w.y;
        if(x>1&&!p[id(x-1,y)]&&c[id(x-1,y)]!='#')
		{
            Q[++r]=point(x-1,y);
            p[id(x-1,y)]=1;
        }
        if(y>1&&!p[id(x,y-1)]&&c[id(x,y-1)]!='#')
		{
            Q[++r]=point(x,y-1);
            p[id(x,y-1)]=1;
        }
    }
}
int main(){
	n=read();
	m=read();
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
		{
            int now=id(i,j);
            c[now]=getchar();
            while(c[now]!='.'&&c[now]!='#')c[now]=getchar();
        }
    bfs();
    Q[l=r=1]=point(1,1);
    int ans=2;
    while(l<=r)
	{
        point w=Q[l++];
        int x=w.x,y=w.y;
        if(x<n&&!v[id(x+1,y)]&&p[id(x+1,y)]&&c[id(x+1,y)]!='#')
		{
            Q[++r]=point(x+1,y);
            v[id(x+1,y)]=1;
        }
        if(y<m&&!v[id(x,y+1)]&&p[id(x,y+1)]&&c[id(x,y+1)]!='#')
		{
            Q[++r]=point(x,y+1);
            v[id(x,y+1)]=1;
        }
        if(v[id(n,m)])
			break;
        ans=min(ans,r-l+1);
    }
    printf("%d\n",ans);
    return 0;
}
