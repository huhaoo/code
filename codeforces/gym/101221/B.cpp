/***************************************************************
	File name: B.cpp
	Author: huhao
	Create time: Mon 09 Nov 2020 02:44:05 PM CST
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
const int N=10010; const i64 inf=1ll<<50;
int n,m; i64 f[N]; double ans;
int a[N],b[N],c;
void solve(i64 *f,i64 a,i64 b,int n)
{
	if(b==0)
	{
		fr(i,1,n) f[i]=std::max(f[i],f[i-1]+a);
		return ;
	}
	static i64 F[N],s[N],t,p[N],l; t=l=1; s[t]=0; p[t]=n;
	fr(i,0,n) F[i]=f[i];
	fr(i,1,n)
	{
		while(t>=l&&p[l]<i) l++;
		while(t>=l)
		{
			int j=s[t];
			i64 P=n+1;
			fd(r,15,0)
			{
				P-=1<<r;
				if(P>=i&&a*(P-j)-b*(P-j)*(P-j-1)/2+F[j]<a*(P-i)-b*(P-i)*(P-i-1)/2+F[i]) ;
				else P+=1<<r;
			}
//			i64 P=(-(2*F[i]-2*a*i-b*i*i)+(2*F[j]-2*a*j-b*j*j)-1)/(b*(i-j))+1;
//			printf(" %d %d   %d=%lld/%d\n",i,j,P,(-(2*F[i]-2*a*i-b*i*i)+(F[j]-2*a*j-b*j*j)-1),(b*(i-j)));
			if(P<=(t==1?i:p[t-1]+1)) t--;
			else{ p[t]=P-1; if(P<=n){ t++; s[t]=i; p[t]=n; } break; }
		}
//		printf("%d %d  %d\n",i,t,s[t]);
		if(t<l){ t++; s[t]=i; p[t]=n; }
		if(t>=l) f[i]=std::max(f[i],a*(i-s[l])-b*(i-s[l])*(i-s[l]-1)/2+F[s[l]]);
	}
	return ;
	fr(i,0,n) printf("%lld%c",F[i],i==n?'\n':' ');
	fr(i,0,n) printf("%lld%c",f[i],i==n?'\n':' ');
	putchar(10);
}
int main()
{
	n=read(); m=read();
	fr(i,1,m) f[i]=-inf;
	ans=-inf;
	fr(q,1,n)
	{
		char op=0; while(op!='C'&&op!='D') op=getchar();
		if(op=='C'){ c++; a[c]=read(); b[c]=read(); }
		else
		{
			int c=read(),a=read(),b=read();
			fr(t,0,c-1)
			{
				static i64 g[N];
				fr(i,0,(m-t)/c) g[i]=f[i*c+t];
				solve(g,a,b,(m-t)/c);
				fr(i,0,(m-t)/c) f[i*c+t]=g[i];
			}
		}
	}
//	fr(i,0,m) printf("%lld%c",f[i],i==m?'\n':' ');
	if(c) fr(t,0,m)
	{
		double l=-1e9,r=1e9;
		fr(i,1,c) if(b[i]==0) l=std::max(l,(double)a[i]);
		while(r-l>1e-9)
		{
			double mid=(l+r)/2;
			double s=0;
			fr(i,1,c) if(b[i]&&mid<a[i]) s+=(a[i]-mid)/b[i];
			if(t<s) l=mid;
			else r=mid;
		}
//		printf("%d  %.10lf\n",t,l);
		double s=0,S=t;
		fr(i,1,c) if(b[i]&&l<a[i]){ s+=(a[i]+l)*(a[i]-l)/b[i]/2; S-=(a[i]-l)/b[i]; }
		ans=std::max(ans,s+f[m-t]+S*l);
	}
	else ans=f[m];
	if(ans<-inf/2) printf("impossible\n");
	else printf("%.10lf\n",ans);
	return 0;
}
