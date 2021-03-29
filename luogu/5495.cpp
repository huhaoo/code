/***************************************************************
	File name: 5495.cpp
	Author: huhao
	Create time: Mon 21 Oct 2019 08:18:38 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define u32 unsigned int
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
u32 read()
{
	u32 r=0,c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		r=r*10+c-48;
		c=getchar();
	}
	return r;
}
const int N=20000010,C=1000000;
int n;
u32 sed,a[N],ans;
int p[N],c,vis[N];
inline u32 getnext(){
	sed^=sed<<13;
	sed^=sed>>17;
	sed^=sed<<5;
	return sed;
}
int main()
{
	n=read();
	sed=read();
	fr(i,2,n)
	{
		if(!vis[i])
			p[++c]=i;
		int k=n/i;
		fr(j,1,c)
			if(p[j]<=k)
			{
				vis[i*p[j]]=1;
				if(i%p[j]==0)
					break;
			}
			else
				break;
	}
	fr(i,1,n)
		a[i]=getnext();
	fr(i,1,c)
		fr(j,1,n/p[i])
			a[j*p[i]]+=a[j];
	fr(i,1,n)
		ans^=a[i];
	printf("%u\n",ans);
	return 0;
}
