#include<stdio.h>
#include<algorithm>
#include<vector>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
#include "dungeons.h"
#ifdef huhao
#include"grader.cpp"
#endif

namespace run
{
const int N=400010; const i64 INF=1ll<<60;
int t[9][14][N]; i64 d[9][14][N]; i64 m[9][14][N];
int n;
std::vector<int> s,p,w,l;
void init(int _n, std::vector<int> _s, std::vector<int> _p, std::vector<int> _w, std::vector<int> _l)
{
//	fprintf(stderr,"%.10lf\n",sizeof(t)*5/1024./1024.);
	n=_n; s=_s; p=_p; w=_w; l=_l;
	fr(b,0,8)
	{
		fr(i,0,n-1)
		{
			if(s[i]<=(1<<(b+b+b)))
			{
				t[b][0][i]=w[i]; m[b][0][i]=INF; d[b][0][i]=s[i];
			}
			else
			{
				t[b][0][i]=l[i]; m[b][0][i]=s[i]; d[b][0][i]=p[i];
			}
		}
		t[b][0][n]=n-1; m[b][0][n]=0; d[b][0][n]=0;
		fr(j,1,12)
		{
			fr(i,0,n-1)
			{
				int u=t[b][j-1][i];
				t[b][j+1][i]=t[b][j-1][u];
				m[b][j+1][i]=std::min(m[b][j-1][i],m[b][j-1][u]-d[b][j-1][i]);
				d[b][j+1][i]=d[b][j-1][i]+d[b][j-1][u];
			}
			fr(i,0,n-1)
			{
				int u=t[b][j+1][i];
				t[b][j][i]=t[b][j+1][u];
				m[b][j][i]=std::min(m[b][j+1][i],m[b][j+1][u]-d[b][j+1][i]);
				d[b][j][i]=d[b][j+1][i]+d[b][j+1][u];
			}
		}
	}
	return;
}

i64 simulate(int p, int z)
{
	i64 v=z;
	fr(b,0,8) fr(_t,0,7)
	{
		fd(q,12,0) fr(__t,0,2)
			if(v<m[b][q][p])
			{
				v+=d[b][q][p]; p=t[b][q][p];
			}
//		printf("%d %I64d\n",p,v);
		if(p!=n)
		{
			assert(v>=s[p]);
			v+=s[p]; p=w[p];
		}
//		printf("%d %I64d\n",p,v);
		if(p==n) return v;
	}
	return v;
}
}
void init(int _n, std::vector<int> _s, std::vector<int> _p, std::vector<int> _w, std::vector<int> _l)
{
	run::init(_n,_s,_p,_w,_l);
}
i64 simulate(int p, int z){ return run::simulate(p,z); }