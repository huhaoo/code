#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
const int N=5010,mod=998244353;
int n,k,p[N];
i64 ans;
int main()
{
	n=read(); k=read(); ans=1;
	fr(i,1,n) p[i]=read();
	fr(i,1,n)
	{
		int s=0,q=0;
		fr(j,1,n) if(p[j]>i) s++; else if(p[j]==i){ q=j; break; }
		assert(s<=k);
//		printf("%d %d\n",i,s);
		if(s==k) ans=ans*(n-q+1)%mod;
	}
	printf("%d\n",int(ans));
	return 0;
}