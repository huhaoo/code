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
const int N=10000010,mod=1000000007;
i64 power(i64 a,i64 b,i64 p=mod){ i64 r=1; for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p; return r; }
i64 n;
i64 f[N],g[N];
int main()
{
	n=10000000;
	fr(i,1,n) f[i]=power(2,i)-1;
	fr(i,1,n){ i64 I=power(f[i],mod-2); fr(j,2,n/i) f[i*j]=f[i*j]*I%mod; }
//	fr(i,1,10) printf("%I64d%c",f[i],i==10?'\n':' ');
	fr(i,1,n) g[i]=1;
	fr(i,1,n) fr(j,1,n/i) g[i*j]=g[i*j]*(f[i]+1)%mod;
	fr(i,1,n) g[i]--;
//	fr(i,1,10) printf("%I64d%c",g[i],i==10?'\n':' ');
	fr(i,1,n) fr(j,2,n/i) g[i*j]=(g[i*j]-g[i])%mod;
//	fr(i,1,10) printf("%I64d%c",g[i],i==10?'\n':' ');
	i64 ans=1;
	fr(i,1,n) ans=(ans+g[i]+mod)%mod;
	printf("%I64d\n",ans);
	return 0;
}