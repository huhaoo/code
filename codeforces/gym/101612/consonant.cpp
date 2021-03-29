/***************************************************************
	File name: consonant.cpp
	Author: huhao
	Create time: Wed 25 Nov 2020 04:34:01 PM CST
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
const int N=200;
char s[1000010];
int id[N],n,a[N][N];
int ans,Ans;
int main()
{
	freopen("consonant.in","r",stdin); freopen("consonant.out","w",stdout);
	fr(i,'a','z')
	{
		char c[10]="aeiouwy"; int flag=1;
		fr(j,0,6) if(i==c[j]) flag=0;
		if(flag) id[i]=n++;
		else id[i]=-1;
	}
	scanf("%s",s);
	fr(i,0,strlen(s)-2)
	{
		int u=id[s[i]],v=id[s[i+1]];
		if(u>=0&&v>=0){ a[u][v]++; a[v][u]++; }
	}
	fr(i,0,(1<<n)-1)
	{
		int v=0;
		fr(j,0,n-1) fr(k,0,n-1) if(((i>>j)&1)!=((i>>k)&1)) v+=a[j][k];
		if(v>ans){ ans=v; Ans=i; }
	}
	fr(i,0,strlen(s)-1) if(id[s[i]]>=0&&((Ans>>id[s[i]])&1)) s[i]+='A'-'a';
	printf("%s\n",s);
	return 0;
}
