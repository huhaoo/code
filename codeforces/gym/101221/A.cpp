/***************************************************************
	File name: A.cpp
	Author: huhao
	Create time: Mon 12 Oct 2020 03:37:44 PM CST
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
const int N=1010;
char s[N];
int n,lst;
inline void move(int a,int b)
{
	printf("%d to %d\n",a,b);
	a+=n+n; b+=n+n;
	assert(s[a]!=' '&&s[a+1]!=' '&&s[b]==' '&&s[b+1]==' '&&a>0&&b>0&&a<n*4&&b<n*4);
	std::swap(s[a],s[b]); std::swap(s[a+1],s[b+1]);
}
void move(int a){ move(a,lst); lst=a; }
int main() 
{
	n=read();
	fr(i,1,n+n) s[i]=' ';
	fr(i,1,n+n) s[i+n+n]='a'+(i&1);
	lst=-1;
	switch(n&3)
	{
		case 0:
		{
			fr(i,0,n/4-1){ move(n+2+i*4); move(3+i*4); }
			fr(i,0,n/4-1){ move(i*4); move(n+3+i*4); }
			break;
		}
		case 1:
		{
			fr(i,0,n/4-1){ move(n+3+i*4); move(3+i*4); }
			move(n+1);
			fr(i,0,n/4-1){ move(i*4); move(n+4+i*4); }
			break;
		}
		case 2:
		{
			static char c[N]; int C=0;
			fr(i,1,n+n-2) c[++C]=' ';
			c[++C]='a'; c[++C]='b'; c[++C]='b';
			fr(i,1,(n-6)/4){ c[++C]='a'; c[++C]='b'; c[++C]='b'; c[++C]='a'; }
			c[++C]=' '; c[++C]=' '; c[++C]='a'; c[++C]='b'; c[++C]='a'; c[++C]='a';
			fr(i,1,(n-6)/4){ c[++C]='b'; c[++C]='b'; c[++C]='a'; c[++C]='a'; }
			fr(i,0,2) c[++C]='b';
			fr(i,0,1) c[++C]='a';
			static int s1[N],s2[N]; int t1=0,t2=0;
			fr(i,n+n,n*4-1) if(i!=n*3-4&&s[i]!=c[i]&&s[i+1]!=c[i+1])
			{
				if(s[i]=='a') s1[++t1]=i;
				else s2[++t2]=i;
				i++;
			}
			fr(i,1,t2){ move(s1[i]-n-n); move(s2[i]-n-n); }
			move(n-4);
			C=0;
			fr(i,1,n+n-2) c[++C]=' ';
			fr(i,1,n) c[++C]='a';
			fr(i,1,n) c[++C]='b';
			c[++C]=' '; c[++C]=' ';
			t1=t2=0;
			fr(i,1,n*4-1) if(s[i]!=c[i]&&s[i+1]!=c[i+1]&&s[i]!=' ')
			{
				if(s[i]=='a') s1[++t1]=i;
				else s2[++t2]=i;
				i++;
			}
			fr(i,1,t2){ move(s1[i]-n-n); move(s2[i]-n-n); }
			move(s1[t1]-n-n);
			break;
		}
		case 3:
		{
			move(n-1);
			fr(i,0,n/4-1){ move(3+i*4); move(n+3+i*4); }
			move(n+n-1); move(n,-3); lst=n;
			fr(i,0,n/4-1){ move(i*4); move(4+n+i*4); }
			break;
		}
	}
//	printf("%s\n",s+1);
	return 0;
}
