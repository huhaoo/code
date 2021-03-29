/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Tue 01 Dec 2020 04:09:01 PM CST
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
#include<queue>
const int N=1<<13|10;
int n,vis[N][N],a[N],s[N];
char ans[N];
int solve(int m,int l,int r)
{
	if(vis[m][r]) return 0;
//	printf("%d %d %d\n",m,l,r);
	if(m==n+1) return !l||!r||l==r;
	vis[m][r]=1;
	if((((l&(-l))==l&&l>r)&&solve(m,0,l+r))||(((r&(-r))==r&&r>l)&&solve(m,l+r,0))) return 1;
	if(!l||(l&(-l))>=a[m])
	{
		int L=l+a[m],R=r;
		if((L&(-L))==L&&(R&L)==L&&R-L<=L){ R-=L; L<<=1; }
		if(solve(m+1,L,R))
		{
			ans[m]='l';
			return 1;
		}
	}
	if(!r||(r&(-r))>=a[m])
	{
		int L=l,R=r+a[m];
		if((R&(-R))==R&&(R&L)==R&&L-R<=R){ L-=R; R<<=1; }
		if(solve(m+1,L,R))
		{
			ans[m]='r';
			return 1;
		}
	}
	return 0;
}
int main()
{
//	freopen("in","r",stdin);
	fr(T,1,read())
	{
		n=read();
		fr(i,1,n){ a[i]=read(); s[i]=s[i-1]+a[i]; }
//		printf("%d\n",n);
		fr(i,0,n+1) fr(j,0,s[n]) vis[i][j]=0;
		memset(ans,0,sizeof(ans));
		if((s[n]&(-s[n]))!=s[n]||!solve(1,0,0)) printf("no\n");
		else
		{
			printf("%s\n",ans+1);
			std::deque<int> q;
			fr(i,1,n)
				if(ans[i]=='l')
				{
					int v=a[i];
					while(!q.empty()&&q.front()==v){ q.pop_front(); v<<=1; }
					q.push_front(v);
				}
				else
				{
					int v=a[i];
					while(!q.empty()&&q.back()==v){ q.pop_back(); v<<=1; }
					q.push_back(v);
				}
			assert(q.size()==1);
//			while(!q.empty()){ printf("%d ",q.front()); q.pop_front(); }
//			putchar(10);
		}
	}
	return 0;
}
