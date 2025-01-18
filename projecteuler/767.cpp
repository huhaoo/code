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
const int N=1<<20|10,mod=1000000007;
i64 n,m,k;
i64 power(i64 a,i64 b,i64 p){ i64 r=1; for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p; return r; }
i64 f[N],F[N];
i64 fn[N],Fn[N];
int main()
{
//	n=16; m=9; k=3;
	n=16; k=20000; m=k*k;
	f[0]=1; fr(i,1,k) f[i]=f[i-1]*i%mod;
	F[k]=power(f[k],mod-2,mod); fd(i,k,1) F[i-1]=F[i]*i%mod;
	fr(i,0,k){ fn[i]=power(f[i],n,mod); Fn[i]=power(F[i],n,mod); }
	i64 ans=0;
	fr(j,0,k)
	{
		i64 S=0;
		fr(l,0,k-j) S+=Fn[l]*Fn[k-j-l]%mod;
		ans=(ans+(j&1?mod-1:1)*power(mod+1-power(2,m/k-1,mod),j,mod)%mod*f[k]%mod*F[j]%mod*F[k-j]%mod*power(2,j,mod)%mod *(S%mod*fn[k-j]%mod))%mod;
	}
	printf("%lld\n",ans);
	return 0;
}