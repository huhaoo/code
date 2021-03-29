/***************************************************************
	File name: kebab.cpp
	Author: huhao
	Create time: Wed 30 Dec 2020 02:35:52 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
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
const int N=500010,mod=1000000007;
int m,n,id[N],t,a[N],b[N],ans;
int f[2][500][500];
void Add(int &a,int b){ a=(a+b); if(a>=mod) a-=mod; }
int main()
{
	freopen("kebab.in","r",stdin); freopen("kebab.out","w",stdout);
	m=read(); t=read();
	fr(i,1,m)
	{
		a[i]=read(); int B=a[i]-read();
		fr(j,1,a[i]){ n++; id[n]=i; b[n]=std::min(B,(a[i]-1)/(t+1)+1); }
	}
	f[0][t][0]=1;
	fr(i,1,n)
	{
		fr(j,0,t) fr(k,0,b[i]) f[i&1][j][k]=0;
		fr(j,0,t) fr(k,0,b[i-1])
		{
			int kk=(id[i-1]==id[i]?k:0);
			Add(f[i&1][std::min(j+1,t)][kk],f[(i&1)^1][j][k]);
			if(j==t&&kk!=b[i]) Add(f[i&1][0][kk+1],f[(i&1)^1][j][k]);
		}
//		printf("\n %d %d %d\n",i,b[i],id[i]);
//		fr(j,0,t) fr(k,0,b[i]) printf("%d%c",f[i][j][k],k==b[i]?'\n':' ');
	}
	fr(i,0,t) fr(j,0,b[n]) Add(ans,f[n&1][i][j]);
	printf("%d\n",ans);
	return 0;
}
