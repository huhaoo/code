/***************************************************************
	File name: G.cpp
	Author: huhao
	Create time: Thu 29 Oct 2020 07:33:37 PM CST
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
#define pii std::pair<int,int>
#define F first
#define S second
const int N=1<<18|10,L=18;
int f[N],n,m;
char s[N];
int R[N],a[N][4],F[N][L+2],d[N],p[N],g[N];
int New(){ m++; memset(a[m],0,sizeof(a[m])); return m; }
int Go(int p,int D)
{
	if(d[p]<D) return 1;
//	printf("j %d %d   ",p,D);
	fd(i,L,0) if(d[p]-(1<<i)>=D) p=F[p][i];
//	printf("%d\n",p);
	return p;
}
int ins(int p,int c)
{
	if(a[p][c]) return a[p][c];
	int q=New();
//	printf("+ %d %d  %d\n",p,c,q);
	a[p][c]=q; d[q]=d[p]+1; F[q][0]=p;
	fr(i,1,L) F[q][i]=F[F[q][i-1]][i-1];
	return q;
}
pii t[N];
int _l[N];
pii queryr(int k,int l,int r,int v)
{
	if(v<0) return pii(0,0);
	if(l==r) return pii(std::min(f[l],v+1),l);
	int mid=(l+r)>>1;
	if(t[k<<1].F+t[k<<1].S-1>=r+v) return queryr(k<<1,l,mid,v+_l[k<<1|1]);
	else return queryr(k<<1|1,mid+1,r,v);
}
pii Queryr(int k,int l,int r,int L,int R,int p)
{
	if(l>R||L>r) return pii(0,0);
	if(L<=l&&r<=R) return queryr(k,l,r,p-r);
	int mid=(l+r)>>1;
	return std::max(Queryr(k<<1,l,mid,L,R,p),Queryr(k<<1|1,mid+1,r,L,R,p));
}
void build(int k,int l,int r)
{
	_l[k]=r-l+1;
	if(l==r){ t[k]=pii(f[l],l); return ; }
	int mid=(l+r)>>1;
	build(k<<1,l,mid); build(k<<1|1,mid+1,r);
	if(t[k<<1].F+t[k<<1].S<t[k<<1|1].F+t[k<<1|1].S) t[k]=t[k<<1|1];
	else t[k]=t[k<<1];
}
int query(int p,int l){ return g[Go(R[p],l)]; }
void dp()
{
	static int q[N],l,r; l=1; r=0;
	fr(i,0,3) if(a[1][i]) q[++r]=a[1][i];
	g[0]=g[1]=-1;
//	fr(i,1,m) fr(j,0,3) printf("%d%c",a[i][j],j==3?'\n':' ');
	while(l<=r)
	{
		int u=q[l++];
		int _l=p[u],_r=p[u]+d[u]-1,mid=(_l+_r)/2;
		pii x=Queryr(1,1,n,mid+1,_r,_r);
//		printf(" %d %d  %d\n",x.S,x.F,Go(R[x.S],x.F));
		g[u]=std::max(query(x.S,x.F)+d[u]-1,g[F[u][0]]+1);
		fr(i,0,3) if(a[u][i]) q[++r]=a[u][i];
//		printf("%d    %d  (%d,%d)  %d\n",u,F[u][0],p[u],p[u]+d[u]-1,g[u]);
	}
}
int main()
{
	fr(T,1,read())
	{
		scanf("%s",s+1); n=strlen(s+1); m=0; R[0]=R[1]=New();
		fr(i,1,n)
		{
			if(s[i]=='A') s[i]=0;
			else if(s[i]=='C') s[i]=1;
			else if(s[i]=='G') s[i]=2;
			else s[i]=3;
		}
		for(int i=2,j=0,r=0;i<=n;i++) if(s[i]==s[i-1])
		{
//			printf("%d %d %d  %d %d\n",i,j,r,j-(i-j),f[j-(i-j)]);
			if(i<=r){ f[i]=std::min(f[j-(i-j)],r-i+1); R[i]=Go(R[j-(i-j)],f[i]); }
			else{ f[i]=0; R[i]=1; }
//			printf("%d %d %d   %d\n",i,f[i],R[i],s[i]);
			while(i+f[i]<=n&&i-f[i]-1>=1&&s[i+f[i]]==s[i-f[i]-1]){ p[R[i]=ins(R[i],s[i+f[i]])]=i; f[i]++; }
			if(i+f[i]-1>r){ r=i+f[i]-1; j=i; }
//			printf(" %d %d\n",i,f[i]);
		}
		else{ f[i]=0; R[i]=1; }
//		fr(i,1,n) printf("%d%c",p[R[i]],i==n?'\n':' ');
		build(1,1,n); dp();
		int ans=0;
		fr(i,1,m) ans=std::max(ans,g[i]);
//		fr(i,1,n) printf("%d%c",i%10,i==end_i?'\n':' ');
//		fr(i,1,n) printf("%d%c",s[i],i==end_i?'\n':' ');
//		fr(i,1,n) printf("%d%c",f[i],i==end_i?'\n':' ');
//		printf("%d\n",ans);
		printf("%d\n",n-ans);
	}
	return 0;
}
