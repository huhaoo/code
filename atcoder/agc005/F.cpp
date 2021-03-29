/***************************************************************
	File name: F.cpp
	Author: huhao
	Create time: Fri 29 Jan 2021 02:36:23 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
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
		r=r*10+c-48;
		c=getchar();
	}
	return r*t;
}
const int N=1<<20|10,mod=924844033;
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1; a%=p;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
i64 inv(i64 a){ return power(a,mod-2,mod); }
inline i64 Mod(i64 a){ return a>=mod?a-mod:a; }
inline void Add(i64 &a,i64 b){ a=Mod(a+b); }
const int g=5;
int r[N],l;
i64 w[N];
void init(int n)
{
	l=0;
	while((1<<l)<n) l++;
	fr(i,0,(1<<l)-1) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	w[0]=1; w[1]=power(g,(mod-1)>>l,mod);
	fr(i,2,1<<l) w[i]=w[i-1]*w[1]%mod;
}
void NTT(i64 *a,int opt)
{
	fr(i,0,(1<<l)-1) if(i<r[i]) std::swap(a[i],a[r[i]]);
	fr(i,0,l-1) for(int j=0;j<(1<<l);j+=(1<<(i+1))) fr(k,0,(1<<i)-1)
	{
		i64 x=a[j+k],y=a[j+k+(1<<i)]*w[opt==1?(k<<(l-i-1)):(1<<l)-(k<<(l-i-1))]%mod;
		a[j+k]=Mod(x+y); a[j+k+(1<<i)]=Mod(x-y+mod);
	}
	i64 I=inv(1<<l);
	if(opt==-1) fr(i,0,(1<<l)-1) a[i]=a[i]*I%mod;
}
#include<vector>
int n;
i64 a[N],b[N],f[N],F[N],s[N];
std::vector<int> e[N];
void dfs(int u,int f)
{
	s[u]=1;
	for(auto v:e[u]) if(v!=f){ dfs(v,u); s[u]+=s[v]; a[s[v]]--; }
	a[n]++; a[n-s[u]]--;
}
int main()
{
	n=read();
	fr(i,1,n-1){ int u=read(),v=read(); e[u].push_back(v); e[v].push_back(u); }
	dfs(1,0); f[0]=1; fr(i,1,n) f[i]=f[i-1]*i%mod;
	F[n]=inv(f[n]); fd(i,n,1) F[i-1]=F[i]*i%mod;
	fr(i,0,n) a[i]=a[i]*f[i]%mod;
	fr(i,0,n) b[i]=F[n-i];
	init(n<<2); NTT(a,1); NTT(b,1);
	fr(i,0,(1<<l)-1) a[i]=a[i]*b[i]%mod;
	NTT(a,-1);
	fr(i,1,n) printf("%lld\n",(a[i+n]*F[i]%mod+mod)%mod);
	return 0;
}
