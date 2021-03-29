/**************************************************************
	File name: 3695.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 11/18/2018, 1:43:29 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#include<map>
#include<string>
#define N 500010
map<string,int>t;
int v[N],n;
char *in,*l,*r;
void run(char *l,char *r);
int calc(char *l,char *r)//calc
{
	int s=0,op=1;
	while((*l<'a'||*l>'z')&&(*l<'0'||*l>'9'))
	{
		if(*l=='-')op=-1;
		l++;
	}
	while(l<=r)
	{
		while((*l<'a'||*l>'z')&&(*l<'0'||*l>'9'))l++;
		if(*l>='a'&&*l<='z')//var
		{
			int pos;
			string a;
			a.clear();
			while(*l>='a'&&*l<='z')
			{
				a.push_back(*l);
				l++;
			}
			pos=t[a];
			while(l<=r&&*l!='['&&*l!='+'&&*l!='-')
				l++;
			if(*l=='[')//array
			{
				l++;
				char *rr=l;
				while(*rr!=']')rr++;
				pos+=calc(l,rr-1);
				l=rr+1;
				while(l<=r&&*l!='+'&&*l!='-')l++;
			}
			s+=op*v[pos];
			if(*l=='+')op=1;
			if(*l=='-')op=-1;
		}
		else//const
		{
			int d=0;
			while(*l>='0'&&*l<='9')
			{
				d=d*10+*l-48;
				l++;
			}
			s+=op*d;
			while(l<r&&*l!='+'&&*l!='-')
				l++;
			if(*l=='+')op=1;
			if(*l=='-')op=-1;
		}
	}
	return s;
}
int cmp(char *l,char *r)
{
	char *p1,*p2;
	int a,b;
	p1=l;
	while(*p1!=',')p1++;
	p2=p1+1;
	while(*p2!=',')p2++;
	a=calc(p1+1,p2-1);
	b=calc(p2+1,r);
	while(*l!='l'&&*l!='g'&&*l!='e'&&*l!='n')l++;
	if(*l=='l')
	{
		if(*(l+1)=='e')
			return a<=b;
		return a<b;
	}
	else if(*l=='g')
	{
		if(*(l+1)=='e')
			return a>=b;
		return a>b;
	}
	else if(*l=='e')
		return a==b;
	return a!=b;
}
void run1(char *l,char *r)
{
	while(*l!='v'&&*l!='i'&&*l!='h'&&*l!='w')l++;
	if(*l=='v')//var
	{
		l+=4;
		while(l<r)
		{
			string a;
			a.clear();
			while(*l<'a'||*l>'z')l++;
			while(*l>='a'&&*l<='z')
			{
				a.push_back(*l);
				l++;
			}
			while(*l!='i'&&*l!='a')l++;
			if(*l=='i')//int
			{
				n++;
				t[a]=n;
				l+=3;
			}
			else if(*l=='a')//array
			{
				int lv=0,rv=0;
				while(*l<'0'||*l>'9')l++;
				while(*l>='0'&&*l<='9')
				{
					lv=lv*10+*l-48;
					l++;
				}//read a num
				while(*l<'0'||*l>'9')l++;
				while(*l>='0'&&*l<='9')
				{
					rv=rv*10+*l-48;
					l++;
				}//read the other num
				l++;
				t[a]=n-lv+1;
				n+=rv-lv+1;
			}
		}
	}
	else if(*l=='i')//ihu
	{
		l+=3;
		char *rr=l;
		while(*rr!=':'&&*rr!='{'&&*rr!='}')rr++;
		if(cmp(l,rr-1))
			run(rr,r);
	}
	else if(*l=='h')//hor
	{
		l+=3;
		char *p1,*p2,*p3;
		int pos,lv,rv;
		string a;
		a.clear();
		p1=l;
		while(*p1!=',')p1++;
		p2=p1+1;
		while(*p2!=',')p2++;
		p3=p2+1;
		while(*p3!=':'&&*p3!='{'&&*p3!='}')p3++;
		while(*l<'a'||*l>'z')l++;
		while(*l>='a'&&*l<='z')
		{
			a.push_back(*l);
			l++;
		}
		pos=t[a];
		lv=calc(p1+1,p2-1);
		rv=calc(p2+1,p3-1);
		for(v[pos]=lv;v[pos]<=rv;v[pos]++)
			run(p3,r);
	}
	else if(*l=='w')//while
	{
		l+=5;
		char *rr=l;
		while(*rr!=':'&&*rr!='{'&&*rr!='}')rr++;
		while(cmp(l,rr-1))
			run(rr,r);
	}
}
void run2(char *l,char *r)
{
	while(*l!='s'&&*l!='y')l++;
	if(*l=='y')//yosoro
	{
		l+=6;
		printf("%d ",calc(l,r));
	}
	else if(*l=='s')//set
	{
		int pos;
		string a;
		l+=3;
		a.clear();
		while(*l<'a'||*l>'z')l++;
		while(*l>='a'&&*l<='z')
		{
			a.push_back(*l);
			l++;
		}
		pos=t[a];
		while(*l!=','&&*l!='[')l++;
		if(*l=='[')//array
		{
			l++;
			char *rr=l;
			while(*rr!=']')rr++;
			pos+=calc(l,rr-1);
			l=rr+1;
		}
		while(*l!=',')l++;
		l++;
		v[pos]=calc(l,r);
/*		putchar(10);putchar(10);
		for(char *i=l;i<=r;i++)putchar(*i);
		putchar(10);
		printf("%d\n\n",v[pos]);*/
	}
}
int main()
{
	in=new char[1<<20|10];
	memset(in,0,sizeof(char[1<<20|10]));
	fread(in,1,1<<20,stdin);
	char *r=in;
	while(*r!=0)r++;
	run(in,r-1);
	return 0;
}
void run(char *ll,char *rr)
{
/*	putchar(10);
	for(char *i=ll;i<=rr;i++)putchar(*i);
	putchar(10);*/
	char *l,*r;
	int k=0;
	while(ll<=rr)
	{
		while(*ll!='{'&&*ll!=':'&&ll<=rr)ll++;
		if(*ll=='{')//var && hor && while && ihu
		{
			k=1;
			l=ll+1;
			while(k)
			{
				ll++;
				if(*ll=='{')k++;
				if(*ll=='}')k--;
			}
			r=ll-1;
			run1(l,r);
		}
		else if(*ll==':')//yoroso && set
		{
			l=ll+1;
			while(*ll!='\n'&&ll<=rr)ll++;
			r=ll-1;
			run2(l,r);
		}
	}
}