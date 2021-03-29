/****************************************************************
	File name: 1486.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/17/2018, 9:53:52 PM
****************************************************************/
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
#define N 100010
#include<stdlib.h>
int r,v[N],w[N],s[N][2],siz[N],q,m,p,cnt;
#define update(k) siz[k]=1+siz[s[k][0]]+siz[s[k][1]];
int make(int vv,int ww)
{
	cnt++;
	v[cnt]=vv;w[cnt]=ww;siz[cnt]=1;
	return cnt;
}
int merge(int l,int r)
{
	if(l*r==0)return l+r;
	if(w[l]<=w[r])
	{
		s[l][1]=merge(s[l][1],r);
		update(l);
		return l;
	}
	else
	{
		s[r][0]=merge(l,s[r][0]);
		update(r);
		return r;
	}
}
void split(int k,int val,int &l,int &r)
{
	if(!k){l=r=0;return;}
	if(v[k]<=val)
	{
		l=k;
		split(s[l][1],val,s[l][1],r);
		update(l);
	}
	else
	{
		r=k;
		split(s[r][0],val,l,s[r][0]);
		update(r);
	}
}
void insert(int v)
{
	int l,rr;
	split(r,v,l,rr);
	r=merge(l,merge(make(v,rand()),rr));
}
int kth(int x,int k)
{
	if(siz[s[x][1]]>=k)return kth(s[x][1],k);
	if(siz[s[x][1]]+1==k)return v[x];
	return kth(s[x][0],k-siz[s[x][1]]-1);
}
void print(int x)
{
	if(!x)return;
	printf("(");print(s[x][0]);printf("%d",v[x]);print(s[x][1]);printf(")");
}
char opt[10];
int sum;
int main()
{
	srand((unsigned long long)new char);
	q=read();m=read();
	while(q--)
	{
		scanf("%s",opt);
		if(*opt=='I')
		{
			int a=read();
			insert(a-p);
			if(a-p<m)sum--;
		}
		if(*opt=='A')
		{
			int a=read();
			p+=a;m-=a;
		}
		if(*opt=='S')
		{
			int a=read();
			p-=a;m+=a;
		}
		if(*opt=='F')
		{
			int a=read();
			if(siz[r]<a)printf("-1\n");
			else printf("%d\n",kth(r,a)+p);
		}
		int l;
		split(r,m-1,l,r);
		sum+=siz[l];
	}
	printf("%d\n",sum);
	return 0;
}