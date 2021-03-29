/***************************************************************
	File name: main.cpp
	Author: huhao
	Create time: Sun 20 Oct 2019 03:19:19 PM CST
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
int main()
{
	int opt=read();
	if(opt==1)
		printf("3\n1 0 0 1 0\n1 1 0 0 0\n2 0.5 0.86602540378 0.5 -0.86602540378\n");
	else if(opt==2)
		printf("3\n1 0 0 5.23124577 4.31624417\n1 1 0 5.23124577 4.31624417\n2 5.23124577 4.31624417 5.23124577 -4.31624417\n");
	else if(opt==3)
		printf("5\n1 0 0 1 0\n1 1 0 0 0\n2 0.5 0.86602540 0.5 -0.86602540\n1 0.5 1 0.5 0\n2 1.4916198487 0.8708099243547 0.00838015129 0.129190075645\n");
	else if(opt==4)
		printf("10\n1 1 0 0 0\n1 2 0 0 0\n1 4 0 0 0\n1 8 0 0 0\n1 16 0 0 0\n1 32 0 0 0\n1 64 0 0 0\n1 128 0 0 0\n1 256 0 0 0\n1 512 0 0 0\n");
	else if(opt==5)
		printf("10\n1 1 0 0 0\n1 2 0 0 0\n1 4 0 0 0\n1 8 0 0 0\n1 16 0 0 0\n1 32 0 1 0\n1 63 0 1 0\n1 125 0 0 0\n1 250 0 0 0\n1 500 0 0 0\n");
	else if(opt==7)
		printf("5\n1 0 0 12.34441574 0\n1 12.34441574 0 0 0\n2 5.16457145 9.12243565 6.17220787 -10.690577625\n1 5.055779179 11.2616027 0 0\n2 12.34441574 0 -7.22494449 10.009234588\n");
	return 0;
}
