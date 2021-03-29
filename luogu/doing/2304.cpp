/***************************************************************
	File name: 2304.cpp
	Author: huhao
	Create time: Wed 05 Jun 2019 09:00:16 AM CST
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
#include<map>
namespace run
{
	const int N=300010,inf=15<<26;
	int n,t[N][5],f[N],m[N],mm[N],lm[N],rm[N],p[N],ans,_p,l[N],r[N],s[N],begin[N],next[N],to[N],e,w[N],d[N],S,T,vis[N],q[N],dis[N],c[N],_c[N];
	void add(int u,int v,int _w)
	{
		e++;
		if(_w)
			printf("%d %d %d\n",u,v,_w);
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
		w[e]=_w;
	}
	struct point
	{
		int x,y,id;
		point(int _x=0,int _y=0,int _id=0)
		{
			x=_x;
			y=_y;
			id=_id;
		}
	}a[N];
	int cmp(point a,point b)
	{
		return a.y==b.y?a.x<b.x:a.y<b.y;
	}
	map<int,int>m1,m2,m3;
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	int bfs(int S,int T)
	{
		int l=1,r=1;
		memset(vis,0,sizeof(vis));
		q[r]=T;
		vis[T]=1;
		dis[T]=0;
		while(l<=r)
		{
			int u=q[l];
			l++;
			fo(i,u)
				if(w[i^1]&&!vis[to[i]])
				{
					dis[to[i]]=dis[u]+1;
					vis[to[i]]=1;
					q[++r]=to[i];
				}
		}
		return vis[S];
	}
	int dfs(int u,int T,int mf)
	{
		if(u==T)
			return mf;
		int ans=0;
		fo(i,u)
			if(w[i]&&dis[u]==dis[to[i]]+1)
			{
				int f=dfs(to[i],T,mf);
				if(!f)
					continue;
				w[i]-=f;
				w[i^1]+=f;
				mf-=f;
				ans+=f;
			}
		return ans;
	}
	int main()
	{
		n=read();
		fr(i,1,n)
		{
			a[i].x=read();
			a[i].y=read();
			a[i].id=i;
		}
		a[++n]=point(0,0,0);
		sort(a+1,a+n+1,cmp);
		fr(i,1,n)
		{
			int k;
			if((k=m1[a[i].x-a[i].y]))
				t[i][++t[i][0]]=k;
			if((k=m2[a[i].x]))
				t[i][++t[i][0]]=k;
			if((k=m3[a[i].x+a[i].y]))
				t[i][++t[i][0]]=k;
			m1[a[i].x-a[i].y]=i;
			m2[a[i].x]=i;
			m3[a[i].x+a[i].y]=i;
		}
		fr(i,2,n)
			f[i]=m[i]=-inf;
		ans=1;
		_p=1;
		for(int i=2,j;i<=n;i=j+1)
		{
			j=i;
			while(a[j+1].y==a[i].y)
				j++;
			fr(k,i,j)
			{
				l[k]=i;
				r[k]=j;
			}
			fr(k,i,j)
			{
				fr(o,1,t[k][0])
					if(f[k]<m[t[k][o]]&&m[t[k][o]]>=0)
					{
						f[k]=m[t[k][o]];
						p[k]=t[k][o];
					}
			}
			int _m=-inf,pm=0;
			fr(k,i,j)
			{
				if(f[k]+1>_m+k-i+1)
				{
					if(m[k]<f[k]+1)
					{
						m[k]=f[k]+1;
						mm[k]=k;
					}
				}
				else
				{
					if(m[k]<_m+k-i+1)
					{
						m[k]=_m+k-i+1;
						mm[k]=pm;
					}
				}
				if(f[k]>_m)
				{
					_m=f[k];
					pm=k;
				}
			}
			_m=-inf;
			pm=0;
			fd(k,j,i)
			{
				if(f[k]+1>_m+j-k+1)
				{
					if(m[k]<f[k]+1)
					{
						m[k]=f[k]+1;
						mm[k]=k;
					}
				}
				else
				{
					if(m[k]<_m+j-k+1)
					{
						m[k]=_m+j-k+1;
						mm[k]=pm;
					}
				}
				if(f[k]>_m)
				{
					_m=f[k];
					pm=k;
				}
			}
			fr(k,i,j)
				if(f[k]+j-i+1>ans)
				{
					ans=f[k]+j-i+1;
					_p=k;
				}
		}
		s[0]=0;
		fr(i,l[_p],_p-1)
			s[++s[0]]=a[i].id;
		fd(i,r[_p],_p)
			s[++s[0]]=a[i].id;
		_p=p[_p];
		while(a[_p].id)
		{
			if(mm[_p]<_p)
			{
				fd(i,_p,mm[_p]+1)
					s[++s[0]]=a[i].id;
				fr(i,l[_p],mm[_p])
					s[++s[0]]=a[i].id;
			}
			else if(mm[_p]==_p)
			{
				s[++s[0]]=a[_p].id;
			}
			else
			{
				fr(i,_p,mm[_p]-1)
					s[++s[0]]=a[i].id;
				fd(i,r[_p],mm[_p])
					s[++s[0]]=a[i].id;
			}
			_p=p[mm[_p]];
		}
		printf("%d\n",ans);
		while(s[0])
		{
			printf("%d",s[s[0]]);
			s[0]--;
			putchar(s[0]?' ':'\n');
		}
		n++;
		e=1;
		fr(i,2,n)
			if(m[i]+r[i]-l[i]+1==ans)
				c[i]=1;
		for(int i=n,j;i>1;i--)
		{
			j=i;
			i=l[i];
			fr(k,i,j)
				if(c[k]&&m[k]==f[k]+1)
					_c[k]=1;
			int _m=inf;
			fr(k,i,j)
			{
				if(f[k]>=_m)
					_c[k]=1;
				if(c[k])
					_m=min(_m,m[k]-k+i-1);
			}
			_m=inf;
			fd(k,j,i)
			{
				if(f[k]>=_m)
					_c[k]=1;
				if(c[k])
					_m=min(_m,m[k]-j+k-1);
			}
			fr(k,i,j)
				if(_c[i])
					fr(o,1,t[k][0])
						if(m[t[k][o]]>=f[k])
						{
							printf("%d %d\n",a[t[k][o]].id,a[k].id);
							c[t[k][o]]=1;
							d[k]++;
							d[t[k][o]]--;
							add(t[k][o],k,inf);
							add(k,t[k][o],0);
						}
		}
		fr(i,2,n)
			fr(j,1,t[i][0])
			{
				add(t[i][j],i,inf);
				add(i,t[i][j],0);
			}
		add(n,1,inf);
		add(1,n,0);
		int p_=e,_ans=0;
		S=n+1;
		T=n+2;
		fr(i,1,n)
			if(d[i]>0)
			{
				add(i,T,d[i]);
				add(T,i,0);
			}
			else if(d[i]<0)
			{
				add(S,i,-d[i]);
				add(i,S,0);
			}
		while(bfs(S,T))
			_ans+=dfs(S,T,inf);
		w[p_]=0;
		w[p_^1]=0;
		while(bfs(n,1))
			_ans-=dfs(n,1,inf);
		printf("%d\n",_ans);
		return 0;
	}
}
int main()
{
	return run::main();
}
