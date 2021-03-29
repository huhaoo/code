/***************************************************************
	File name: 2168.cpp
	Author: huhao
	Create time: Tue 11 Jun 2019 09:34:14 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define i64 long long
#define fr(i,a,b) for(i64 i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(i64 i=(a),end_##i=(b);i>=end_##i;i--)
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
#include<queue>
struct word
{
	i64 l,w;
	word(i64 _l=0,i64 _w=0)
	{
		l=_l;
		w=_w;
	}
};
bool operator<(word a,word b)
{
	return a.w==b.w?a.l>b.l:a.w>b.w;
}
priority_queue<word>q;
i64 n,k,ans;
int main()
{
	n=read();
	k=read();
	fr(i,1,n)
		q.push(word(0,read()));
	i64 i=(n-1)/(k-1);
	if(i*(k-1)+1!=n)
	{
		word a,b;
		fr(j,i*(k-1)+1,n)
		{
			a=q.top();
			q.pop();
			b.l=max(b.l,a.l+1);
			b.w+=a.w;
		}
		ans+=b.w;
		q.push(b);
	}
	while(i--)
	{
		word a,b;
		fr(j,1,k)
		{
			a=q.top();
			q.pop();
			b.l=max(b.l,a.l+1);
			b.w+=a.w;
		}
		ans+=b.w;
		q.push(b);
	}
	printf("%lld\n%lld\n",ans,q.top().l);
	return 0;
}
