/***************************************************************
	File name: alice.cpp
	Author: huhao
	Create time: Tue 16 Jun 2020 06:27:38 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
const int N=2010;
int n,m,l,P[N];
char S[N],s[N];
char c[N];
int main()
{
	FILE *in=fopen("alice.in","r");
	fscanf(in,"%d%d%s",&n,&m,S); srand(998244353);
	fr(i,0,n+n-1) P[i]=i;
	std::random_shuffle(P,P+n+n);
	fr(i,0,n+n-1) s[P[i]]=S[i];
	fr(i,n+n,N-1) s[i]='0';
	l=(n+n+2)/3*2;
	fr(i,0,l-1) c[i]=getchar();
//	fprintf(stderr,"S: %s\ns: %s\n",S,s);
	fr(i,0,l-1) c[i]-='0';
	fr(i,0,l/2)
		if((c[i<<1]<<1)+c[i<<1|1]==3)
			printf("%c%c%c",s[i*3],s[i*3+1],s[i*3+2]);
		else
			printf("%c",s[i*3+(c[i<<1]<<1)+c[i<<1|1]]);
	fflush(stdout);
	return 0;
}
