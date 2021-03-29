/**************************************************************
	File name: 可持久化平衡树.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/12/2018, 4:09:27 PM
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
#define N 500010
#define D 50
int cnt,siz[N*D],val[N*D],w[N*D],s[N*D][2],r[N];
int make(int v,int ww)
{
	cnt++;val[cnt]=v;w[cnt]=ww;siz[cnt]=1;
	return cnt;
}
int make(int p)
{
	cnt++;
	val[cnt]=val[p];siz[cnt]=siz[p];w[cnt]=w[p];
	s[cnt][0]=s[p][0];s[cnt][1]=s[p][1];
	return cnt;
}
#define update(k) siz[k]=1+siz[s[k][0]]+siz[s[k][1]]
int merge(int l,int r)
{
	if(l*r==0)return l+r;
	if(w[l]<=w[r])
	{
		int k=make(l);
		s[k][1]=merge(s[k][1],r);
		update(k);
		return k;
	}
	else
	{
		int k=make(r);
		s[k][0]=merge(l,s[k][0]);
		update(k);
		return k;
	}
}
void split(int x,int v,int &l,int &r)
{
	if(!x){l=r=0;return;}
	if(val[x]<=v)
	{
		l=make(x);
		split(s[l][1],v,s[l][1],r);
		update(l);
	}
	else
	{
		r=make(x);
		split(s[r][0],v,l,s[r][0]);
		update(r);
	}
}
int insert(int ro,int v)
{
	int l,r;
	split(ro,v,l,r);
	return merge(merge(l,make(v,rand())),r);
}
int _delete(int ro,int v)
{
	int l,m,r;
	split(ro,v-1,l,r);
	split(r,v,m,r);
	return merge(merge(l,merge(s[m][0],s[m][1])),r);
}
int _rank(int ro,int v,int &nr)
{
	int l,r;
	split(ro,v-1,l,r);
	int ans=siz[l]+1;nr=merge(l,r);
	return ans;
}
int kth(int ro,int k,int &nr)
{
	nr=ro;
	while(ro)
	{
		if(siz[s[ro][0]]>=k){ro=s[ro][0];continue;}
		k-=siz[s[ro][0]];
		if(k==1)return val[ro];
		ro=s[ro][1];k-=1;
	}
	return -1;
}
int min(int r)
{
	while(s[r][0])r=s[r][0];
	return val[r];
}
int max(int r)
{
	while(s[r][1])r=s[r][1];
	return val[r];
}
int lower(int ro,int v,int &nr)
{
	int l,r;
	split(ro,v-1,l,r);
	if(!l){nr=r;return -2147483647;}
	int ans=max(l);
	nr=merge(l,r);
	return ans;
}
int upper(int ro,int v,int &nr)
{
	int l,r;
	split(ro,v,l,r);
	if(!r){nr=l;return 2147483647;}
	int ans=min(r);
	nr=merge(l,r);
	return ans;
}

int main()
{
	srand((unsigned long long)new char);
	fr(i,1,read())
	{
		int v=read(),o=read(),x=read();
		if(o==1)r[i]=insert(r[v],x);
		if(o==2)r[i]=_delete(r[v],x);
		if(o==3)printf("%d\n",_rank(r[v],x,r[i]));
		if(o==4)printf("%d\n",kth(r[v],x,r[i]));
		if(o==5)printf("%d\n",lower(r[v],x,r[i]));
		if(o==6)printf("%d\n",upper(r[v],x,r[i]));
	}
	return 0;
}