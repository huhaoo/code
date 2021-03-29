/***************************************************************
	File name: G.cpp
	Author: huhao
	Create time: Mon 30 Nov 2020 04:49:39 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
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
const int N=4000010;
int n,t[N][26],m,s[N],r[N],q,f[N];
int Q[N],L,R;
int id[N];
char c[N];
int main()
{
	n=read(); q=read(); r[0]=m=1;
	fr(i,1,n)
	{
		int f; scanf("%s%d",c,&f);
		int C=c[0]-'A'; s[r[i]=t[r[f]][C]=++m]++;
	}
	fr(i,1,q)
	{
		scanf("%s",c); std::reverse(c,c+strlen(c));
		int p=1;
		fr(i,0,strlen(c)-1)
		{
			int o=c[i]-'A';
			if(!t[p][o]) t[p][o]=++m;
			p=t[p][o];
		}
		id[i]=p;
	}
	f[1]=1;
	fr(i,0,25) if(!t[1][i]) t[1][i]=1;
	else{ f[t[1][i]]=1; Q[++R]=t[1][i]; }
	while(L<=R)
	{
		int u=Q[L++];
		fr(i,0,25)
			if(t[u][i])
			{
				f[t[u][i]]=t[f[u]][i];
				Q[++R]=t[u][i];
			}
			else t[u][i]=t[f[u]][i];
	}
	fd(i,R,1) s[f[Q[i]]]+=s[Q[i]];
	fr(i,1,q) printf("%d\n",s[id[i]]);
	return 0;
}
