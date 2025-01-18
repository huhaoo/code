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
int n,k; double ans;
const int N=10000010;
void ran()
{
	std::mt19937 Rand(12345);
	double s=0; int T=1000000;
	fr(t,1,T)
	{
		static int vis[N]; vis[0]=1; fr(i,1,n*k){ vis[i]=0; vis[i+n*k]=1; }
		fr(i,1,n)
		{
			int cnt=0;
			fr(j,1,k) vis[n*k+(i-1)*k+j]=0;
			fr(j,1,2*k)
			{
				int u=0; while(vis[u]) u=Rand()%(2*n*k)+1;
				cnt+=(u>n*k); vis[u]=1;
			}
			s+=cnt*cnt;
		}
	}
	printf("%.10lf\n",s/T);
}
#define V(x) (n*k-(x-1)*k+k)
int main()
{
	n=read(); k=read(); if(k==1){ printf("%d\n",n); return 0; }
	static double f[N],g[N];
	fd(i,n,1) f[i]=f[i+1]+(double)V(i+1)*(V(i+1)-1);
	fd(i,n,1) g[i]=g[i+1]+f[i]/(V(i)-1)/(V(i+1)-1);
//	ran();
	if(0) fr(i,1,n) fr(j,i,n) fr(t,j,n)
	{
		ans+=(double)(i==j?k*(k-1):k*k*2)*
		     2*k*(2*k-1)/(V(t))/(V(t)-1)*
			 V(j)*V(j+1)/V(i)/V(i+1)*
			 V(t)*(V(t)-1)*V(t+1)*(V(t+1)-1)/V(j)/(V(j)-1)/V(j+1)/(V(j+1)-1);
	}
	if(0) fr(i,1,n) fr(j,i,n)
	{
		ans+=(double)(i==j?k*(k-1):k*k*2)*
		     2*k*(2*k-1)/V(i)/V(i+1)*f[j]
			 /(V(j)-1)/(V(j+1)-1);
	}
	if(1)
	{
		fr(i,1,n)
		{
			ans+=(double)k*(k-1)*2*k*(2*k-1)/V(i)/V(i+1)*f[i]/(V(i)-1)/(V(i+1)-1);
			ans+=(double)k*k*2*2*k*(2*k-1)/V(i)/V(i+1)*g[i+1];
		}
	}
	printf("%.10lf\n",ans+n*k);
	return 0;
}