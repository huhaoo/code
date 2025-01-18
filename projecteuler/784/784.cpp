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
const int N=2000010;
int n;
std::vector<int> d[N];
int p[N],c[N],m;
void add(int u)
{
	while(u%2==0){ c[1]++; u/=2; }
	for(auto i:d[u]) if(i!=2){ m++; p[m]=i; c[m]=0; while(u%i==0){ u/=i; c[m]++; } }
}
i64 ans;
void solve(int k,int d,int r)
{
	if(d==m+1)
	{
		i64 u=k,v=(i64)(r-1)*(r+1)/k;
//		printf("%lld %lld %d\n",u,v,r);
		i64 p=u+r,q=v+r;
		if(p*r==q*u+1&&q*r==p*v+1)
		{
//			printf("%lld %lld\n",p,q);
			ans+=p+q;
		}
		return ;
	}
	fr(i,0,c[d])
	{
		solve(k,d+1,r);
		if((i64)k*p[d]+r<=n&&(i64)k*p[d]<=r) k*=p[d]; else break;
	}
}
int main()
{
	n=read();
	fr(i,2,n) if(!d[i].size()) fr(j,1,n/i) d[i*j].push_back(i);
	fr(i,2,n-1)
	{
		p[m=1]=2; c[1]=0; add(i-1); add(i+1);
//		fr(i,1,m) printf("%d %d\n",p[i],c[i]);
		solve(1,1,i);
	}
	printf("%lld\n",ans);
	return 0;
}