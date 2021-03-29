/***************************************************************
	File name: list.cpp
	Author: huhao
	Create time: Sat 24 Oct 2020 03:27:05 PM CST
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
const int N=3000;
int n,m,p[N],v[N],lg[N];
i64 f[N][N],g[N][N],h[N][N],F[N][N],G[N][N],H[N][N];
int a[N],c;
char s[N]; int C;
inline i64 query(i64 a,i64 b){ return h[a][b]+g[a][b]*2+f[a][b]*2; }
void tostring()
{
	s[C=0]='[';
	fr(i,1,c)
	{
		static int A[N],t; t=0; int o=a[i];
		while(o){ A[++t]=o%10; o/=10; }
		while(t) s[++C]=A[t--]+48;
		if(i==c){ s[++C]=']'; s[++C]=','; }
		else{ s[++C]=','; s[++C]=' '; }
	}
	s[++C]=' '; s[++C]=0;
}
i64 lower(i64 l)
{
	i64 S=l,I=0; c=0;
	fr(i,1,n){ S-=query(1,i); if(S<=0){ I=i; break; } }
	S=l; fr(i,1,I-1) S-=query(1,i); i64 Lg=0,_S=0;
//	fprintf(stderr,"%lld %lld\n",I,S);
	for(int i=1;_S<I&&p[i]<=I;)
	{
		int j=i;
		while(I-_S-p[j]>=0&&S-(h[j+1][I-_S-p[j]]+2*g[j+1][I-_S-p[j]]+(4+Lg+lg[p[j]])*f[j+1][I-_S-p[j]])>0)
		{
//			fprintf(stderr,"* %lld %lld  %lld\n",p[j],S,h[j+1][I-_S-p[j]]+2*g[j+1][I-_S-p[j]]+(4+Lg+lg[p[j]])*f[j+1][I-_S-p[j]]);
			S-=(h[j+1][I-_S-p[j]]+2*g[j+1][I-_S-p[j]]+(4+Lg+lg[p[j]])*f[j+1][I-_S-p[j]]); j++;
		}
		a[++c]=p[j]; Lg+=lg[p[j]]+2; _S+=p[j]; i=j+1;
	}
//	fprintf(stderr," "); fr(i,1,c) fprintf(stderr,"%d%c",a[i],i==c?'\n':' ');
	tostring();
//	fprintf(stderr,"> %lld %lld %lld  %lld\n",l,S,C,l-S-C+1);
	return l-S+1;
}
void print(i64 l,i64 r)
{
	while(l<=r)
	{
		i64 p=lower(l);
//		fprintf(stderr,"%lld %lld  %s\n",p,p+C-1,s);
		if(!(l<p+C)) return ;
		while(l<=r&&l<p+C){ putchar(s[l-p]); l++; }
	}
}
int main()
{
	freopen("list.in","r",stdin); freopen("list.out","w",stdout);
	n=2100;
	fr(i,2,n)
	{
		if(!v[i]) p[++m]=i;
		fr(j,1,m) if(i*p[j]<=n)
		{
			v[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
		else break;
	}
	fr(i,1,n) lg[i]=lg[i/10]+1;
	f[m+1][0]=1;
	fd(i,m,1) fr(j,0,n) f[i][j]=f[i+1][j]+(j>=p[i]?f[i+1][j-p[i]]:0);
	fd(i,m,1) fr(j,0,n) g[i][j]=g[i+1][j]+(j>=p[i]?g[i+1][j-p[i]]+f[i+1][j-p[i]]:0);
	fd(i,m,1) fr(j,0,n) h[i][j]=h[i+1][j]+(j>=p[i]?h[i+1][j-p[i]]+f[i+1][j-p[i]]*lg[p[i]]:0);
	fr(i,1,m)
	{
		F[i][0]=f[i][0]; G[i][0]=g[i][0]; H[i][0]=h[i][0];
		fr(j,1,n){ F[i][j]=f[i][j]+F[i][j-1]; G[i][j]=g[i][j]+G[i][j-1]; H[i][j]=h[i][j]+H[i][j-1]; }
	}
	i64 l=read(),r=read();
	print(l,r);
	return 0;
}
