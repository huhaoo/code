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
int cnt=0;
i64 m,ans,n;
i64 d(i64 n,i64 m)
{
	i64 ans=0;
	while(m){ ans+=n/m; i64 t=n%m; n=m; m=t; }
	return ans;
	// return !m?0:n/m+d(m,n%m);
}
void D(i64 x)
{
	cnt++;
	i64 y=d(n,x); if(y<ans||(y==ans&&x<m)){ printf("%lld %lld\n",x,y); fflush(stdout); ans=y; m=x; }
}

// an/b, 0<a<b, n<~10^12
// i64 muln(i64 a,i64 b)
// {
// 	return a*n/b;
// }

// an+bm>=cn+dm
void update(i64 a,i64 b,i64 c,i64 d,i64 &l,i64 &r,int bor)
{
	a-=c; b-=d;
	if(!b){ if(a<0) l=r+1; return ; }
	// an+bm>=bor
	if(b>0)
	{
		// m>=(bor-an)/b
		l=std::max(l,(bor-a*n+b-1)/b);
		// if(a>=0) ;
		// else if(-a>=b) l=n;
		// else l=std::max(l,(bor-a*n)/b);
	}
	else
	{
		//m<=(-bor+an)/-b
		r=std::min(r,(-bor+a*n)/-b);
		// if(a<=0) r=0;
		// else if(a>=-b) ;
		// else r=std::min(r,(a*n-bor)/-b);
	}
}

double bs=(1+sqrt(5))/2;
double l2[1<<20|10];

inline int log2i(i64 x)
{
	return int((x<=1?0:x>>20?l2[1<<20]+l2[x>>20]:l2[x])+0.999);
}

// an+bm, cn+dm
void solve(i64 a,i64 b,i64 c,i64 d,i64 l,i64 r,i64 w)
{
	// cnt++;
	if(w+log2i(std::min(a*n+b*l,a*n+b*r))>ans) return ;
	if(r-l<10){ for(i64 i=l;i<=r;i++) D(i); return ; }
	if(std::abs(a)>1e6||std::abs(b)>1e6||std::abs(c)>1e6||std::abs(d)>1e6||std::min(c*n+d*l,c*n+d*r)<=0)
	{
		printf("%lld %lld %lld %lld %lld %lld  %lld  %lld %lld\n",a,b,c,d,l,r,w,c*n+d*l,c*n+d*r);
		exit(0);
	}
	fr(i,1,ans)
	{
		if(w+i+log2i(std::min(c*n+d*l,c*n+d*r))>ans) break;
		i64 L=l,R=r;
		update(a,b,c*i,d*i,L,R,0); update(c*(i+1),d*(i+1),a,b,L,R,1);
		// printf("%lld %lld %lld %lld %lld %lld %lld  %d\n",a,b,c,d,L,R,w,i);
		solve(c,d,a-c*i,b-d*i,L,R,w+i);
	}
}
int main()
{
	for(int i=2;i<=(1<<20);i++) l2[i]=log(i)/log(bs);
	// n=998244353;
	// n=8191;
	n=1e12+39;
	printf("%lld\n",n);
	ans=100;
	solve(1,0,0,1,1,n-1,0);
	printf("%lld %lld  %d\n",ans,m,cnt);
	return 0;
}