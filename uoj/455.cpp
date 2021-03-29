/***************************************************************
	File name: 455.cpp
	Author: huhao
	Create time: Sun 17 Jan 2021 03:02:51 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
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
#include<queue>
#include<vector>
#define pii std::pair<i64,i64>
const int N=200010;
int n,m;
std::vector<int> a[N];
std::priority_queue<pii,std::vector<pii>,std::greater<pii> > q1,q2;
i64 ans;
void ins(i64 a)
{
	pii t=q2.top(); q2.pop();
	t.second--; if(t.second) q2.push(t);
	i64 p=t.first;
	ans+=a+p; q1.push({-(a+a+p),1});
}
void Ins(i64 a,i64 b,i64 c)
{
	i64 s=0;
	while(c&&q1.top().first+a+b<0)
	{
//		printf("%lld %lld  %lld\n",c,q1.top().second,q1.size());
		pii t=q1.top(); i64 k=std::min(c,t.second); q1.pop();
		ans+=(t.first+a+b)*k; s+=k; c-=k; t.second-=k;
		if(t.second) q1.push(t);
		q2.push({-(a+a+t.first),k});
//		q1.push({-a-b,k});
	}
	if(c) q2.push({-a+b,c});
	if(s) q1.push({-a-b,s});
}
int main()
{
	n=read(); m=read(); i64 sn=0;
	fr(i,1,n) a[i]={read(),-1};
	fr(i,1,m){ int p=read(),x=read(),y=read(); a[++n]={p,x,y}; sn+=y; }
	std::sort(a+1,a+n+1); if(n-m>sn){ printf("-1\n"); return 0; }
	q1.push({1ll<<50,1ll<<50}); q2.push({1ll<<50,1ll<<50});
	fr(i,1,n)
		if(a[i][1]==-1) ins(a[i][0]);
		else Ins(a[i][0],a[i][1],a[i][2]);
	printf("%lld\n",ans);
	return 0;
}
