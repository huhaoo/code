/***************************************************************
	File name: F.cpp
	Author: huhao
	Create time: Mon 20 Jan 2020 04:12:26 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
#define pii std::pair<i64,i64>
const int N=100010;
i64 w[N],f[N],n,D[N];
pii d[N];
int main()
{
	n=read();
	fr(i,1,n) d[i]=pii(read(),i);
	std::sort(d+1,d+n+1);
	fr(i,1,n) w[i]=1;
	fd(i,n,2)
	{
		pii F=*lower_bound(d+1,d+n+1,pii(d[i].first+w[d[i].second]-(n-w[d[i].second]),0));
//		printf("%lld %lld\n",d[i].second,F.second);
		if(F.first!=d[i].first+w[d[i].second]-(n-w[d[i].second])){ printf("-1\n"); return 0; }
		f[d[i].second]=F.second; w[F.second]+=w[d[i].second];
	}
	fd(i,n,2) D[f[d[i].second]]+=D[d[i].second]+w[d[i].second];
	if(D[d[1].second]!=d[1].first){ printf("-1\n"); return 0; }
	fd(i,n,2) printf("%lld %lld\n",d[i].second,f[d[i].second]);
	return 0;
}
