/**************************************************************
	File name: 1971.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/6/2018, 5:58:16 PM
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
namespace mainn
{
	#define N 50
	#define E 100010
	int n,m,q,a[N][N],cnt,x,y,num[N][N],e,begin[E],next[E],to[E],nn,p[E],vis[E],l[E],ans[E],ban[E];
	int mx[4]={0,0,1,-1},my[4]={1,-1,0,0};
	#define fo(i,a) for(int i=begin[a];i;i=next[i])
	void add(int u,int v)
	{
//		printf("%d %d\n",u,v);
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
	}
	int dfs(int u)
	{
		if(ban[u])return 0;
		vis[u]=1;
		fo(i,u)if(!ban[to[i]]&&!p[to[i]]){p[u]=to[i];p[to[i]]=u;return 1;}
		fo(i,u)
		{
			int v=to[i];
			if(ban[v])continue;
			if(!vis[p[v]]&&dfs(p[v]))
			{
				p[u]=v;
				p[v]=u;
				return 1;
			}
		}
		return 0;
	}
	char s[N];
	int main()
	{
		n=read();
		m=read();
		fr(i,1,n)
		{
			scanf("%s",s+1);
			fr(j,1,m)
				if(s[j]=='X')a[i][j]=1;
				else if(s[j]=='.')a[i][j]=1,x=i,y=j;
		}
		fr(i,1,n)
			fr(j,1,m)
				if(a[i][j]==1)
				{
					if((i+j-x-y)%2==0)
						num[i][j]=++cnt;
				}
		nn=cnt;
		fr(i,1,n)
			fr(j,1,m)
				if(a[i][j]==0)
				{
					if(((i+j-x-y)%2+2)%2==1)
						num[i][j]=++cnt;
				}
//		fr(i,1,n)
//			fr(j,1,m)
//				printf("%d%c",num[i][j],j==m?'\n':' ');
//		putchar(10);
		fr(i,1,n)
			fr(j,1,m)
				if(a[i][j]==1&&num[i][j])
					fr(k,0,3)
					{
						int xx=i+mx[k],yy=j+my[k];
						if(!num[xx][yy])continue;
						add(num[i][j],num[xx][yy]);
						add(num[xx][yy],num[i][j]);
					}
//		printf("%d %d\n",x,y);
//		fr(i,1,n)
//			fr(j,1,m)
//				printf("%d%c",num[i][j],j==m?'\n':' ');
		fr(i,1,nn)
			if(!p[i])
			{
				fr(j,1,cnt)vis[j]=0;
				dfs(i);
			}
//		fr(j,1,cnt)printf("%d%c",p[j],j==cnt?'\n':' ');
//		fr(i,1,n)
//			fr(j,1,m)
//				printf("%d%c",num[i][j]?c[num[i][j]]:2,j==m?'\n':' ');
//		putchar(10);
		q=read();
		fr(i,1,q)
		{
			int xx=read(),yy=read();
			ban[num[x][y]]=1;
			int f1=1,f2=1;
			if(p[num[x][y]])
			{
				int kk=p[num[x][y]];
				p[num[x][y]]=p[kk]=0;
				fr(j,1,cnt)vis[j]=0;
				if(dfs(kk))
					f1=0;
			}
			else
				f1=0;
			ban[num[xx][yy]]=1;
			if(p[num[xx][yy]])
			{
				int kk=p[num[xx][yy]];
				p[num[xx][yy]]=p[kk]=0;
				fr(j,1,cnt)vis[j]=0;
				if(dfs(kk))
					f2=0;
			}
			else
				f2=0;
			if(f1&&f2)ans[++ans[0]]=i;
			x=read();
			y=read();
		}
//		fr(i,1,n)
//			fr(j,1,m)
//				printf("%d%c",num[i][j]?c[num[i][j]]:2,j==m?'\n':' ');
		fr(i,0,ans[0])
			printf("%d\n",ans[i]);
		return 0;
	}
}
int main(){return mainn::main();}