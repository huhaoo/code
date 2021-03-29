/***************************************************************
	File name: J.cpp
	Author: huhao
	Create time: Wed 04 Nov 2020 04:23:32 PM CST
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
#define pii std::pair<i64,i64>
#include<vector>
const int N=25100;
const i64 inf=1ll<<50;
int n,m,c;
i64 a[N]; int b[N],id[N]; i64 mi[N],mx[N];
i64 aa[510][510];
int ans[N];
i64 at(int p,i64 v){ return a[p]+b[p]*v; }
int main()
{
	n=read(); m=read();
	fr(i,1,n)
	{
		static i64 A[N];
		fr(j,1,m) A[j]=read();
		std::sort(A+1,A+m+1);
		fr(j,1,m) A[j]+=A[j-1];
		fr(j,1,m){ aa[i][m-j]=A[j]; c++; id[c]=i; a[c]=A[j]; b[c]=m-j; mi[c]=at(c,0); mx[c]=at(c,inf); }
	}
	fr(i,1,n) ans[i]=n;
	fr(i,1,c)
	{
		i64 l[N],r[N],v[N];
		static pii p[N]; int t=0; int s=n,Ans=n;
		fr(j,1,n){ v[j]=1; l[j]=0; r[j]=inf; }
		v[id[i]]=0;
		fr(j,1,c) if(id[i]!=id[j]&&aa[id[j]][b[i]]>a[i])
		{
			if((mi[i]>=mi[j])!=(mx[i]>=mx[j]))
			{
				if(b[i]>b[j]) r[id[j]]=std::min(r[id[j]],(a[j]-a[i]-1)/(b[i]-b[j])+1);
				else l[id[j]]=std::max(l[id[j]],(a[i]-a[j])/(b[j]-b[i])+1);
			}
			else if(mi[i]>=mi[j]) v[id[j]]=0;
		}
		else v[id[j]]=0;
//		printf("%d  %lld %d\n",i,a[i],b[i]);
//		fr(j,1,n) if(v[j]) printf("  %d:%lld %lld\n",j,l[j],r[j]);
		fr(j,1,n) if(l[j]>=r[j]) v[j]=0;
		fr(j,1,n) if(v[j]){ p[++t]=pii(l[j],1); p[++t]=pii(r[j],-1); }
//		fr(j,1,t) printf(" %lld %lld\n",p[j].first,p[j].second);
		std::sort(p+1,p+t+1);
		fr(j,1,t)
		{
			s-=p[j].second; Ans=std::min(Ans,s);
		}
		ans[id[i]]=std::min(ans[id[i]],Ans);
	}
	fr(i,1,n) printf("%d\n",ans[i]);
	return 0;
}
