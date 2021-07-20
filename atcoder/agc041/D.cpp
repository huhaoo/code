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
const int N=5010;
int mod,n;
int C[N][N],f2[N][N*2],ans;
inline i64 Mod(i64 a){ return a>=mod?a-mod:a; }
int main()
{
	n=read(); mod=read();
	if(n==2){ printf("3\n"); return 0; }
	fr(i,0,n) C[i][0]=1;
	fr(i,1,n) fr(j,1,n) C[i][j]=Mod(C[i-1][j]+(i<=j?C[i][j-i]:0));
	fr(i,1,n)
	{
		static int f[N],g[N];
		fr(j,0,i) f[j]=g[j]=0;
		fr(j,0,i) f[i-j]=C[n/2][j];
		if(i==n) g[0]=1;
		else if(i==n-1) fr(j,0,(n-1)/2) g[j]=1;
		else
		{
			assert(((n-1)/2+1)*2>i);
			fr(j,(n-1)/2+1,i) g[j]=mod-C[n-i-1][j-(n-1)/2-1];
			fr(j,1,i) g[j]=Mod(g[j]+g[j-1]);
			fr(j,0,i) g[j]=Mod(g[j]+C[n-i][j]);
		}
		fr(j,1,i) g[j]=Mod(g[j]+g[j-1]);
		fr(j,1,i) ans=(ans+(i64)f[j]*g[j-1])%mod;
	}
	printf("%d\n",ans);
	return 0;
}