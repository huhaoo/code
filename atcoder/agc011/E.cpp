/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Tue 23 Feb 2021 03:56:47 PM CST
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
const int N=5000010;
int n,m;
char s[N];
int a[N],b[N],c;
int main()
{
	scanf("%s",s+1); n=strlen(s+1); m=n*10;
	fr(i,1,n) a[i]=s[n-i+1]-48;
	fr(i,1,n) a[i]*=9;
	fr(i,1,n){ a[i+1]+=a[i]/10; a[i]%=10; }
	while(a[n+1]){ n++; a[n+1]+=a[n]/10; a[n]%=10; }
	fr(i,1,n) c+=a[i];
	b[0]=c;
	fr(i,1,m)
	{
		a[1]++; c++;
		for(int j=1;a[j]==10;j++){ a[j]=0; a[j+1]++; c-=9; }
		b[i]=c;
	}
	fr(i,0,n) if(i*9>=b[i*9]){ printf("%d\n",i); return 0; }
	return 0;
}
