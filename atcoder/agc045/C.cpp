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
const int mod=1000000007,N=10010;
int n,a,b;
int f[N],g[N],h[N];
int ans;
void Add(int &a,int b){ a+=b; if(a>=mod) a-=mod; }
int main()
{
	n=read(); a=read(); b=read(); if(a>b) std::swap(a,b);
	f[1]=1;
	fr(i,2,n+2)
	{
		f[i]=f[i-1];
		fr(j,a,i-1) Add(f[i],f[i-j-1]);
	}
//	fr(i,1,b-1) printf("%d%c",f[i],i==b-1?'\n':' ');
	fr(i,1,b-1) fr(j,1,a-1) Add(g[i+j],f[i]);
//	fr(i,1,n) printf("%d%c",g[i],i==n?'\n':' ');
	fr(i,0,b-1) fr(j,1,a-1) Add(h[i+j],f[i+1]);
//	fr(i,1,n) printf("%d%c",h[i],i==n?'\n':' ');
	fr(i,1,n) fr(j,2,i) Add(h[i],(i64)g[j]*h[i-j]%mod);
//	fr(i,1,n) printf("%d%c",h[i],i==n?'\n':' ');
	ans=1;
	fr(i,1,n) ans=ans*2%mod;
	fr(i,0,b-1) Add(ans,mod-(i64)h[n-i]*f[i+1]%mod);
	printf("%d\n",ans);
	return 0;
}