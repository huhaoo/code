/**************************************************************
	File name: 1117.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 3/3/2019, 11:04:50 AM
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
#define N 300010
struct sa
{
	int n,m;
	int sa[N],r[N],t[N],p[N],a[N],h[N][20],b[N];
	char s[N];
	#define mem(a) memset(a,0,sizeof(a))
	void clear()
	{
		n=m=0;
		mem(sa);
		mem(r);
		mem(t);
		mem(p);
		mem(a);
		mem(h);
		mem(b);
		mem(s);
	}
	#undef mem
	void sort()
	{
		fr(i,1,n)
			t[r[i]]++;
		fr(i,2,m)
			t[i]+=t[i-1];
		fd(i,n,1)
			sa[t[r[p[i]]]--]=p[i];
		fr(i,1,m)
			t[i]=0;
	}
	int lcp(int x,int y)
	{
		x=r[x];
		y=r[y];
		if(x>y)
			swap(x,y);
		x++;
		int _b=b[y-x+1];
		return min(h[x][_b],h[y-(1<<_b)+1][_b]);
	}
	void calc()
	{
		fr(i,1,n)
		{
			r[i]=s[i]-'a'+1;
			p[i]=i;
			m=max(m,r[i]);
		}
		fr(i,2,n)
			b[i]=b[i>>1]+1;
		sort();
		fr(i,0,20)
		{
			int c=0;
			fr(j,1,(1<<i))
				p[++c]=n-j+1;
			fr(j,1,n)
				if(sa[j]-(1<<i)>0)
					p[++c]=sa[j]-(1<<i);
			sort();
			fr(j,1,n)
				a[j]=r[j];
			r[sa[1]]=m=1;
			fr(j,2,n)
			{
				if(a[sa[j]]!=a[sa[j-1]]||a[sa[j]+(1<<i)]!=a[sa[j-1]+(1<<i)])
					m++;
				r[sa[j]]=m;
			}
			if(m==n)
				break;
		}
		int k=0;
		fr(i,1,n)
		{
			if(k)
				k--;
			while(s[i+k]==s[sa[r[i]-1]+k])
				k++;
			h[r[i]][0]=k;
		}
		fr(j,1,15)
			fr(i,1,n)
				h[i][j]=min(h[i][j-1],h[i+(1<<(j-1))][j-1]);
	}
}sa,rs;
char c[N];
int T,n,x[N],y[N];
long long ans;
int main()
{
	T=read();
	while(T--)
	{
		scanf("%s",c);
		sa.clear();
		rs.clear();
		sa.n=rs.n=n=strlen(c);
		fr(i,1,n)
		{
			sa.s[i]=c[i-1];
			rs.s[i]=c[n-i];
		}
		sa.calc();
		rs.calc();
		fr(i,1,n+1)
			x[i]=y[i]=0;
		ans=0;
		fr(i,1,n/2)
			fr(j,2,n/i)
			{
				int a=(j-1)*i,b=j*i,c,d,e;
				c=min(sa.lcp(a,b),i);
				d=min(rs.lcp(n-b+2,n-a+2),i-1);
				e=c+d-i+1;
				if(c+d>=i)
				{
					x[a-d]++;
					x[a-d+e]--;
					y[b+c-e]++;
					y[b+c]--;
				}
			}
		fr(i,1,n)
		{
			x[i]+=x[i-1];
			y[i]+=y[i-1];
		}
		// fr(i,1,n)
			// printf("%d %d\n",y[i],x[i]);
		fr(i,1,n)
			ans+=y[i]*x[i+1];
		printf("%lld\n",ans);
	}
	return 0;
}