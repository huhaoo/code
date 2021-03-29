/****************************************************************
	File name: 3369.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/30/2018, 9:52:17 AM
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
int s[N][2],cnt,val[N],siz[N],root,w[N];
#define update(k) siz[k]=siz[s[k][0]]+siz[s[k][1]]+1
#include<stdlib.h>
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
void split(int k,int v,int &l,int &r)
{
	if(!k){l=r=0;return;}
	if(val[k]<=v)
	{
		l=k;
		split(s[l][1],v,s[l][1],r);
	}
	else
	{
		r=k;
		split(s[r][0],v,l,s[r][0]);
	}
	update(k);
}
int make(int v,int ww)
{
	cnt++;
	val[cnt]=v;
	w[cnt]=ww;
	siz[cnt]=1;
	return cnt;
}
void insert(int v)
{
	int l,r;
	split(root,v,l,r);
	root=merge(l,merge(make(v,rand()),r));
}
void delete_(int v)
{
	int l,r,m;
	split(root,v-1,l,r);
	split(r,v,m,r);
	root=merge(l,merge(merge(s[m][0],s[m][1]),r));
}
int rank_(int v)
{
	int l,r,ans;
	split(root,v-1,l,r);
	ans=siz[l]+1;
	root=merge(l,r);
	return ans;
}
int kth(int k,int v)
{
	if(siz[s[k][0]]>=v)return kth(s[k][0],v);
	if(siz[s[k][0]]+1==v)return val[k];
	return kth(s[k][1],v-siz[s[k][0]]-1);
}
int vmax(int k)
{
	while(s[k][1])k=s[k][1];
	return val[k];
}
int vmin(int k)
{
	while(s[k][0])k=s[k][0];
	return val[k];
}
int upper(int v)
{
	int l,r,ans;
	split(root,v,l,r);
	ans=vmin(r);
	merge(l,r);
	return ans;
}
int lower(int v)
{
	int l,r,ans;
	split(root,v-1,l,r);
	ans=vmax(l);
	merge(l,r);
	return ans;
}
int main()
{
	srand((unsigned long long)new char);
	fr(T,1,read())
    {
        int opt=read(),v=read();
        if(opt==1)insert(v);
        if(opt==2)delete_(v);
        if(opt==3)printf("%d\n",rank_(v));
        if(opt==4)printf("%d\n",kth(root,v));
        if(opt==5)printf("%d\n",lower(v));
        if(opt==6)printf("%d\n",upper(v));
    }
	return 0;
}