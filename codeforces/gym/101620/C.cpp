/***************************************************************
	File name: C.cpp
	Author: huhao
	Create time: Mon 09 Nov 2020 04:44:22 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
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
const int N=35,W=1<<15;
i64 f[N][W+10],g[N][W+10];
i64 Solve(i64 n,i64 s,i64 d,i64 c,i64 t)
{
//	printf("> %lld %lld %lld %lld  %lld\n",n,s,d,c,t);
	if(n==1) return t>>1;
	if(d<=W&&s-d<=0&&s+c*d>=(1<<n)) return f[n][d-s]*t+g[n][d-s]+(s+(c-1)*d==(1<<n)-1?t>>1:0);
	i64 w=(1<<(n-1))-1,ans=0;
	if(s+(c-1)*d==w+w+1){ c--; ans=t>>1; }
	if(!c) return ans;
	if(s>w) ans+=Solve(n-1,s-w,d,c,t<<1|1);
	else if(s+(c-1)*d<=w) ans+=Solve(n-1,s,d,c,t<<1);
	else
	{
		int p=(w-s)/d+1;
		ans+=Solve(n-1,s,d,p,t<<1);
		ans+=Solve(n-1,s+p*d-w,d,c-p,t<<1|1);
	}
	return ans;
}
i64 solve(i64 n,i64 s,i64 d,i64 c,i64 t)
{
//	printf("< %lld %lld %lld %lld  %lld\n",n,s,d,c,t);
	if(n==1) return t<<1|1;
	i64 w=(1<<(n-1))-1,ans=0;
	if(s<=w+1&&s+(c-1)*d>=w+1&&(w+1-s)%d==0) ans=t<<1|1;
	if(s+(c-1)*d<=w+1)
	{
		if(s+(c-1)*d==w+1) c--;
		if(c) ans+=Solve(n-1,s,d,c,t<<1);
		return ans;
	}
	if(s>=w+1)
	{
		if(s==w+1){ s+=d; c--; }
		if(c) ans+=solve(n-1,s-w-1,d,c,t<<1|1);
		return ans;
	}
	int p=(w-s)/d+1;
	ans+=Solve(n-1,s,d,p,t<<1); p++;
	if(s+(p-1)*d==w+1) p++;
	ans+=solve(n-1,s+(p-1)*d-w-1,d,c-p+1,t<<1|1);
	return ans;
}
int main()
{
	int n=read(),q=read();
	fr(Q,1,q)
	{
		int s=read(),d=read(),c=read();
		if(d<=W)
		{
			memset(f,0,sizeof(f)); memset(g,0,sizeof(g));
			fr(i,2,n) fr(j,0,d-1)
			{
				int _j=(j+(1<<(i-1))-1)%d;
				f[i][j]=(f[i-1][j]+f[i-1][_j])<<1;
				if((j+(1<<(i-1))-1)%d==0) f[i][j]++;
				if((j+(1<<i)-2)%d==0) f[i][j]++;
				g[i][j]=g[i-1][j]+g[i-1][_j]+f[i-1][_j];
			}
		}
		printf("%lld\n",solve(n,s,d,c,1));
	}
	return 0;
}
