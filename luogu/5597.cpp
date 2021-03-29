/***************************************************************
	File name: T103287.cpp
	Author: huhao
	Create time: Sun 20 Oct 2019 02:42:20 PM CST
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
#include<set>
const int N=2010;
int n,ans,Ans,s[N][2],R,cnt,f[N],a[N][N],m[N],op[N],O,v[N];
char c[N];
int build(int l,int r)
{
	int k=++cnt,p=l+1,w=1;
	if(c[l]=='0')
		;
	else if(c[l]=='1')
		s[k][0]=build(l+1,r);
	else if(c[l]=='2')
		s[k][1]=build(l+1,r);
	else
	{
		while(w+=v[c[p]])
			p++;
		s[k][0]=build(l+1,p);
		s[k][1]=build(p+1,r);
	}
	return k;
}
int calc(int k)
{
	int ans=1;
	m[k+1]=0;
	fr(i,1,m[k])
		if(s[a[k][i]][0]&&!f[s[a[k][i]][0]])
			a[k+1][++m[k+1]]=s[a[k][i]][0];
	if(m[k+1])
		ans+=calc(k+1);
	m[k+1]=0;
	fr(i,1,m[k])
		if(s[a[k][i]][1]&&!f[s[a[k][i]][1]])
			a[k+1][++m[k+1]]=s[a[k][i]][1];
	if(m[k+1])
		ans+=calc(k+1);
	return ans;
}
void solve()
{
	fr(i,1,n)
		f[i]=0;
	int k=R;
	m[1]=0;
	while(k)
	{
		f[k]=1;
		a[1][++m[1]]=k;
		fr(i,1,O)
			k=s[k][op[i]];
	}
	ans=min(ans,2*calc(1)-O);
}
void dfs(int k)
{
	if(!k)
		return;
	if(O)
		solve();
	O++;
	op[O]=0;
	dfs(s[k][0]);
	op[O]=1;
	dfs(s[k][1]);
	O--;
}
int main()
{
	scanf("%s",c+1);
	v['0']=-1;
	v['3']=1;
	n=strlen(c+1);
	R=build(1,n);
	ans=n*2;
	dfs(1);
	printf("%d\n",ans);
	return 0;
}
