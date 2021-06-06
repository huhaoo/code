#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
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
const int N=100010;
i64 n,x,y;
i64 a[N],b[N],d[N];
i64 l,r;
bool check(i64 v)
{
	fr(i,1,n)
	{
		i64 l=a[i]*y-v,r=a[i]*y+v;
		l=std::max(l,0ll); l=(l+x-1)/x; r=r/x; if(l>r) return 0;
		b[i]=l; d[i]=r-l;
	}
//	printf("%I64d\n",v);
//	fr(i,1,n) printf("%d%c",(int)b[i],i==n?'\n':' ');
//	fr(i,1,n) printf("%d%c",(int)d[i],i==n?'\n':' ');
	i64 s=y,S=0;
	fr(i,1,n){ s-=b[i]; S+=d[i]; }
//	printf(" %I64d %I64d\n",s,S);
	if(s<0||s>S) return 0;
	fr(i,1,n)
	{
		i64 k=std::min(d[i],s);
		s-=k; b[i]+=k;
	}
	return 1;
}
int main()
{
	n=read(); x=read(); y=read();
	fr(i,1,n) a[i]=read();
	l=0; r=x+y;
	while(l<r)
	{
		i64 mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	check(l);
//	printf("%I64d\n",l);
	fr(i,1,n) printf("%d%c",(int)b[i],i==n?'\n':' ');
	return 0;
}