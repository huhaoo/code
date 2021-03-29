/***************************************************************
	File name: gomuku.cpp
	Author: huhao
	Create time: Mon 16 Nov 2020 09:43:00 PM CST
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
#define io
#ifndef io
#include"gomoku.h"
#else
void output(int x,int y){ printf("%d %d\n",x,y); fflush(stdout); }
void input(int &x,int &y){ x=read(); y=read(); }
#endif
const int N=1010;
int x[N],y[N],t,a[N][N];
void input(){ t++; input(x[t],y[t]); if(x[t]==-1) return ; a[x[t]][y[t]]=1; }
void Sort(int l,int r)
{
	fr(i,l,r) fr(j,i+1,r) if(x[i]==x[j]?y[i]<y[j]:x[i]<x[j]); else{ std::swap(x[i],x[j]); std::swap(y[i],y[j]); }
}
void work()
{
	input(); // (10,10)
	output(5,5);
	input(); // (10 +/- 1,10 +/- 1)
	output(4,5);
	input(); // 3 black chain
	Sort(1,3);
	output(x[1]-(x[2]-x[1]),y[1]-(y[2]-y[1]));
	input();
	int k=1;
	if(x[4]==x[3]+x[3]-x[2]&&y[4]==y[3]+y[3]-y[2]) k=2;
	output(x[3]+(x[3]-x[2])*k,y[3]+(y[3]-y[2])*k);
	// defend part

	t=0; input(); //(3,5)/(6,5)
	if(x[t]==3)
	{
		output(5,4); input(); // (3,6)
		output(3,4); input(); // (3,7/8/9), next too.
		output(5,6); input();
		output(3,6+7+8+9-y[2]-y[3]-y[4]); input();
		if(!a[5][3]&&!a[5][7])
		{
			output(5,3); input();
			if(!a[5][7]) output(5,7);
			else output(5,2);
		}
		else
		{
			output(6,7); input();
			if(!a[7][8]) output(7,8);
			else output(2,3);
		}
	}
	else
	{
		output(4,4); input(); // (6,6)
		output(6,4); input(); // (6,7/8/9), next too.
		output(4,6); input();
		output(6,6+7+8+9-y[2]-y[3]-y[4]); input();
		if(!a[4][3]&&!a[4][7])
		{
			output(4,3); input();
			if(!a[4][7]) output(4,7);
			else output(4,2);
		}
		else
		{
			output(3,7); input();
			if(!a[2][8]) output(2,8);
			else output(7,3);
		}
	}
	input(); // (-1,-1)
}
#ifdef io
int main(){ work(); return 0; }
#endif
