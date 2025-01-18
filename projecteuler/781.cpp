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
const int N=50010,mod=1000000007;
int n;
int f[N][2],F[N][2];
void Add(int &a,int b){ a+=b; if(a>=mod) a-=mod; }
int main()
{
	n=read(); f[0][1]=1;
	fr(t,1,n)
	{
		fr(i,0,t) fr(j,0,1){ F[i][j]=f[i][j]; f[i][j]=0; }
		fr(i,0,t)
		{
			Add(f[i][1],F[i+1][0]);
			Add(f[i][1],(i64)F[i+1][1]*(i+1)%mod);
			if(i) Add(f[i][1],F[i-1][1]);
			Add(f[i][0],(i64)F[i+1][1]*(i+1)%mod);
			if(i) Add(f[i][0],F[i-1][1]);
		}
//		if(t%1000==0){ printf("%d %.10lf\n",t,clock()*1./CLOCKS_PER_SEC); fflush(stdout); }
//		fr(j,0,1) fr(i,0,n) printf("%d%c",f[i][j],i==n?'\n':' ');
	}
	printf("%d\n",f[0][0]);
	return 0;
}