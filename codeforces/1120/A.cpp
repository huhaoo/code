/****************************************************************
	File name: 1120A.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 3/3/2019, 11:58:18 PM
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
#define N 500010
int m,k,s,n,a[N],b[N],t[N],p1,p2,c[N],l;
int main()
{
	m=read();
	k=read();
	n=read();
	s=read();
	fr(i,1,m)
		a[i]=read();
	fr(i,1,s)
		b[i]=read();
	p1=1;
	p2=m-(n-1)*k;
	fr(i,p1,p2)
		t[a[i]]++;
	fr(i,1,n)
	{
		int f=1;
		fr(j,1,s)
		{
			t[b[j]]--;
			if(t[b[j]]<0)
				f=0;
		}
		if(f)
		{
			printf("%d\n",m-n*k);
			l=k-s;
			fr(j,1,s)
				c[b[j]]++;
			fr(j,p1,p2)
				if(c[a[j]])
					c[a[j]]--;
				else if(l)
					l--;
				else
					printf("%d ",j);
			putchar('\n');
			return 0;
		}
		fr(j,1,s)
			t[b[j]]++;
		fr(j,p1,p1+k-1)
			t[a[j]]--;
		fr(j,p2+1,p2+k)
			t[a[j]]++;
		p1+=k;
		p2+=k;
	}
	printf("-1\n");
	return 0;
}