/***************************************************************
	File name: G.cpp
	Author: huhao
	Create time: Tue 13 Oct 2020 05:14:48 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
const int N=1000010;
const i64 inf=1ll<<60;
i64 l,v1,v2,e,s,c;
i64 a[N],A[N];
i64 v[N],m,h;
i64 calc(i64 l,i64 mx)
{
	if(!l) return 0;
	i64 x=0,y=h; x=0;
	fr(i,1,m)
		if(v[i]>0){ x+=1<<(h-v[i]); l-=(1<<(h-v[i]+1))-1; }
		else{ x+=1<<(h+v[i]); l-=(1<<(h+v[i]+1)); }
//	printf("%lld %lld  %lld  %lld\n",x,l,y,mx);
	while((x<<5)-(x<<1)<=l){ l-=(x<<5)-(x<<1); x<<=4; y+=4; }
	while(l>0){ l-=(x<<=1); y++; }
	return y>mx?inf:y;
}
int solve(i64 n,i64 H)
{
	if(n==0) return 1;
	if(m==0) return 0;
	if(v[m]<0){ v[m]=-v[m]; return solve(n-1,H); }
	if(v[m]>H){ m--; return solve(n,H); }
	if(n>>(H-v[m]+1)) // n>(1<<(H-v[m]+1))-1
	{
		n-=(1<<(H-v[m]+1))-1; m--;
		return solve(n,H);
	}
	else
	{
		v[m]++; v[m+1]=v[m]; v[m]=-v[m]; m++;
		return solve(n,H);
	}
}
int main()
{
	fr(T,1,read())
	{
		l=read(); v1=read(); v2=read(); e=read(); s=read();
		if(v2-v1<=e){ printf("0\n"); continue; }
		v1=v2-(v2-v1-1)/e*e; v2-=e; a[c=0]=v1-e;
		if(v2>l){ printf("impossible\n"); continue; }
		for(i64 i=v1,j;i<=v2;)
		{
			j=l/(l/i); j=v1+(j-v1)/e*e; a[++c]=j; i=j+e;
		}
		if(a[c]>v2) a[c]=v2;
		v[m=1]=1; h=1;
		fr(i,1,c){ A[i]=(a[i]-a[0])/e; a[i]=l/s/a[i]; }
		A[0]=0;
//		fr(i,0,c) printf("%lld %lld\n",A[i],a[i]);
		i64 ans=calc(A[c],a[c]);
		fd(i,c,1) if(ans==inf)
		{
			h=a[i]+1;
			if(!solve(A[i]-A[i-1],a[i])) break;
//			printf(" %d %lld\n",i,m);
//			fr(j,1,m) printf("%lld%c",v[j],j==m?'\n':' ');
			ans=std::min(ans,std::max(calc(A[i-1],a[i-1]),a[i]));
		}
		if(ans==inf) printf("impossible\n");
		else printf("%lld\n",ans);
//		putchar(10);
	}
	return 0;
}
