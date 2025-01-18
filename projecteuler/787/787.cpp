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
int n; i64 ans;
int m; int a[100];
int p[100000],c;
bool check(int u){ for(int i=2;i*i<=u;i++) if(u%i==0) return 0; return 1; }
void split(int u)
{
	m=0;
	for(int i=1;p[i]*p[i]<=u;i++) if(u%p[i]==0)
	{
		a[++m]=p[i]; while(u%p[i]==0) u/=p[i];
	}
	if(u>1) a[++m]=u;
}
int calc(int n,int p)
{
	if(!n||p>m) return n;
	return calc(n,p+1)-calc(n/a[p],p+1);
}
int main()
{
	fr(i,2,100000) if(check(i)) p[++c]=i;
	n=read();
	fr(i,1,n/2) if(i%2==1)
	{
		split(i); ans+=calc(n-i,1)-calc(i,1);
		if(i%10000000==1){ printf("%.5lf %.5lf\n",i*1./(n/2),clock()*1./CLOCKS_PER_SEC); fflush(stdout); }
//		printf("%d %d  %d %d\n",i,m,calc(n-i,1),calc(i,1));
	}
	printf("%lld\n",ans*2+1);
	return 0;
}