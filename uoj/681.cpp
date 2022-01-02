#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
i64 read()
{
	i64 r=0,t=1,c=getchar();
	while(c<'0'||c>'9'){ t=c=='-'?-1:1; c=getchar(); }
	while(c>='0'&&c<='9'){ r=(r<<3)+(r<<1)+(c^48); c=getchar(); }
	return r*t;
}
const int N=250010,L=61;
int n,q,t;
i64 a[N],b[L+10][N];
i64 ans;
int main()
{
	n=read(); q=read(); t=read();
	fr(i,1,n)
	{
		a[i]=read();
		fr(j,0,L) b[j][i]=a[i]&((1ll<<(j+1))-1);
	}
	fr(i,0,L) std::sort(b[i]+1,b[i]+n+1);
	while(q--)
	{
		i64 v=read()^(t*(ans>>20)); ans=0;
		fr(j,0,L)
		{
			i64 V=v&((1ll<<(j+1))-1),op=(V>=(1ll<<j));
			if(op) V-=1ll<<j;
			i64 x=(std::lower_bound(b[j]+1,b[j]+n+1,(1ll<<(j+1))-V)-std::lower_bound(b[j]+1,b[j]+n+1,(1ll<<j)-V))&1;
			if(op&&(n&1)) x^=1;
			if(x) ans|=1ll<<j;
		}
		printf("%lld\n",ans);
	}
	return 0;
}