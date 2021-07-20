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
const int N=1<<19|10,mod=998244353,g=3;
i64 power(i64 a,i64 b,i64 p=mod)
{
	i64 r=1; a%=p;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
i64 inv(i64 a){ return power(a,mod-2); }
namespace _hash
{
	const i64 Sed[]={123,456,17,10007},Mod[]={998244353,1000000007,19491001,1000000009};
	struct Hash
	{
		i64 h[4];
		Hash(){ h[0]=h[1]=h[2]=h[3]=0; }
	};
	Hash operator+(Hash a,i64 v){ fr(i,0,3) a.h[i]=(a.h[i]+power(Sed[i],v,Mod[i]))%Mod[i]; return a; }
	bool operator<(Hash a,Hash b){ fr(i,0,3) if(a.h[i]!=b.h[i]) return a.h[i]<b.h[i]; return 0; }
}
using _hash::Hash;
i64 Mod(i64 a){ return a>=mod?a-mod:a; }
namespace NTT
{
	i64 l,r[N],w[N];
	void init(int n)
	{
		l=0; while((1<<l)<n) l++;
		fr(i,0,(1<<l)-1) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
		w[0]=1; w[1]=power(g,(mod-1)>>l,mod);
		fr(i,2,(1<<l)) w[i]=w[i-1]*w[1]%mod;
	}
	void ntt(i64 *a,int op)
	{
		fr(i,0,(1<<l)-1) if(i<r[i]) std::swap(a[i],a[r[i]]);
		fr(i,0,l-1)
		{
			static i64 W[N];
			fr(k,0,(1<<i)-1) W[k]=w[op==1?(k<<(l-i-1)):(1<<l)-(k<<(l-i-1))];
			for(int j=0;j<(1<<l);j+=(1<<(i+1))) fr(k,0,(1<<i)-1)
			{
				i64 x=a[j+k],y=a[j+k+(1<<i)]*W[k]%mod;
				a[j+k]=Mod(x+y); a[j+k+(1<<i)]=Mod(x-y+mod);
			}
		}
		if(op==-1){ i64 I=inv(1<<l); fr(i,0,(1<<l)-1) a[i]=a[i]*I%mod; }
	}
}
#define poly std::vector<i64>
poly operator*(poly a,poly b)
{
	int n=a.size(),m=b.size(); using namespace NTT;
	if(n+m-1<=0)
	{
		poly c(n+m-1);
		fr(i,0,n-1) fr(j,0,m-1) c[i+j]=(c[i+j]+a[i]*b[j])%mod;
		return c;
	}
	init(n+m-1); static i64 A[N],B[N];
	fr(i,0,(1<<l)-1) A[i]=B[i]=0;
	fr(i,0,n-1) A[i]=a[i]; fr(i,0,m-1) B[i]=b[i];
//	fr(i,0,n-1) printf("%lld%c",a[i],i==end_i?'\n':' ');
//	fr(i,0,m-1) printf("%lld%c",b[i],i==end_i?'\n':' ');
	ntt(A,1); ntt(B,1);
	fr(i,0,(1<<l)-1) A[i]=A[i]*B[i]%mod;
	ntt(A,-1); a.clear(); fr(i,0,n+m-2) a.push_back(A[i]);
//	fr(i,0,n+m-2) printf("%lld%c",a[i],i==end_i?'\n':' ');; putchar(10);
	return a;
}
poly operator+(poly a,poly b){ a.resize(std::max(a.size(),b.size())); fr(i,0,b.size()-1) a[i]=Mod(a[i]+b[i]); return a; }
int n,m,cnt[N];
std::vector<int> e[N];
int w[N],r,R,rf;
void dfs(int u,int f)
{
	int mw=0; w[u]=1;
	for(auto v:e[u]) if(v!=f){ dfs(v,u); w[u]+=w[v]; mw=std::max(mw,w[v]); }
	mw=std::max(mw,n-w[u]);
	if(mw<R){ R=mw; r=u; rf=f; }
}
std::map<Hash,int> t; int h[N]; int s[N];
void Dfs(int u,int f)
{
	for(auto i=e[u].begin();i!=e[u].end();i++) if(*i==f){ e[u].erase(i); break; }
	Hash H; w[u]=1;
	for(auto v:e[u]){ Dfs(v,u); H=H+h[v]; w[u]+=w[v]; if(w[v]>w[s[u]]) s[u]=v; }
	if(w[s[u]]+w[s[u]]<w[u]) s[u]=0;
	for(auto i=e[u].begin();i!=e[u].end();i++) if(*i==s[u]){ e[u].erase(i); break; }
	if(!t.count(H)) t[H]=++m;
	h[u]=t[H];
//	printf("%d %d  %d\n",u,s[u],h[u]);
}
struct Math
{
	i64 f[N],F[N];
	Math(i64 n)
	{
		f[0]=1; fr(i,1,n) f[i]=f[i-1]*i%mod;
		F[n]=inv(f[n]); fd(i,n,1) F[i-1]=F[i]*i%mod;
	}
} C(N-10);
poly f[N],F[N];
std::pair<poly,poly> calc(poly f,int l,int r)
{
	if(l==r) return {poly{C.F[l]},f};
	int mid=(l+r)>>1; auto x=calc(f,l,mid),y=calc(f,mid+1,r);
	return {x.first+x.second*y.first,x.second*y.second};
}
poly calc(int l,int r)
{
	if(l==r) return F[l];
	int mid=(l+r)>>1; return calc(l,mid)*calc(mid+1,r);
}
void solve(int u)
{
	for(int i=u;i;i=s[i]) for(auto j:e[i]) solve(j);
	int c=0;
	for(int i=u;i;i=s[i])
	{
		c++; F[c]={1,1};
		for(auto j:e[i]) cnt[h[j]]++;
		for(auto j:e[i]) if(cnt[h[j]])
		{
			f[j][0]--; F[++c]=calc(f[j],0,cnt[h[j]]).first;
			cnt[h[j]]=0;
		}
	}
	f[u]=calc(1,c);
}
int main()
{
	n=read();
	fr(i,1,n-1){ int u=read(),v=read(); e[u].push_back(v); e[v].push_back(u); }
	R=n; dfs(1,0);
	poly ans;
	if(w[r]==n/2)
	{
		Dfs(r,rf); Dfs(rf,r);
		if(h[r]==h[rf]){ solve(r); f[r][0]--; ans=calc(f[r],0,2).first; }
		else{ solve(r); solve(rf); ans=f[r]*f[rf]; }
	}
	else{ Dfs(r,0); solve(r); ans=f[r]; }
	assert(ans.size()==n+1);
	fr(i,1,n) printf("%lld%c",ans[i]*C.f[i]%mod,i==n?'\n':' ');
	return 0;
}