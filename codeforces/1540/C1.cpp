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
const int N=120,mod=1000000007;
i64 power(i64 a,i64 b,i64 p=mod)
{
	i64 r=1; a%=p;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
i64 inv(i64 a){ return power(a,mod-2); }
i64 n,q,C[N],c[N],b[N],s[N];
i64 f[N][N*N],p[N][N*N];
i64 a[N*N*N],m,ans[N*N*N];
int main()
{
//	(sizeof(a)*4/1024./1024.);
	n=read();
	fr(i,1,n) C[i]=C[i-1]+(c[i]=read());
	fr(i,2,n) b[i]=read()+b[i-1];
	fr(i,2,n) s[i]=s[i-1]-b[i];
	q=read();
	fr(i,1,n) fr(j,0,C[i]) // j+s[i]<xi x>=(j+s[i])/i+1
		p[i][j]=(j+s[i]+i*100000)/i-100000+1;
	fr(i,1,n) fr(j,0,C[i]) a[++m]=p[i][j];
	a[++m]=-100001; std::sort(a+1,a+m+1); m=std::unique(a+1,a+m+1)-a-1;
//	fr(i,1,n) fr(j,1,C[i]) printf("%I64d%c",p[i][j],j==C[i]?'\n':' ');
	fr(t,1,m)
	{
		f[0][0]=1;
		fr(i,1,n) fr(j,0,C[i]) f[i][j]=0;
		fr(i,1,n)
		{
			fr(j,0,C[i-1])
			{
				f[i][j]+=f[i-1][j];
				f[i][j+c[i]+1]-=f[i-1][j];
			}
			fr(j,1,C[i]) f[i][j]+=f[i][j-1];
			fr(j,0,C[i]) if(a[t]>=p[i][j]) f[i][j]=0;
			else f[i][j]%=mod;
		}
//		fr(i,1,n) fr(j,1,C[i]) printf("%I64d%c",f[i][j],j==C[i]?'\n':' ');
		fr(i,0,C[n]) ans[t]+=f[n][i];
		ans[t]%=mod;
//		printf("%I64d %I64d\n",a[t],ans[t]);
	}
	while(q--)
	{
		int x=std::upper_bound(a+1,a+m+1,read())-a-1; //if(x==0) x=1;
		printf("%I64d\n",ans[x]);
	}
	return 0;
}