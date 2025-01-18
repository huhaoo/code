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
const int N=110;
const i64 inf=1ll<<60;
const long double eps=1e-10;
i64 F[N];
i64 C(i64 a,i64 b)
{
	if(a<b||b<0) return 0;
	i64 ans=1; if(b>a-b) b=a-b;
	fr(i,0,b-1)
	{
		if(ans/(i+1)>inf/(a-i)) return inf;
		ans=ans*(a-i)/(i+1);
		if(ans>=inf) return inf;
	}
	return ans;
}
i64 calc(long double a,long double b,long double s)
{
	static i64 m,f[N];
	if(a<b) std::swap(a,b);
	m=std::min(64ll,(i64)(s/a)); f[m+1]=-1;
	fr(i,0,m) f[i]=(i64)((s-a*i)/b);
	i64 ans=0;
	fr(i,0,m){ ans+=C(i+1+f[i],i+1); if(ans>=inf) return inf; }
	return ans;
}
long double solve(i64 n,long double a,long double b)
{
	if(a>b) std::swap(a,b);
	long double l=0,r=b*60;
	while(r-l>eps)
	{
		long double mid=(l+r)/2;
		if(calc(a,b,mid)>=n) r=mid;
		else l=mid;
	}
	return l;
}
int main()
{
	F[1]=F[2]=1; fr(i,3,30) F[i]=F[i-1]+F[i-2];
	long double ans=0;
	fr(i,1,30)
	{
		i64 n=1'000'000'000'000; long double a=sqrt(i),b=sqrt(F[i]);
		long double Ans=solve(n,a,b);
		printf("%.10Lf\n",Ans);
		ans+=Ans;
	}
	printf("%.10Lf\n",ans);
	return 0;
}