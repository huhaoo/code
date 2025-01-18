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
const int N=10000010;
i64 n;
i64 calc(i64 d)
{
	i64 ans=0;
	for(i64 i=0,j=n/d;i<=n/d;i++)
	{
		while((i*i+j*j)*d*d>n*n) j--;
		ans+=j;
	}
//	printf("%lld %lld\n",d,ans);
	return ans;
}
int v[N],p[N],m;
i64 P[N],M;
i64 Mu[N];
i64 ans;
int main()
{
	n=10000000;
	fr(i,2,n)
	{
		if(!v[i])
		{
			p[++m]=i;
			if(i==2){ P[++M]=i; }
			else if(i%4==3){ P[++M]=(i64)i*i; }
			else{ P[++M]=i; P[++M]=i; }
		}
		fr(j,1,m) if(i*p[j]<=n)
		{
			v[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
		else break;
	}
	Mu[1]=1;
	fr(i,1,M) fd(j,n/P[i],1) Mu[j*P[i]]-=Mu[j];
//	fr(i,1,n) printf("%lld%c",Mu[i],i==n?'\n':' ');
//	fr(i,1,n) printf("%lld%c",calc(i),i==n?'\n':' ');
	fr(i,1,n) ans+=Mu[i]*calc(i);
	printf("%lld\n",ans);
	return 0;
}