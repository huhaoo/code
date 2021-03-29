/***************************************************************
	File name: 172.cpp
	Author: huhao
	Create time: Thu 11 Jun 2020 01:37:57 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
i64 read()
{
	i64 r=0,t=1,c=getchar();
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
const int N=1000010;
//             123456789012345678
const i64 inf=2000000000000000000;
i64 T,n,q,m,a[N],d[N],l[N];
i64 f[N],g[N],ans;
char s[N];
void init()
{
	static i64 f[N],g[N]; i64 c=0; m=0;
	fr(i,0,n) f[i]=0;
	fr(i,2,n)
	{
		f[i]=f[i-1];
		while(f[i]&&s[f[i]+1]!=s[i]) f[i]=f[f[i]];
		if(s[f[i]+1]==s[i]) f[i]++;
	}
	for(i64 i=f[n];i;i=f[i]) g[++c]=n-i;
	g[++c]=n;
//	fr(i,1,c) printf("%d%c",g[i],i==c?'\n':' ');
	for(i64 i=1,j;i<=c;i=j+1)
	{
		if(i==c){ m++; a[m]=g[i]; d[m]=0; l[m]=1; j=i; break; }
		j=i+1;
		while(j<n&&g[j+1]-g[j]==g[i+1]-g[i]) j++;
		m++; a[m]=g[i]; d[m]=g[i+1]-g[i]; l[m]=j-i;
	}
}
inline void Min(i64 &a,i64 b){ if(a>b) a=b; }
void dp(i64 *f,i64 p,i64 d,i64 L,i64 t)
{
	if(!l) return ;
	i64 D=d%p;
	static i64 vis[N];
	fr(i,0,p-1) vis[i]=0;
	fr(s,0,p-1) if(!vis[s])
	{
		static i64 a[N],n; a[n=1]=s;
		for(i64 j=(s+d>=p?s+d-p:s+d);j!=s;j=(j+d>=p?j+d-p:j+d)) a[++n]=j;
		fr(i,1,n) vis[a[n+i]=a[i]]=1;
		n+=n;
		static i64 q[N],l,r; q[l=r=1]=1;
		fr(i,2,n)
		{
			if(q[l]+L<i) l++;
			Min(f[a[i]],f[a[q[l]]]+t+d*(i-q[l]));
			while(l<=r&&f[a[q[r]]]>f[a[i]]+d*(i-q[r])) r--;
			q[++r]=i;
		}
	}
}
int main()
{
	T=read();
	while(T--)
	{
		n=read(); q=read(); scanf("%s",s+1); init(); ans=0;
		fr(i,0,a[1]-1) f[i]=inf;
		f[0]=0; dp(f,a[1],d[1],l[1],a[1]);
		fr(i,2,m)
		{
			fr(j,0,a[i-1]-1) g[j]=f[j];
			fr(j,0,a[i]-1) f[j]=inf;
			fr(j,0,a[i-1]-1) Min(f[g[j]%a[i]],g[j]);
			dp(f,a[i],a[i-1],1,0); dp(f,a[i],d[i],l[i],a[i]);
		}
//		fr(i,1,m) printf("%d %d %d\n",a[i],d[i],l[i]);
//		fr(i,0,a[m]-1) printf("%lld%c",f[i],i==end_i?'\n':' ');
		fr(i,0,a[m]-1) ans+=std::max(0ll,(q-n-f[i]+a[m])/a[m]);
		printf("%lld\n",ans);
	}
	return 0;
}
