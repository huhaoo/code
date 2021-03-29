/**************************************************************
	File name: 5056.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2/22/2019, 2:59:21 PM
	Example:
	- luogu5056 https://www.luogu.org/problemnew/show/P5056
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
#define N 15
#define M 10000000ll
int p[N],n,m,_x,_y;
char s[N][N];
#include<map>
map<long long,long long>f;
long long calc(int x,int y,int g)
{
	long long h=x*M*M+y*M+g,r=0,_g=0,cnt=1;
	if(f.count(h))
		return f[h];
	if(s[x][y]=='*')
	{
		if(!(g/p[y-1]%9))
		{
			if(y!=m)
				r=calc(x,y+1,g);
			else
				r=calc(x+1,1,g*3);
		}
		else
			r=0;
	}
	else if(x==_x&&y==_y)
	{
		if(!(g-7*p[y-1]))
			r=1;
	}
	else
		switch(g/p[y-1]%9)
		{
			case 0:
			{
				_g=g+p[y-1]+2*p[y];
				if(y!=m)
					r+=calc(x,y+1,_g);
				break;
			}
			case 4:
			{
				_g=g-4*p[y-1];
				fr(i,y+2,m)
					if(g/p[i-1]%3==1)
						cnt++;
					else if(g/p[i-1]%3==2)
					{
						cnt--;
						if(!cnt)
						{
							_g-=p[i-1];
							break;
						}
					}
				if(y!=m)
					r+=calc(x,y+1,_g);
				break;
			}
			case 8:
			{
				_g=g-8*p[y-1];
				fd(i,y-1,1)
					if(g/p[i-1]%3==2)
						cnt++;
					else if(g/p[i-1]%3==1)
					{
						cnt--;
						if(!cnt)
						{
							_g+=p[i-1];
							break;
						}
					}
				if(y!=m)
					r+=calc(x,y+1,_g);
				else
					r+=calc(x+1,1,_g*3);
				break;
			}
			case 5:
			{
				_g=g-5*p[y-1];
				if(y!=m)
					r+=calc(x,y+1,_g);
				break;
			}
			case 1:
			case 2:
			{
				int k=g/p[y-1]%3;
				_g=g-k*p[y-1];
				if(y!=m)
				{
					r+=calc(x,y+1,_g+k*p[y-1]);
					r+=calc(x,y+1,_g+k*p[y]);
				}
				else
				{
					r+=calc(x+1,1,(_g+k*p[y-1])*3);
				}
				break;
			}
			case 3:
			case 6:
			{
				int k=g/p[y]%3;
				_g=g-k*p[y];
				if(y!=m)
				{
					r+=calc(x,y+1,_g+k*p[y-1]);
					r+=calc(x,y+1,_g+k*p[y]);
				}
				else
				{
					r+=calc(x+1,1,(_g+k*p[y-1])*3);
				}
				break;
			}
		}
//	printf("%d %d %d %lld\n",x,y,g,r);
	return f[h]=r;
}
int main()
{
	n=read();
	m=read();
	fr(i,1,n)
	{
		scanf("%s",s[i]+1);
		fr(j,1,m)
			if(s[i][j]=='.')
			{
				_x=i;
				_y=j;
			}
	}
	if(!_x&&!_y)
	{
		printf("1\n");
		return 0;
	}
	p[0]=1;
	fr(i,1,m+1)
		p[i]=p[i-1]*3;
	printf("%lld\n",calc(1,1,0));
	return 0;
}