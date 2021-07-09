#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
const int N=110,mod=998244353;
int n;
i64 f[N],ans;
int g[N][N*N*2],G[N][N*N*2];
int w[N];
void Add(int &a,int b){ a+=b; if(a>=mod) a-=mod; }
int main()
{
	n=read(); f[0]=1;
	fr(i,1,n) f[i]=f[i-1]*i%mod;
	fr(i,1,n) w[i]=read();
	g[0][n*n]=1;
	fr(i,1,n)
	{
		fr(j,0,n) fr(k,0,n*n*2){ G[j][k]=g[j][k]; g[j][k]=0; }
		fr(j,0,n) fr(k,0,n*n*2) if(G[j][k])
		{
			Add(g[j+1][k+w[i]],G[j][k]);
			Add(g[j][k-w[i]],G[j][k]);
		}
	}
	fr(i,0,n) ans+=f[i]*f[n-i]%mod*g[i][n*n]%mod;
	printf("%d\n",int(ans%mod));
	return 0;
}