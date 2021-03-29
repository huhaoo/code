/***************************************************************
	File name: I.cpp
	Author: huhao
	Create time: Wed 14 Oct 2020 03:03:45 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
#include<vector>
#include<map>
const int M=9,N=30;
struct opt
{
	std::vector<int> op,a,b;
	opt(){ op=a=b=std::vector<int>(0); }
	void add(int Op,int A=0,int B=0){ op.push_back(Op); a.push_back(A); b.push_back(B); }
	int empty(){ return op.empty(); }
} ;
#define u64 unsigned long long
struct sudoku
{
	int a[M][M];
	sudoku(){ memset(a,0,sizeof(a)); }
	int *operator[](int p){ return a[p]; }
	sudoku r(int x,int y)
	{
		fr(i,0,8) std::swap(a[x][i],a[y][i]);
		return *this;
	}
	sudoku R(int x,int y)
	{
		fr(i,0,2) r(3*x+i,3*y+i);
		return *this;
	}
	sudoku F()
	{
		fr(i,0,8) fr(j,i+1,8) std::swap(a[i][j],a[j][i]);
		return *this;
	}
	sudoku D(int x,int y)
	{
		fr(i,0,8) fr(j,0,8)
			if(a[i][j]==x) a[i][j]=y;
			else if(a[i][j]==y) a[i][j]=x;
		return *this;
	}
	sudoku D(opt &o)
	{
		int c=0;
		fr(i,0,8) fr(j,0,8) if(a[i][j]>c){ c++; if(a[i][j]!=c){ o.add('D',a[i][j],c); D(a[i][j],c); } }
		return *this;
	}
	u64 hash()
	{
		u64 ans=0,sed=10007;
		fr(i,0,8) fr(j,0,8) ans=ans*sed+a[i][j];
		return ans;
	}
} a[N];
int operator<(sudoku a,sudoku b)
{
	fr(i,0,8) fr(j,0,8) if(a[i][j]!=b[i][j]) return a[i][j]<b[i][j];
	return 0;
}
opt operator+(opt a,opt b)
{
	fr(i,0,b.a.size()-1)
	{
		a.op.push_back(b.op[i]);
		a.a.push_back(b.a[i]);
		a.b.push_back(b.b[i]);
	}
	return a;
}
opt rev(opt a)
{
	std::reverse(a.op.begin(),a.op.end());
	std::reverse(a.a.begin(),a.a.end());
	std::reverse(a.b.begin(),a.b.end());
	return a;
}
opt ans[N][N];
std::map<u64,opt> m[N];
int n;
int main()
{
	freopen("intellectual.in","r",stdin); freopen("intellectual.out","w",stdout);
	n=read();
	fr(t,1,n)
	{
		fr(i,0,8)
		{
			static char s[N];
			scanf("%s",s);
			fr(j,0,8) a[t][i][j]=(s[j]=='.'?0:s[j]-48);
		}
	}
	fd(t,n,1)
	{
		fr(x,0,5) fr(y,0,5) fr(z,0,5) fr(w,0,5) fr(f,0,1) fr(_f,0,1) if(!(f&_f))
		{
			sudoku r=a[t]; opt op;

			if(_f){ r.F(); op.add('F'); }

			if(x&1){ r.r(0,1); op.add('r',0,1); }
			if(x&2){ r.r(0,2); op.add('r',0,2); }
			if(x&4){ r.r(1,2); op.add('r',1,2); }

			if(y&1){ r.r(3,4); op.add('r',3,4); }
			if(y&2){ r.r(3,5); op.add('r',3,5); }
			if(y&4){ r.r(4,5); op.add('r',4,5); }

			if(z&1){ r.r(6,7); op.add('r',6,7); }
			if(z&2){ r.r(6,8); op.add('r',6,8); }
			if(z&4){ r.r(7,8); op.add('r',7,8); }

			if(w&1){ r.R(0,1); op.add('R',0,1); }
			if(w&2){ r.R(0,2); op.add('R',0,2); }
			if(w&4){ r.R(1,2); op.add('R',1,2); }
			fr(i,0,op.a.size()-1){ op.a[i]++; op.b[i]++; }

			if(f){ r.F(); op.add('F'); }

			r.D(op);

			if(!f) m[t][r.hash()]=rev(op);
			if(!_f) fr(T,t+1,n) if(ans[t][T].empty()&&m[T].count(r.hash())) ans[t][T]=op+m[T][r.hash()];
		}
	}
	fr(i,1,n) fr(j,i+1,n)
		if(ans[i][j].empty()) printf("No\n");
		else
		{
			printf("Yes\n%d\n",ans[i][j].a.size());
			fr(k,0,ans[i][j].a.size()-1)
				if(ans[i][j].op[k]=='F') printf("F\n");
				else printf("%c %d %d\n",ans[i][j].op[k],ans[i][j].a[k],ans[i][j].b[k]);
		}
	return 0;
}
