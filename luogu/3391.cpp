/**************************************************************
	File name: 3391.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/1/2018, 4:16:16 PM
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
#include<stdlib.h>
#define N 100010
int val[N],w[N],s[N][2],n,q,rev[N],cnt,root,siz[N];
#define update(k) siz[k]=siz[s[k][0]]+siz[s[k][1]]+1
int make(int v,int ww){cnt++;val[cnt]=v;w[cnt]=ww;siz[cnt]=1;return cnt;}
void reverse(int k)
{
	if(rev[k])
	{
		swap(s[k][0],s[k][1]);
		rev[s[k][0]]^=1;rev[s[k][1]]^=1;rev[0]=0;
		rev[k]=0;
	}
}
int merge(int l,int r)
{
	if(l*r==0)return l+r;
	if(w[l]<=w[r])
	{
		reverse(l);
		s[l][1]=merge(s[l][1],r);
		update(l);
		return l;
	}
	else
	{
		reverse(r);
		s[r][0]=merge(l,s[r][0]);
		update(r);
		return r;
	}
}
void split(int k,int v,int &l,int &r)
{
	if(!k){l=r=0;return;}
	reverse(k);
	if(siz[s[k][0]]<v)
	{
		l=k;
		split(s[k][1],v-siz[s[k][0]]-1,s[l][1],r);
	}
	else
	{
		r=k;
		split(s[k][0],v,l,s[r][0]);
	}
	update(k);
}
void print(int k)
{
	if(!k)return;
	reverse(k);
	print(s[k][0]);
	printf("%d ",val[k]);
	print(s[k][1]);
}
int main()
{
	srand((unsigned long long)new char);
	n=read();
	fr(i,1,n)root=merge(root,make(i,rand()));
	q=read();
	while(q--)
	{
		int l=read(),r=read();
		int a,b,c;
		split(root,l-1,a,b);
		split(b,r-l+1,b,c);
		rev[b]^=1;
		root=merge(a,merge(b,c));
	}
	print(root);
	return 0;
}