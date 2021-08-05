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
#ifdef ONLINE_JUDGE
typedef __uint128_t u128;
#else
#define u128 unsigned long long
#endif
inline u128 input() { static char buf[100]; scanf("%s", buf); u128 res = 0;for(int i = 0;buf[i];++i) {		res = res << 4 | (buf[i] <= '9' ? buf[i] - '0' : buf[i] - 'a' + 10);	}	return res;}inline void output(u128 res) { if(res >= 16) output(res / 16);	putchar(res % 16 >= 10 ? 'a' + res % 16 - 10 : '0' + res % 16);}
#define U u128
const int N=1<<20|10;
int n,q;
U a[N];
U t[N]; bool m[N]; int w[N];
U *s[N];
void update(int k)
{
	m[k]=m[k<<1]|m[k<<1|1]; s[k][0]=0;
	fr(i,0,w[k<<1]-1)
	{
		s[k][i+1]=(s[k][i]&s[k<<1][i])|(s[k<<1][i]&s[k<<1|1][i])|(s[k][i]&s[k<<1|1][i]);
		s[k][i]^=s[k<<1][i]^s[k<<1|1][i];
	}
}
inline void tag(int k,U v){ if((t[k]&v)!=t[k]){ t[k]&=v; fr(i,0,w[k]-1) s[k][i]&=v; } }
inline void pushdown(int k){ tag(k<<1,t[k]); tag(k<<1|1,t[k]); t[k]=~(U)0; }
int L,R; U v;
void build(int k,int l,int r)
{
	t[k]=~(U)0;
	if(l==r){ m[k]=(bool)a[l]; w[k]=1; s[k]=new U[2]; s[k][0]=a[l]; s[k][1]=0; return ; }
	int mid=(l+r)>>1; build(k<<1,l,mid); build(k<<1|1,mid+1,r);
	w[k]=w[k<<1]+1; s[k]=new U[w[k]+1]; memset(s[k],0,sizeof(U)*(w[k]+1)); update(k);
}
void modify1(int k,int l,int r)
{
	if(l>R||L>r||!m[k]) return ;
	if(l==r){ a[l]&=t[k]; t[k]=~(U)0; a[l]/=v; m[k]=(bool)a[l]; s[k][0]=a[l]; return ; }
	int mid=(l+r)>>1; pushdown(k);
	modify1(k<<1,l,mid); modify1(k<<1|1,mid+1,r); update(k);
}
void modify2(int k,int l,int r)
{
	if(l>R||L>r) return ;
	if(L<=l&&r<=R){ tag(k,v); return ; }
	int mid=(l+r)>>1; pushdown(k);
	modify2(k<<1,l,mid); modify2(k<<1|1,mid+1,r); update(k);
}
U query(int k,int l,int r)
{
	if(l>R||L>r) return 0;
	if(L<=l&&r<=R){ U ans=0; fd(i,w[k],0) ans=(ans<<1)+s[k][i]; return ans; }
	int mid=(l+r)>>1; pushdown(k);
	return query(k<<1,l,mid)+query(k<<1|1,mid+1,r);
}
int main()
{
	n=read(); q=read();
	fr(i,1,n) a[i]=input();
	build(1,1,n);
	while(q--)
	{
		int op=read(); L=read(); R=read();
		if(op!=3) v=input();
		if(op==1){ if(v>1) modify1(1,1,n); }
		else if(op==2) modify2(1,1,n);
		else{ output(query(1,1,n)); putchar(10); }
	}
	return 0;
}