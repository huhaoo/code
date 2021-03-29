/**************************************************************
	File name: 1081.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/3/2018, 9:47:31 AM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(long long i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(long long i=(a),_end_=(b);i>=_end_;i--)
long long read()
{
	long long r=0,t=1,c=getchar();
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
#define N 100010
#define B 20
long long n,h[N],r[N],pre[N],nex[N],p[N],c,a[N],b[N],d[N][B+10],da[N][B+10],db[N][B+10],f[N][B+10],l,x,y,z,ans;
long long cmp1(long long a,long long b)
{
	return h[a]<h[b];
}
long long dis(long long a,long long b){return abs(h[a]-h[b]);}
long long cmp2(long long a,long long b)
{
	return a*b==0?b==0:dis(a,c)==dis(b,c)?h[a]<h[b]:dis(a,c)<dis(b,c);
}
int main()
{
	n=read();
	fr(i,1,n)h[i]=read(),r[i]=i;
	sort(r+1,r+n+1,cmp1);
	fr(i,1,n)p[r[i]]=i;
	fr(i,2,n){pre[i]=i-1;nex[i-1]=i;}
	fr(i,1,n)
	{
		long long k=p[i],d[4]={r[pre[pre[k]]],r[pre[k]],r[nex[k]],r[nex[nex[k]]]};
		c=i;sort(d,d+4,cmp2);
		a[i]=d[1];b[i]=d[0];
		k=nex[k];pre[k]=pre[pre[k]];nex[pre[k]]=k;
//		fr(j,0,3)printf("%lld%c",d[j],j==3?'\n':' ');
	}
	a[n-1]=a[n]=b[n]=0;
	fr(i,1,n)
	{
		f[i][0]=b[a[i]];
		da[i][0]=dis(i,a[i]);
		db[i][0]=dis(a[i],b[a[i]]);
		d[i][0]=da[i][0]+db[i][0];
	}
	fr(j,1,B)fr(i,1,n)
	{
		f[i][j]=f[f[i][j-1]][j-1];
		d[i][j]=d[i][j-1]+d[f[i][j-1]][j-1];
		da[i][j]=da[i][j-1]+da[f[i][j-1]][j-1];
		db[i][j]=db[i][j-1]+db[f[i][j-1]][j-1];
	}
	l=read();
	fr(i,1,n)
	{
		long long aa=0,b=0,ll=l;x=i;
		fd(j,B,0)if(f[x][j]&&d[x][j]<=ll)
		{
			ll-=d[x][j];aa+=da[x][j];b+=db[x][j];x=f[x][j];
		}
		if(a[x]&&da[x][0]<=ll)aa+=da[x][0];
		if(ans==0||(!(b==0&&z!=0)&&aa*z==b*y?h[i]>h[ans]:aa*z<b*y))
		{
			ans=i;y=aa;z=b;
		}
//		printf("%lld %lld\n",a,b);
	}
//	fr(i,1,n)printf("%lld%c",a[i],i==n?'\n':' ');
//	fr(i,1,n)printf("%lld%c",b[i],i==n?'\n':' ');
	printf("%lld\n",ans);
	int q=read();
	while(q--)
	{
		long long aa=0,b=0;x=read();l=read();
		fd(j,B,0)if(f[x][j]&&d[x][j]<=l)
		{
//			printf("%lld %lld %lld\n",l,x,j);
			l-=d[x][j];aa+=da[x][j];b+=db[x][j];x=f[x][j];
		}
		if(a[x]&&da[x][0]<=l)aa+=da[x][0];
		printf("%lld %lld\n",aa,b);
	}
//	fr(i,1,n)fr(j,0,B)printf("%lld%c",f[i][j],j==B?'\n':' ');
	return 0;
}