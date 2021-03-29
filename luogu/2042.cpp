/***************************************************************
	File name: 2042.cpp
	Author: huhao
	Create time: Thu 27 Jun 2019 06:51:02 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(long long i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(long long i=(a),end_##i=(b);i>=end_##i;i--)
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
		r=r*10+c-48;
		c=getchar();
	}
	return r*t;
}
const long long N=500010,inf=1ll<<40;
#include<stdlib.h>
long long n,q,c[N],v[N],R,s[N][2],S[N],w[N],tw[N],mw[N][2],aw[N],rev[N],f[N],F[N];
//node: v,s,S,w,tw,mw,rev,f,F,aw
long long make(long long _w)
{
	long long k=c[c[0]];
	c[0]--;
	s[k][0]=s[k][1]=0;
	v[k]=rand();
	tw[k]=_w;
	w[k]=_w;
	S[k]=1;
	rev[k]=0;
	F[k]=0;
	mw[k][0]=mw[k][1]=aw[k]=w[k];
	return k;
}
void down(long long k)
{
	if(!k)
		return;
	if(rev[k])
	{
		swap(s[k][0],s[k][1]);
		swap(mw[k][0],mw[k][1]);
		rev[k]=0;
		rev[s[k][0]]^=1;
		rev[s[k][1]]^=1;
		rev[0]=0;
	}
	if(F[k])
	{
		w[k]=S[k]*f[k];
		tw[k]=f[k];
		F[k]=0;
		F[s[k][0]]=F[s[k][1]]=1;
		f[s[k][0]]=f[s[k][1]]=f[k];
		F[0]=f[0]=0;
		mw[k][0]=mw[k][1]=aw[k]=max(w[k],f[k]);
	}
}
void update(long long k)
{
	down(s[k][0]);
	down(s[k][1]);
	S[k]=1+S[s[k][0]]+S[s[k][1]];
	w[k]=tw[k]+w[s[k][0]]+w[s[k][1]];
	mw[k][0]=max(mw[s[k][0]][0],w[s[k][0]]+tw[k]+max(mw[s[k][1]][0],0ll));
	mw[k][1]=max(mw[s[k][1]][1],w[s[k][1]]+tw[k]+max(mw[s[k][0]][1],0ll));
	aw[k]=max(max(aw[s[k][0]],aw[s[k][1]]),tw[k]+max(mw[s[k][0]][1],0ll)+max(mw[s[k][1]][0],0ll));
}
long long merge(long long a,long long b)
{
	if(!a||!b)
		return a|b;
	if(v[a]<v[b])
	{
		down(a);
		s[a][1]=merge(s[a][1],b);
		update(a);
		return a;
	}
	else
	{
		down(b);
		s[b][0]=merge(a,s[b][0]);
		update(b);
		return b;
	}
}
void split(long long k,long long p,long long &l,long long &r)
{
	if(!k)
	{
		l=r=0;
		return;
	}
	down(k);
	if(p>=S[s[k][0]]+1)
	{
		l=k;
		split(s[l][1],p-S[s[k][0]]-1,s[l][1],r);
		update(l);
	}
	else
	{
		r=k;
		split(s[r][0],p,l,s[r][0]);
		update(r);
	}
}
void del(int k)
{
	if(!k)
		return;
	c[++c[0]]=k;
	del(s[k][0]);
	del(s[k][1]);
}
int main()
{
	srand((unsigned long long)new char);
	mw[0][0]=mw[0][1]=aw[0]=-inf;
	n=read();
	q=read();
	fr(i,1,500000)
		c[++c[0]]=i;
	fr(i,1,n)
		R=merge(R,make(read()));
	while(q--)
	{
		char s[20];
		scanf("%s",s);
		if(*s=='I')
		{
			long long p=read(),l,r;
			split(R,p,l,r);
			fr(i,1,read())
				l=merge(l,make(read()));
			R=merge(l,r);
		}
		else if(*s=='D')
		{
			long long p=read(),L=read(),l,m,r;
			split(R,p-1,l,m);
			split(m,L,m,r);
			R=merge(l,r);
			del(m);
		}
		else if(*s=='R')
		{
			long long p=read(),L=read(),l,m,r;
			split(R,p-1,l,m);
			split(m,L,m,r);
			rev[m]^=1;
			r=merge(l,merge(m,r));
		}
		else if(*s=='M'&&*(s+2)=='K')
		{
			long long p=read(),L=read(),_v=read(),l,m,r;
			split(R,p-1,l,m);
			split(m,L,m,r);
			F[m]=1;
			f[m]=_v;
			R=merge(l,merge(m,r));
		}
		else if(*s=='G')
		{
			long long p=read(),L=read(),l,m,r;
			split(R,p-1,l,m);
			split(m,L,m,r);
			printf("%lld\n",w[m]);
			R=merge(l,merge(m,r));
		}
		else
			printf("%lld\n",aw[R]);
	}
	return 0;
}
