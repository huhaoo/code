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
const int N=1<<27|10,mod=998244353;
int n,m,f[N];
void Add(int &a,int b){ a+=b; if(a>=mod) a-=mod; }
int main()
{
	n=read(); m=read(); int l=0; while((1<<l)<=m) l++;
	fr(i,0,m) f[i]=1;
	fr(t,2,n)
	{
		fr(i,0,l-1) for(int j=0;j<(1<<l);j+=(1<<(i+1))) fr(k,0,(1<<i)-1) Add(f[j+k],f[j+k+(1<<i)]);
		f[0]=0; fr(i,1,(1<<l)-1) if(!(__builtin_popcount(i)&1)) f[i]=mod-f[i];
		fr(i,0,l-1) for(int j=0;j<(1<<l);j+=(1<<(i+1))) fr(k,0,(1<<i)-1) Add(f[j+k+(1<<i)],f[j+k]);
		fr(i,m+1,(1<<l)-1) f[i]=0;
//		fprintf(stderr,"%d  %d\n",t,clock()); fflush(stderr);
//		fr(i,0,(1<<l)-1) printf("%d%c",f[i]%mod,i==end_i?'\n':' ');
	}
	int ans=0;
	fr(i,0,m) Add(ans,f[i]);
	printf("%d\n",ans%mod);
//	printf("%.10lf\n",clock()*1./CLOCKS_PER_SEC);
	return 0;
}