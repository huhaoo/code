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
const int N=300010,mod=998244353;
i64 n,x,a[N];
i64 query(i64 l,i64 r)
{
	return std::upper_bound(a+1,a+n+1,r)-std::lower_bound(a+1,a+n+1,l);
}
i64 solve(int l,int r)
{
	i64 ans=0;
	fr(i,l,r)
	{
		i64 v=0;
		fd(j,60,0) if(x>=(1ll<<j))
		{
			i64 op=(a[i]>>j)&1;
			if((x>>j)&1)
			{
				v^=(op^1)<<j;
			}
			else
			{
//				printf("%I64d %d  %I64d %I64d\n",a[i],j,(v^((op^1)<<j)),(v^((op^1)<<j))+(1ll<<j)-1);
				ans+=query((v^((op^1)<<j)),(v^((op^1)<<j))+(1ll<<j)-1);
				v^=op<<j;
			}
		}
		else v^=a[i]&(1ll<<j);
	}
//	printf("%I64d\n",ans);
	return (ans/2+r-l+2)%mod;
}
int main()
{
	n=read(); x=read()-1;
	if(x==-1)
	{
		i64 ans=1;
		fr(i,1,n) ans=(ans*2)%mod;
		printf("%d\n",int(ans-1));
		return 0;
	}
	i64 X=1; while(X<=x) X<<=1;
	fr(i,1,n) a[i]=read();
	std::sort(a+1,a+n+1);
	int i=1; i64 ans=1;
	while(i<=n)
	{
		int j=i;
		while(j<n&&(a[j+1]^a[i])<X) j++;
		ans=ans*solve(i,j)%mod;
		i=j+1;
	}
	printf("%d\n",int((ans+mod-1)%mod));
	return 0;
}