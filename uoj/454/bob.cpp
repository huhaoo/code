/***************************************************************
	File name: bob.cpp
	Author: huhao
	Create time: Tue 16 Jun 2020 06:33:38 PM CST
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
int n,m,a[N],l,b[N];
char s[N],c[N];
int P[N];
int main()
{
	FILE *in=fopen("bob.in","r"),*out=fopen("bob.out","w");
	fscanf(in,"%d%d",&n,&m); srand(998244353);
	fr(i,0,n+n-1) P[i]=i;
	std::random_shuffle(P,P+n+n);
	fr(i,0,n-1)
	{
		int A;
		fscanf(in,"%d",&A); A--; a[P[A]]=1; b[P[A]]=i;
	}
	l=(n+n+2)/3;
	fr(i,0,l-1)
	{
		int I=i*3;
		if(a[I]+a[I+1]+a[I+2]>=2) printf("11");
		else if(a[I]) printf("00");
		else if(a[I+1]) printf("01");
		else printf("10");
	}
	fflush(stdout);
	scanf("%s",s); char *S=s;
	fr(i,0,l-1)
	{
		int I=i*3;
		if(a[I]+a[I+1]+a[I+2]>=2)
		{
			if(a[I]) c[b[I]]=*S;
			if(a[I+1]) c[b[I+1]]=*(S+1);
			if(a[I+2]) c[b[I+2]]=*(S+2);
			S+=2;
		}
		else if(a[I]||a[I+1]||a[I+2]) c[b[I]+b[I+1]+b[I+2]]=*S;
		S++;
	}
	fprintf(out,"%s\n",c);
//	fprintf(stderr,"%s\n",c);
	return 0;
}
