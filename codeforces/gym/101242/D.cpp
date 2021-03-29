/***************************************************************
	File name: D.cpp
	Author: huhao
	Create time: Thu 12 Nov 2020 08:17:14 PM CST
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
const int N=110;
const char show[N][N]=
{
".XX...XX.....XX...XX.",
"X..X.X..X...X..X.X..X",
"X..X.X..X.X.X..X.X..X",
".XX...XX.....XX...XX.",
"X..X.X..X.X.X..X.X..X",
"X..X.X..X...X..X.X..X",
".XX...XX.....XX...XX.",
};
const char number[11][N][N]=
{
	{
		".XX.",
		"X..X",
		"X..X",
		"....",
		"X..X",
		"X..X",
		".XX."
	},

	{
		"....",
		"...X",
		"...X",
		"....",
		"...X",
		"...X",
		"...."
	},

	{
		".XX.",
		"...X",
		"...X",
		".XX.",
		"X...",
		"X...",
		".XX."
	},

	{
		".XX.",
		"...X",
		"...X",
		".XX.",
		"...X",
		"...X",
		".XX."
	},

	{
		"....",
		"X..X",
		"X..X",
		".XX.",
		"...X",
		"...X",
		"...."
	},

	{
		".XX.",
		"X...",
		"X...",
		".XX.",
		"...X",
		"...X",
		".XX."
	},

	{
		".XX.",
		"X...",
		"X...",
		".XX.",
		"X..X",
		"X..X",
		".XX."
	},

	{
		".XX.",
		"...X",
		"...X",
		"....",
		"...X",
		"...X",
		"...."
	},

	{
		".XX.",
		"X..X",
		"X..X",
		".XX.",
		"X..X",
		"X..X",
		".XX."
	},

	{
		".XX.",
		"X..X",
		"X..X",
		".XX.",
		"...X",
		"...X",
		".XX."
	},

	{
		"....",
		"....",
		"....",
		"....",
		"....",
		"....",
		"...."
	}
};
#include<vector>
char s[N][N][N],c[60*24+10][N][N];
int ans[N][N],flag,n;
int main()
{
	n=read();
	fr(i,0,n-1) fr(j,0,6) scanf("%s",s[i][j]);
	fr(i,0,23) fr(j,0,59)
	{
		int id=i*60+j;
		int a[4]={i/10,i%10,j/10,j%10};
		if(a[0]==0) a[0]=10;
		fr(j,0,6) fr(k,0,20) c[id][j][k]='.';
		fr(j,0,3)
		{
			int p=(std::vector<int>({0,5,12,17})[j]);
			fr(x,0,6) fr(y,0,3) c[id][x][p+y]=number[a[j]][x][y];
		}
		c[id][2][10]=c[id][4][10]='X';
	}
	fr(i,0,6) fr(j,0,20) ans[i][j]=2;
	fr(t,0,24*60-1)
	{
		int Flag=1;
		static int Ans[N][N];
		fr(i,0,6) fr(j,0,20) Ans[i][j]=2;
		fr(T,0,n-1)
		{
			int _t=(t+T)%(24*60);
			fr(i,0,6) fr(j,0,20) if(s[T][i][j]!=c[_t][i][j])
			{
				int a=(s[T][i][j]=='.'?0:1);
				Ans[i][j]=a;
			}
		}
		fr(T,0,n-1)
		{
			int _t=(t+T)%(24*60);
			fr(i,0,6) fr(j,0,20) if(Ans[i][j]!=2)
			{
				int a=(s[T][i][j]=='.'?0:1);
				if(Ans[i][j]!=a) Flag=0;
			}
		}
/*		printf("%d\n",Flag);
		fr(i,0,6)
		{
			fr(j,0,20) printf("%c",c[t][i][j]);
			putchar(10);
		}
		break;*/
		if(Flag)
		{
			fr(i,0,6) fr(j,0,20)
			{
				int _flag=0;
				fr(T,1,n-1) if(s[T][i][j]!=s[0][i][j]) _flag=1;
				if(_flag) Ans[i][j]=-1;
			}
			if(!flag)
			{
				flag=1;
				fr(i,0,6) fr(j,0,20) ans[i][j]=Ans[i][j]==2?3:Ans[i][j];
			}
			else
			{
				fr(i,0,6) fr(j,0,20)
				{
					if(ans[i][j]==3||Ans[i][j]==2) ans[i][j]=3;
					else if(ans[i][j]==2) ans[i][j]=Ans[i][j];
					else if(ans[i][j]!=Ans[i][j]) ans[i][j]=3;
				}
			}
/*			fr(i,0,6)
			{
				fr(j,0,20) printf("%d ",Ans[i][j]);
				putchar(10);
			}
			break;*/
		}
	}
/*	fr(i,0,6)
	{
		fr(j,0,20) printf("%d ",ans[i][j]);
		putchar(10);
	}*/
	if(flag)
	{
		fr(i,0,6)
		{
			fr(j,0,20)
				if(show[i][j]=='.') putchar('.');
				else putchar(ans[i][j]==-1?'W':ans[i][j]>=2?'?':ans[i][j]+48);
			putchar(10);
		}
	}
	else printf("impossible\n");
	return 0;
}
