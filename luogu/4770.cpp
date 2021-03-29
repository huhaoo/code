/**************************************************************
	File name: 4770.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 3/13/2019, 9:43:01 AM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#define N 1000010
struct sam
{
	int n,k,l[N],f[N],t[N][30],r[N];
	void clear()
	{
		fr(i,0,n)
		{
			l[i]=0;
			r[i]=0;
			f[i]=0;
			memset(t[i],0,sizeof(t[i]));
		}
		n=k=1;
	}
	sam()
	{
		clear();
	}
	int insert(int c)
	{
		int p,np,q,nq;
		np=++n;
		l[np]=l[k]+1;
		r[np]=r[k]+1;
		p=k;
		k=np;
		while(p&&!t[p][c])
		{
			t[p][c]=np;
			p=f[p];
		}
		if(!p)
		{
			f[np]=1;
			return np;
		}
		q=t[p][c];
		if(l[q]==l[p]+1)
		{
			f[np]=q;
			return np;
		}
		nq=++n;
		r[nq]=r[q];
		memcpy(t[nq],t[q],sizeof(t[q]));
		l[nq]=l[p]+1;
		f[nq]=f[q];
		f[q]=f[np]=nq;
		while(p&&t[p][c]==q)
		{
			t[p][c]=nq;
			p=f[p];
		}
		return np;
	}
	/*
	int walk(int p,char *s)
	{
		int l=strlen(s);
		fr(i,0,l-1)
			p=t[p][s[i]-'a'];
		return p;
	}
	*/
}s,t;
char cs[N],ct[N];
int v[N*40],l[N*40][2],r[N],cnt,ls,lt,T,d[N],p[N];
void t_insert(int k,int p,int _l,int _r,int _v)
{
	v[k]+=_v;
	if(_l==_r)
		return;
	int mid=(_l+_r)>>1;
	if(p<=mid)
	{
		if(!l[k][0])
			l[k][0]=++cnt;
		t_insert(l[k][0],p,_l,mid,_v);
	}
	else
	{
		if(!l[k][1])
			l[k][1]=++cnt;
		t_insert(l[k][1],p,mid+1,_r,_v);
	}
}
int t_merge(int _l,int _r)
{
	if(!_l||!_r)
		return _l+_r;
	int c=++cnt;
	v[c]=v[_l]+v[_r];
	l[c][0]=t_merge(l[_l][0],l[_r][0]);
	l[c][1]=t_merge(l[_l][1],l[_r][1]);
	return c;
}
int t_sum(int k,int _l,int _r,int ql,int qr)
{
	if(_r<ql||_l>qr||!v[k])
		return 0;
	if(_l>=ql&&_r<=qr)
		return v[k];
	int mid=(_l+_r)>>1;
	return t_sum(l[k][0],_l,mid,ql,qr)+t_sum(l[k][1],mid+1,_r,ql,qr);
}
struct que
{
	int q[N],l,r;
	void clear()
	{
		l=1;
		r=0;
	}
	que()
	{
		clear();
	}
}q;
/*
void print(int k,int _l,int _r)
{
	if(!v[k])
		return;
	if(_l==_r)
		printf(" %d %d %d\n",_l,_r,v[k]);
	int mid=(_l+_r)>>1;
	print(l[k][0],_l,mid);
	print(l[k][1],mid+1,_r);
}
*/
int main()
{
	scanf("%s",cs+1);
	ls=strlen(cs+1);
	fr(i,1,ls)
	{
		int np=s.insert(cs[i]-'a');
		r[np]=++cnt;
		t_insert(r[np],i,1,ls,1);
	}
//	fr(i,1,s.n)
//		printf("%d%c",s.f[i],i==s.n?'\n':' ');
	fr(i,1,s.n)
		d[s.f[i]]++;
	fr(i,1,s.n)
		if(!d[i])
			q.q[++q.r]=i;
	while(q.l<=q.r)
	{
		int u=q.q[q.l];
		q.l++;
		if(!s.f[u])
			continue;
		r[s.f[u]]=t_merge(r[s.f[u]],r[u]);
		d[s.f[u]]--;
		if(!d[s.f[u]])
			q.q[++q.r]=s.f[u];
	}
	T=read();
	while(T--)
	{
		scanf("%s",ct+1);
		int _l=read(),_r=read();
		long long ans=0;
		lt=strlen(ct+1);
		t.clear();
		p[0]=0;
		int j=1;
		fr(i,1,lt)
		{
			p[i]=p[i-1];
			while(1)
			{
//				print(r[s.t[j][c[i]-'a']],1,ls);
//				printf("%d %d %d %c %d %d %d %d\n",i,j,s.f[j],ct[i],s.t[j][ct[i]-'a'],_l+p[i],_r,t_sum(r[s.t[j][ct[i]-'a']],1,ls,_l+p[i],_r));
				if(s.t[j][ct[i]-'a']&&t_sum(r[s.t[j][ct[i]-'a']],1,ls,_l+p[i],_r))
				{
					j=s.t[j][ct[i]-'a'];
					p[i]++;
					break;
				}
				if(!p[i])
					break;
				p[i]--;
				if(p[i]<=s.l[s.f[j]])
					j=s.f[j];
			}
			t.insert(ct[i]-'a');
		}
//		fr(i,_l,_r)
//			printf("%c",cs[i]);
//		putchar(10);
//		printf("%s\n",ct+1);
//		fr(i,1,lt)
//			printf("%d%c",p[i],i==lt?'\n':' ');
		q.clear();
		fr(i,1,t.n)
			d[i]=0;
		fr(i,1,t.n)
			d[t.f[i]]++;
		fr(i,1,t.n)
			if(!d[i])
				q.q[++q.r]=i;
		while(q.l<=q.r)
		{
			int u=q.q[q.l];
			q.l++;
			t.r[t.f[u]]=min(t.r[t.f[u]],t.r[u]);
			d[t.f[u]]--;
			if(!d[t.f[u]])
				q.q[++q.r]=t.f[u];
		}
		fr(i,1,t.n)
			ans+=max(t.l[i]-max(p[t.r[i]],t.l[t.f[i]]),0);
		printf("%lld\n",ans);
	}
	return 0;
}