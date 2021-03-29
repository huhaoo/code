/***************************************************************
	File name: java2016.cpp
	Author: huhao
	Create time: Mon 23 Nov 2020 09:12:06 PM CST
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
int n;
int main()
{
	freopen("java2016.in","r",stdin); freopen("java2016.out","w",stdout);
	printf("a = ? max ?\n");
	fr(i,1,17) printf("%c = %c max %c\n",'a'+i,'a'+i-1,'a'+i-1);
	printf("%c = %c / %c\n",'a'+18,'a'+17,'a'+17);
	fr(i,19,25) printf("%c = %c + %c\n",'a'+i,'a'+i-1,'a'+i-1);
	n=read();
	if(n==0){ printf("r - r\n"); return 0; }
	int flag=0;
	fr(i,0,7) if((n>>i)&1)
	{
		if(flag) printf("+ ");
		flag=1;
		printf("%c ",'a'+i+18);
	}
	putchar(10);
	return 0;
}
