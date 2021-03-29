/**************************************************************
	File name: 1955.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/6/2018, 3:37:09 PM
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
#include<map>
int f[N],n,t,cnt,u[N],v[N],tot;
map<int,int>a;
int q(int k)
{
	if(a[k])return a[k];
	else return a[k]=++cnt;
}
int getf(int x)
{
	return f[x]=(f[x]==x?x:getf(f[x]));
}
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		a.clear();
		cnt=tot=0;
		fr(i,1,n*2)f[i]=i;
		fr(i,1,n)
		{
			int uu=read(),vv=read(),opt=read();
			if(opt)f[getf(q(uu))]=getf(q(vv));
			else
			{
				tot++;
				u[tot]=uu;
				v[tot]=vv;
			}
		}
		fr(i,1,tot)
			if(getf(q(u[i]))==getf(q(v[i])))
			{
				printf("NO\n");
				goto end;
			}
		printf("YES\n");
		end:;
		fr(i,1,2*n)f[i]=0;
	}
	return 0;
}