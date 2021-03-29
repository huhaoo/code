/**************************************************************
	File name: 2147.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/16/2018, 3:53:19 PM
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
template<class t,int _size,t (*opt)(t a,t b)>
class LCT
{
	private:
	#define size (_size+1)
		int s[size][2],rev[size],f[size],q[size],cnt;
		t v[size],sum[size];
	#undef size
		int isroot(int k){return s[f[k]][0]!=k&&s[f[k]][1]!=k;}
		int wson(int k){return s[f[k]][1]==k;}
		void update(int k){sum[k]=opt(v[k],opt(sum[s[k][0]],sum[s[k][1]]));}
		void reverse(int k)
		{
			if(rev[k])
			{
				rev[s[k][0]]^=1;rev[s[k][1]]^=1;rev[k]=0;
				swap(s[k][0],s[k][1]);
			}
		}
		void rorate(int k)
		{
			if(isroot(k))return;
			int ff=f[k],o=wson(k);
			if(!isroot(ff))s[f[ff]][wson(ff)]=k;
			f[k]=f[ff];f[ff]=k;f[s[k][o^1]]=ff;
			s[ff][o]=s[k][o^1];s[k][o^1]=ff;
			update(ff);update(k);
		}
		void splay(int k)
		{
			int i=k;q[cnt=1]=k;
			while(!isroot(i)){q[++cnt]=f[i];i=f[i];}
			while(cnt){reverse(q[cnt]);cnt--;}
			while(!isroot(k))
			{
				int ff=f[k];
				if(!isroot(ff))rorate((wson(ff)==wson(k))?ff:k);
				rorate(k);
			}
		}
		void access(int k)
		{
			int l=0;
			while(k)
			{
				splay(k);
				s[k][1]=l;update(k);
				l=k;k=f[k];
			}
		}
		void makeroot(int k){access(k);splay(k);rev[k]^=1;}
		int findroot(int k)
		{
			access(k);splay(k);reverse(k);
			while(s[k][0])
			{
				k=s[k][0];
				reverse(k);
			}
			return k;
		}
		void split(int u,int v)
		{
			makeroot(u);
			access(v);
		}
	public:
		int query(int u,int v)
		{
			makeroot(u);
			if(findroot(v)==u)return 1;
			return 0;
		}
		int link(int u,int v)
		{
			makeroot(u);
			if(findroot(v)==u)return 1;
			f[u]=v;
			return 0;
		}
		//1:u,v in a tree
		int cut(int u,int v)
		{
			makeroot(u);
			if(findroot(v)!=u)return 1;
			if(f[u]!=v||s[u][1])return 1;
			f[u]=s[v][0]=0;
			return 0;
		}
		//1:(u,v) not in E
		void modfiy(int k,t val)
		{
			splay(k);v[k]=val;
			update(k);
		}
	#define mem(k) memset(k,0,sizeof(k))
		LCT()
		{
			mem(s);mem(rev);mem(f);mem(q);cnt=0;
			mem(v);mem(sum);
		}
		void clear(){LCT();}
	#undef mem
};
int opt(int a,int b){return a+b;}
LCT<int,10010,opt>a;
int q;
char s[110];
int main()
{
	read();q=read();
	while(q--)
	{
		scanf("%s",s);int u=read(),v=read();
		if(!strcmp(s,"Query")){if(a.query(u,v))printf("Yes\n");else printf("No\n");}
		if(!strcmp(s,"Connect"))a.link(u,v);
		if(!strcmp(s,"Destroy"))a.cut(u,v);
	}
	return 0;
}