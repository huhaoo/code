/***************************************************************
	File name: 3804.cpp
	Author: huhao
	Create time: Thu 11 Jul 2019 09:08:02 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
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
const int N=2000010,C=30;
int t[N][C],w[N],f[N],l[N],c,k;
void add(int s)
{
	int p,q,np,nq;
	np=++c;
	p=k;
	l[np]=l[k]+1;
	k=np;
	w[np]=1;
	while(p&&!t[p][s])
	{
		t[p][s]=np;
		p=f[p];
	}
	if(!p)
	{
		f[np]=1;
		return;
	}
	q=t[p][s];
	if(l[q]==l[p]+1)
	{
		f[np]=q;
		return;
	}
	nq=++c;
	f[nq]=f[q];
	f[np]=f[q]=nq;
	l[nq]=l[p]+1;
	memcpy(t[nq],t[q],sizeof(t[0]));
	while(p&&t[p][s]==q)
	{
		t[p][s]=nq;
		p=f[p];
	}
}
char s[N];
int n,q[N],_l,_r,d[N];
int main()
{
	c=k=1;
	scanf("%s",s+1);
	n=strlen(s+1);
	fr(i,1,n)
		add(s[i]-'a');
	fr(i,2,c)
		d[f[i]]++;
	fr(i,1,c)
		if(!d[i])
			q[++_r]=i;
	_l=1;
	while(_l<=_r)
	{
		int u=q[_l];
		_l++;
		w[f[u]]+=w[u];
		d[f[u]]--;
		if(!d[f[u]])
			q[++_r]=f[u];
	}
	long long ans=0;
	fr(i,1,c)
		if(w[i]>1)
			ans=max(ans,(long long)w[i]*l[i]);
	printf("%lld\n",ans);
	return 0;
}
