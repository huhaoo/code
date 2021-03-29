/**************************************************************
	File name: 4148.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 3/13/2019, 4:16:08 PM
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
#define N 200010
#define rbf 0.9
#define rbi 20
int m,n,s[N][2],x[N],y[N],c[N],t,ans,v[N],r,w[N],p[N],e,rb,rbo;
struct reb
{
	int x,y,v;
}a[N];
int cmp1(reb a,reb b)
{
	return a.x<b.x;
}
int cmp0(reb a,reb b)
{
	return a.y<b.y;
}
void del(int k,int o)
{
	if(!k)
		return;
	e++;
	a[e].x=x[k];
	a[e].y=y[k];
	a[e].v=v[k];
	del(s[k][0],1);
	del(s[k][1],1);
	if(o)
		c[++t]=k;
	x[k]=y[k]=s[k][0]=s[k][1]=w[k]=v[k]=p[k]=0;
}
int build(int l,int r,int o)
{
	if(l>r)
		return 0;
	int k;
	if(t)
	{
		k=c[t];
		t--;
	}
	else
		k=++n;
	if(o)
		nth_element(a+l,a+(l+r)/2,a+r+1,cmp1);
	else
		nth_element(a+l,a+(l+r)/2,a+r+1,cmp0);
	x[k]=a[(l+r)/2].x;
	y[k]=a[(l+r)/2].y;
	v[k]=a[(l+r)/2].v;
	p[k]=r-l+1;
	s[k][0]=build(l,(l+r)/2-1,o^1);
	s[k][1]=build((l+r)/2+1,r,o^1);
	w[k]=w[s[k][0]]+w[s[k][1]]+v[k];
	return k;
}
void rebuild(int k,int o)
{
	e=0;
	del(k,0);
	if(o)
		nth_element(a+1,a+(e+1)/2,a+e+1,cmp1);
	else
		nth_element(a+1,a+(e+1)/2,a+e+1,cmp0);
	x[k]=a[(e+1)/2].x;
	y[k]=a[(e+1)/2].y;
	v[k]=a[(e+1)/2].v;
	p[k]=e;
	s[k][0]=build(1,(e+1)/2-1,o^1);
	s[k][1]=build((e+1)/2+1,e,o^1);
	w[k]=w[s[k][0]]+w[s[k][1]]+v[k];
}
void insert(int k,int o,int _x,int _y,int _v)
{
	int op;
	w[k]+=_v;
	p[k]++;
	if(o)
		op=(_x>=x[k]);
	else
		op=(_y>=y[k]);
	if(!s[k][op])
	{
		if(t)
		{
			s[k][op]=c[t];
			t--;
		}
		else
		{
			n++;
			s[k][op]=n;
		}
		k=s[k][op];
		x[k]=_x;
		y[k]=_y;
		v[k]=w[k]=_v;
		p[k]=1;
	}
	else
		insert(s[k][op],o^1,_x,_y,_v);
	if(p[k]>rbi&&(p[k]*rbf<p[s[k][0]]*1.||p[k]*rbf<p[s[k][1]]*1.))
	{
		rb=k;
		rbo=o;
	}
}
int query(int k,int o,int _x,int _y,int xx,int yy,int qx,int qy,int qxx,int qyy)
{
	if(_x>qxx||xx<qx||_y>qyy||yy<qy||k==0)
		return 0;
	if(_x>=qx&&xx<=qxx&&_y>=qy&&yy<=qyy)
		return w[k];
	int r=0;
	if(x[k]>=qx&&x[k]<=qxx&&y[k]>=qy&&y[k]<=qyy)
		r=v[k];
	if(o)
		return r+query(s[k][0],o^1,_x,_y,x[k],yy,qx,qy,qxx,qyy)+query(s[k][1],o^1,x[k],_y,xx,yy,qx,qy,qxx,qyy);
	else
		return r+query(s[k][0],o^1,_x,_y,xx,y[k],qx,qy,qxx,qyy)+query(s[k][1],o^1,_x,y[k],xx,yy,qx,qy,qxx,qyy);
}
int main()
{
	m=read();
	while(1)
	{
		int opt=read();
		if(opt==3)
			break;
		if(opt==1)
		{
			int _x=read()^ans,_y=read()^ans,_v=read()^ans;
			rb=0;
			if(!n)
			{
				r=n=1;
				x[r]=_x;
				y[r]=_y;
				v[r]=w[r]=_v;
				p[r]=1;
			}
			else
				insert(r,1,_x,_y,_v);
			if(rb)
				rebuild(rb,rbo);
		}
		if(opt==2)
		{
			int _x=read()^ans,_y=read()^ans,_xx=read()^ans,_yy=read()^ans;
			ans=query(r,1,1,1,m,m,_x,_y,_xx,_yy);
			printf("%d\n",ans);
		}
	}
	return 0;
}