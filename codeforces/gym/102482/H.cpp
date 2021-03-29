/***************************************************************
	File name: H.cpp
	Author: huhao
	Create time: Sun 10 Jan 2021 03:44:46 PM CST
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
#include<set>
const int N=1<<22|10;
int n,w,h;
int l[N],r[N],m;
int Read()
{
	int x=read(),y=read();
	if(y==0) return x;
	if(x==w) return y+w;
	if(y==h) return w+h+w-x;
	if(x==0) return w+h+w+h-y;
	assert(false);
}
int id(int p)
{
	if(p<w)            return 1;
	else if(p<w+h)     return 2;
	else if(p<w+h+w)   return 3;
	else if(p<w+h+w+h) return 4;
	assert(false);
}
void Print(int p,char c)
{
	if(p<w)            printf("%.10lf %d",p+0.5,0);
	else if(p<w+h)     printf("%d %.10lf",w,p-w+0.5);
	else if(p<w+h+w)   printf("%.10lf %d",w-(p-w-h)-0.5,h);
	else if(p<w+h+w+h) printf("%d %.10lf",0,h-(p-w-h-w)-0.5);
	putchar(c);
}
std::set<int> L,R;
int p[N],mr;
int main()
{
	n=read(); w=read(); h=read();
	fr(i,1,n){ l[i]=Read(); r[i]=Read(); if(l[i]>r[i]) std::swap(l[i],r[i]); p[i]=i; }
	std::sort(p+1,p+n+1,[&](int a,int b){ return l[a]<l[b]; });
	mr=r[1];
	fr(i,2,n) mr=std::min(mr,r[i]);
	fr(i,1,n){ L.insert(l[i]); R.insert(r[i]); }
	int u=-1,v=-1;
	if(*--L.end()<*R.begin()){ u=0; v=*--L.end(); }
	else fr(i,1,n)
		if(l[p[i]]<mr)
		{
			L.erase(l[p[i]]); R.erase(r[p[i]]); L.insert(r[p[i]]);
			if(*--L.end()<*R.begin()){ u=l[p[i]]; v=*--L.end(); }
		}
		else break;
	if(u!=-1)
	{
		if(id(u)==id(v))
		{
			int p=id(u);
			if(p==1){ u=w+h+w+h-1; v=w; }
			else if(p==2){ u=w-1; v=w+h; }
			else if(p==3){ u=w+h-1; v=w+h+w; }
			else{ u=w+h+w-1; v=0; }
		}
//		printf("%d %d\n",u,v);
		printf("1\n");
		Print(u,' '); Print(v,'\n');
		return 0;
	}
	printf("2\n");
	Print(0,' '); Print(w+h,'\n');
	Print(w,' '); Print(w+h+w,'\n');
	return 0;
}
