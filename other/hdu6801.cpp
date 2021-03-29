/***************************************************************
	File name: hdu6801.cpp
	Author: huhao
	Create time: Mon 03 Aug 2020 12:20:29 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
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
		r=r*10+c-48;
		c=getchar();
	}
	return r*t;
}
#define i64 long long
const int N=1<<21|10,mod=998244353,g=3;
i64 power(i64 a,i64 b,i64 p=mod)
{
	i64 r=1;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
i64 inv(i64 a){ return power(a,mod-2); }
int r[N],l,n,c;
i64 w[N],p,q;
void init(int n)
{
	l=1; while((1<<l)<n) l++;
	fr(i,0,(1<<l)-1) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	w[0]=1; w[1]=power(g,(mod-1)>>l);
	fr(i,2,(1<<l)) w[i]=w[i-1]*w[1]%mod;
}
int Mod(int a){ return a>=mod?a-mod:a; }
void ntt(int *a,int opt)
{
//	return ;
	fr(i,0,(1<<l)-1) if(i<r[i]) std::swap(a[i],a[r[i]]);
	fr(i,0,l-1) for(int j=0;j<(1<<l);j+=(1<<(i+1))) fr(k,0,(1<<i)-1)
	{
		int x=a[j+k],y=a[j+k+(1<<i)]*w[opt==1?(k<<(l-i-1)):(1<<l)-(k<<(l-i-1))]%mod;
		a[j+k]=Mod(x+y); a[j+k+(1<<i)]=Mod(x+mod-y);
	}
	if(opt==-1)
	{
		i64 I=inv(1<<l);
		fr(i,0,(1<<l)-1) a[i]=a[i]*I%mod;
	}
}
i64 sgn(i64 a){ return a&1?mod-1:1; }
struct Choose
{
	i64 f[N],F[N];
	Choose(int n)
	{
		f[0]=1; fr(i,1,n) f[i]=f[i-1]*i%mod;
		F[n]=inv(f[n]); fd(i,n,1) F[i-1]=F[i]*i%mod;
	}
	i64 operator()(int a,int b){ return a>=b&&b>=0?f[a]*F[b]%mod*F[a-b]%mod:0; }
} C(N-10);
int main()
{
	fr(T,1,read())
	{
		n=read(); p=read(); p=p*inv(read())%mod; c=read()-1; q=mod+1-p;
		static int a[N],b[N],f[N],g[N];
		fr(i,0,(1<<l)-1) a[i]=b[i]=f[i]=g[i]=0;
		fr(i,0,n-1)
		{
			a[i]=C(n-c-1,i);
			b[i]=C(c,i)*power(q,mod-1-i)%mod;
		}
		init(n); ntt(a,1); ntt(b,1);
		fr(i,0,(1<<l)-1) a[i]=(i64)a[i]*b[i]%mod;
		ntt(a,-1);
		static i64 Q[N]; Q[0]=1;
		fr(i,1,n) Q[i]=Q[i-1]*q%mod;
		fr(i,0,n-1)
		{
			f[i]=a[i]*inv(mod+1-Q[n-i])%mod*C.f[n-1-i]%mod;
			g[i]=C.F[i]*sgn(i)%mod;
		}
		init(n<<1); ntt(f,1); ntt(g,1);
		fr(i,0,(1<<l)-1) f[i]=(i64)f[i]*g[i]%mod;
		ntt(f,-1);
		fr(i,0,n-1) f[i]=f[i]*p%mod*Q[c]%mod*C.F[n-1-i]%mod;
		fr(i,0,n-1) printf("%d\n",f[i]);
	}
	return 0;
}
