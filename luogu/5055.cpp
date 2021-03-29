/**************************************************************
	File name: 5055.cpp
	Author: huhao
	Email: 826538400@qq.com
	clone time: 2/20/2019, 3:48:40 PM
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
#define N 200010
#define M 30000010
int q,s[M][2],R[M],cnt,S[M],w[M],v[M],r[N];
long long ans,V[M];
int clone(int k)
{
	cnt++;
	w[cnt]=rand();
	s[cnt][0]=s[k][0];
	s[cnt][1]=s[k][1];
	S[cnt]=S[k];
	R[cnt]=R[k];
	v[cnt]=v[k];
	V[cnt]=V[k];
	return cnt;
}
int create(int _v)
{
	cnt++;
	w[cnt]=rand();
	S[cnt]=1;
	v[cnt]=V[cnt]=_v;
	return cnt;
}
void reverse(int k)
{
	if(R[k])
	{
		swap(s[k][0],s[k][1]);
		if(s[k][0])
		{
			s[k][0]=clone(s[k][0]);
			R[s[k][0]]^=1;
		}
		if(s[k][1])
		{
			s[k][1]=clone(s[k][1]);
			R[s[k][1]]^=1;
		}
		R[k]=0;
	}
}
void update(int k)
{
	S[k]=S[s[k][0]]+S[s[k][1]]+1;
	V[k]=V[s[k][0]]+V[s[k][1]]+v[k];
}
int merge(int a,int b)
{
	if(!a||!b)
		return a+b;
	int k;
	reverse(a);
	reverse(b);
	if(w[a]<w[b])
	{
		k=a;
		s[k][1]=merge(s[k][1],b);
	}
	else
	{
		k=b;
		s[k][0]=merge(a,s[k][0]);
	}
	update(k);
	return k;
}
void split(int x,int k,int &l,int &r)
{
	if(!x)
	{
		l=r=0;
		return;
	}
	x=clone(x);
	reverse(x);
	if(S[s[x][R[x]]]>=k)
	{
		r=x;
		split(s[r][0],k,l,s[r][0]);
		update(r);
	}
	else
	{
		l=x;
		split(s[l][1],k-S[s[l][0]]-1,s[l][1],r);
		update(l);
	}
}
int insert(int v,int p,int x)
{
	int _l,_r;
	split(r[v],p,_l,_r);
	return merge(merge(_l,create(x)),_r);
}
int del(int v,int p)
{
	int _l,_m,_r;
	split(r[v],p-1,_l,_m);
	split(_m,1,_m,_r);
	return merge(_l,_r);
}
int rev(int v,int _l,int _r)
{
	int l_,m_,r_;
	split(r[v],_r,m_,r_);
	split(m_,_l-1,l_,m_);
	m_=clone(m_);
	R[m_]^=1;
	return merge(merge(l_,m_),r_);
}
int query(int v,int _l,int _r)
{
	int l_,m_,r_;
	ans=0;
	split(r[v],_r,m_,r_);
	split(m_,_l-1,l_,m_);
	ans=V[m_];
	return clone(r[v]);
}
int main()
{
	srand((unsigned long long)new char);
	q=read();
	fr(i,1,q)
	{
		int v=read(),opt=read();
		switch(opt)
		{
			case 1:
			{
				int p=read()^ans,x=read()^ans;
				r[i]=insert(v,p,x);
				break;
			}
			case 2:
			{
				int p=read()^ans;
				r[i]=del(v,p);
				break;
			}
			case 3:
			{
				int _l=read()^ans,_r=read()^ans;
				r[i]=rev(v,_l,_r);
				break;
			}
			default:
			{
				int _l=read()^ans,_r=read()^ans;
				r[i]=query(v,_l,_r);
				printf("%lld\n",ans);
				break;
			}
		}
	}
	return 0;
}