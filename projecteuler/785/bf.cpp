#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9'){ t=c=='-'?-1:1; c=getchar(); }
	while(c>='0'&&c<='9'){ r=(r<<3)+(r<<1)+(c^48); c=getchar(); }
	return r*t;
}
int main()
{
	int n=1000; i64 ans=0;
	fr(x,1,n) fr(y,x,n)
	{
		i64 k=(i64)x*x+17ll*x*y+(i64)y*y,K=0;
		fd(i,30,0) if((K+(1<<i))*(K+(1<<i))<=k) K+=1<<i;
		if(K*K==k)
		{
			i64 Z=17*(x+y)+8*K;
			if(Z%15==0&&Z/15<=n)
			{
				int z=Z/15;
				if(y<=z&&std::__gcd(x,std::__gcd(y,z))==1){ ans+=x+y+z; }// printf("%d %d %d\n",x,y,z);
			}
		}
	}
	printf("%I64d\n",ans);
	return 0;
}