/***************************************************************
	File name: 1256B.cpp
	Author: huhao
	Create time: Mon 04 Nov 2019 09:19:10 PM CST
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
const int N=110;
int q,n,a[N];
int main()
{
	q=read();
	while(q--)
	{
		n=read();
		fr(i,1,n)
			a[i]=read();
		fr(i,1,n-1)
		{
			int p=i+1;
			fr(j,i+2,n)
				if(a[j]<a[p])
					p=j;
			if(a[p]>a[i])
				continue;
			fd(j,p-1,i)
				swap(a[j],a[j+1]);
			i=p-1;
		}
		fr(i,1,n)
			printf("%d%c",a[i],i==n?'\n':' ');
	}
	return 0;
}
