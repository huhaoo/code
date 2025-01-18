#include<bits/stdc++.h>
#include<thread>
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
const int mod=433494437;
i64 ans[100]; i64 n;
i64 solve(i64 i,i64 j,i64 k,i64 l)
{
	if(std::abs(k)<std::abs(l)) return 0;
	i64 s=(i*i+j*j+k*k+l*l); if(s%8!=0) return 0; else s/=8;
//	printf("%d %d %d %d  %d\n",i,j,k,l,s);
	if((s+i)&3) return 0;
	i64 a=(s+i)/4,b=(s+j)/4,c=(s+k)/4,d=(s+l)/4;
	if(1<=a&&a<=n&&1<=b&&b<=n&&1<=c&&c<=n&&1<=d&&d<=n)
	{
//		printf("%lld %lld %lld %lld\n",a,b,c,d);
		return (a+b+c+d)%mod;
	}
	return 0;
}
void Solve(int id,int al)
{
//	printf("%d start\n",id);
	for(i64 i=id,end_i=sqrt(n<<5)+1;i<=end_i;i+=al)
	{
		for(i64 j=(-i&3);j<=std::abs(i)&&i*i+j*j<=(n<<5);j+=4)
			for(i64 k=(-i&3);k<=j&&i*i+j*j+k*k<=(n<<5);k+=4)
			{
				ans[id]+=solve(i,-j,-k,j+k-i);
				if(i!=j) ans[id]+=solve(-i,j,k,i-j-k);
				ans[id]%=mod;
			}
	}
//	printf("%d end\n",id);
}
int main()
{
	n=100000000; int cnt=1;
	std::thread t[100];
	fr(i,1,cnt) t[i]=std::thread(Solve,i,cnt);
	fr(i,1,cnt) t[i].join();
	fr(i,1,cnt) ans[0]+=ans[i];
	printf("%lld\n",ans[0]%mod);
//	printf("%.10lf\n",clock()*1./CLOCKS_PER_SEC);
	return 0;
}