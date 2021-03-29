/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Sun 29 Nov 2020 08:25:08 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
i64 read()
{
	i64 r=0,t=1,c=getchar();
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
#include<map>
const int N=100010;
int n,m;
i64 a[N];
std::map<i64,i64> t;
i64 s[N];
int main()
{
	n=read(); a[m=1]=n;
	fr(i,1,read())
	{
		i64 x=read();
		while(x<a[m]) m--;
		a[++m]=x;
	}
	t[a[m]]++;
	fd(i,m,1)
	{
		i64 p=a[i];
		while((--t.end())->first>p)
		{
			auto k=*--t.end();
//			printf("%lld   %lld %lld\n",p,k.first,k.second);
			t[p]+=(k.first/p)*k.second; t[k.first%p]+=k.second; t.erase(k.first);
		}
//		for(auto i:t) printf("(%lld,%lld) ",i.first,i.second);; putchar(10);
	}
	for(auto i:t) s[i.first]+=i.second;
	fd(i,n,1) s[i]+=s[i+1];
	fr(i,1,n) printf("%lld\n",s[i]);
	return 0;
}
