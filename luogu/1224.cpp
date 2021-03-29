/**************************************************************
	File name: 1224.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/1/2018, 8:39:28 PM
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
#define N 100010
#define D 110
int n,d,p,v[N][D],s[D],c[D][D];
int times(int *a,int *b,int l)
{
	int r=0;
	fr(i,1,l)
		r+=a[i]*b[i];
	return r;
}
int calc(int k)
{
	int r=0;
	if(d==2)
		fr(i,1,d)
			r+=s[i]*c[k][i];
	else
		fr(i,1,d)
			fr(j,1,d)
				r+=c[i][j]*v[k][i]*v[k][j];
	if(d==2)
		fr(i,1,d)
			s[i]+=c[k][i];
	else
		fr(i,1,d)
			fr(j,1,d)
				c[i][j]+=v[k][i]*v[k][j];
	return r;
}
int main()
{
	n=read();
	d=read();
	p=read();
	fr(i,1,n)
		fr(j,1,d)
			v[i][j]=read()%p;
	fr(i,1,n)
		if(calc(i)%p!=(i-1)%p)
			fr(j,1,i-1)
				if(times(v[i],v[j],d)%p==0)
				{
					if(i>j)swap(i,j);
					printf("%d %d\n",i,j);
					return 0;
				}
	printf("-1 -1\n");
	return 0;
}