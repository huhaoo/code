/***************************************************************
	File name: H.cpp
	Author: huhao
	Create time: Thu 03 Dec 2020 09:37:27 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#include<random>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
#define i128 __int128

#define io
#define Auto

i64 bit(i64 a)
{
	i64 ans=0;
	if(a>=(1ll<<32)){ ans+=32; a>>=32; }
	if(a>=(1ll<<16)){ ans+=16; a>>=16; }
	if(a>=(1ll<<8)){ ans+=8; a>>=8; }
	if(a>=(1ll<<4)){ ans+=4; a>>=4; }
	if(a>=(1ll<<2)){ ans+=2; a>>=2; }
	if(a>=(1ll<<1)){ ans+=1; a>>=1; }
	if(a) ans++;
	return ans;
}
i64 bit(i64 a,i64 b){ return (bit(a)+1)*(bit(b)+1); }
i64 pow(i64 a,i64 d,i64 n,int op=0)
{
	i64 r=1,ans=0;
	for(int i=0;i<60;i++)
	{
		if((d&(1ll<<i))){ ans+=bit(r,a); r=(i128)r*a%n; }
		ans+=bit(a,a); a=(i128)a*a%n;
	}
	return op?ans:r;
}
i64 pow(i64 a,i64 n)
{
	i64 ans=0;
	for(int i=0;i<60;i++){ ans+=(bit(a)+1)*(bit(a)+1); a=(i128)a*a%n; }
	return ans;
}
i64 query(i64 );

// main function - begin
#include<bitset>
#include<vector>
std::bitset<150000> f[5][61][81];
i64 a[10000];
i64 c[10000],C;
void getc(i64 n)
{
	for(int i=2;i*i<=n;i++) if(n%i==0)
	{
		c[++C]=i; while(n%i==0) n/=i;
	}
	if(n>1) c[++C]=n;
}
i64 ord(i64 g,i64 m,i64 n)
{
	fr(i,1,C) while(m%c[i]==0&&pow(g,m/c[i],n)==1) m/=c[i];
	return m;
}
std::vector<std::pair<std::vector<int>,int> > A;
i64 solve(i64 n)
{
	i64 c=query(1)/4-60,l=c*62*62,t=5;
	i64 p=0,q=0,m,w=0,g=1;
	for(i64 i=1<<29|1;i<=n;i+=2) if(n%i==0){ p=i; q=n/i; break; }
	getc(p-1); getc(q-1); m=(p-1)*(q-1);
	fd(i,80,6) fr(j,2,100) if(ord(j,m,n)%i==0){ w=i; g=j; goto label1; }
label1:;
	g=power(g,m/w,n); a[0]=1;
	fr(i,1,w) a[i]=(i128)a[i-1]*g%n;
	fr(i,1,t)
	{
		a[i-1][0][0][0]=1;
		fr(j,0,59) fr(k,0,w-1)
		{
			int d=(i*(1ll<<j))%w;
			a[i-1][j+1][(k+d)%w]|=a[i-1][j][k]<<bit(a[d],a[w]);
		}
		i64 v=query(a[i])
	}
	return w;
}

// main function - end

#ifdef io
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
#ifdef Auto
i64 n,m,d;
bool check(int n)
{
	for(int i=2;i*i<=n;i++) if(n%i==0) return 0;
	return 1;
}
#endif
i64 query(i64 x)
{
#ifdef Auto
//	printf("! %lld => %lld\n",x,pow(x,d,n,1));
	return pow(x,d,n,1);
#else
	printf("! %lld\n",x); fflush(stdout); return read();
#endif
}
int main()
{
#ifdef Auto
	freopen("/dev/urandom","r",stdin);
	unsigned int sed=0;
	fr(i,1,100) sed=sed*sed+sed+getchar();
	std::mt19937 Rand(sed);
	i64 p=4,q=4;
	while(!check(p)) p=Rand()%(1<<29)+(1<<29);
	while(!check(q)||p==q) q=Rand()%(1<<29)+(1<<29);
	n=q*p; m=(p-1)*(q-1); d=0;
	while(std::__gcd(d,m)!=1) d=(((unsigned i64)Rand()<<32)+Rand())%(m-1)+1;
	printf("Q %lld=%lld*%lld  %lld     =>     %lld\n",n,p,q,d,solve(n));
#else
	printf("! %lld\n",solve(read()));
#endif
	return 0;
}
#endif
