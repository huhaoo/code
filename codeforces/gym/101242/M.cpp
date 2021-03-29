/***************************************************************
	File name: M.cpp
	Author: huhao
	Create time: Mon 30 Nov 2020 02:42:10 PM CST
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
#include<vector>
const int N=110;
int n,m;
int op[N][N],a[N][N],l[N],s[N],b[N],p[N];
int x[N],y[N],f[N],id[N];
int ans[N];
void work(int t)
{
	std::vector<int> z;
	fr(i,1,n) if(t>=s[i]&&p[i]<=l[i]) z.push_back(i);
	if(z.empty()) return ;
	for(auto i:z){ y[i]=b[i]; f[i]=0; }
//	fr(i,1,m) x[i]=0;
//	for(auto i:z) fr(j,1,l[i]) if(op[i][j]=='L') x[a[i][j]]=std::max(x[a[i][j]],b[j]);
	while(1)
	{
		int flag=0;
		for(auto i:z) if(op[i][p[i]]=='L'&&id[a[i][p[i]]])
		{
			f[i]=1; //printf("%d   %d %d\n",t,id[a[i][p[i]]],i);
			if(y[id[a[i][p[i]]]]<y[i]){ y[id[a[i][p[i]]]]=y[i]; flag=1; }
		}
		for(auto i:z) if(op[i][p[i]]=='L') fr(j,1,m) if(id[j]&&id[j]!=i&&x[j]>=y[i])
		{
			f[i]=1; //printf("%d   %d %d\n",t,id[j],i);
			if(y[id[j]]<y[i]){ y[id[j]]=y[i]; flag=1; }
		}
		if(!flag) break;
	}
	int o=0;
	for(auto i:z) if(!f[i]&&y[i]>y[o]) o=i;
//	printf("(%d) %d  %d %d\n",t,o,p[o],a[o][p[o]]);
//	for(auto i:z) printf("%d   %d %d\n",i,f[i],y[i]);
//	fr(i,1,m) printf("%d%c",id[i]?x[i]:0,i==m?'\n':' ');
	if(!o) return;
	int i=p[o];
	if(op[o][i]=='C')
	{
		a[o][i]--;
		if(!a[o][i]) p[o]++;
		if(p[o]>l[o]) ans[o]=t+1;
	}
	else
	{
		if(op[o][i]=='U') id[a[o][i]]=0;
		else id[a[o][i]]=o;
		p[o]++; if(p[o]>l[o]) ans[o]=t;
		work(t);
	}
}
int main()
{
	n=read(); m=read();
	fr(i,1,n)
	{
		s[i]=read(); b[i]=read(); l[i]=read(); p[i]=1;
		fr(j,1,l[i]){ op[i][j]=getchar(); a[i][j]=read(); if(op[i][j]=='L') x[a[i][j]]=std::max(x[a[i][j]],b[i]); }
	}
//	fr(i,1,m) printf("%d%c",x[i],i==m?'\n':' ');
	fr(i,0,210000) work(i);
	fr(i,1,n) printf("%d\n",ans[i]);
	return 0;
}
