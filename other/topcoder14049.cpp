#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
const int N=510;
class TheKFactor
{
	const double eps=1e-6,inf=1e20;
	double a[N][N];
	int n,m;
	void pivot(int s,int t)
	{
		double k=a[s][t]; a[s][t]=1;
		fr(i,0,n) a[s][i]/=k;
		fr(i,0,m) if(i!=s)
		{
			double k=a[i][t]; a[i][t]=0;
			fr(j,0,n) a[i][j]-=a[s][j]*k;
		}
	}
	int init()
	{
		while(1)
		{
			int s=0,t=0;
			fr(i,1,m) if(a[i][0]<-eps&&(!s||rand()%3==0)) s=i;
			if(!s) return 1;
			fr(i,1,n) if(a[s][i]<-eps&&(!t||rand()%3==0)) t=i;
			if(!t) return 0;
			pivot(s,t);
		}
	}
	int simplex()
	{
		while(1)
		{
			int s=0,t=0; double mi=inf;
			fr(i,1,n) if(a[0][i]>eps){ t=i; break; }
			if(!t) return 1;
			fr(i,1,m) if(a[i][t]>eps&&mi>a[i][0]/a[i][t]){ s=i; mi=a[i][0]/a[i][t]; }
			if(!s) return 0;
			pivot(s,t);
		}
	}
public:
	double expectedScore(std::vector<int> v)
	{
		srand(998244353);
		n=v.size(); m=1;
		fr(i,m,n) a[m][i]=-1;
		a[m][0]=-1;
		fr(i,1,n)
		{
			m++; a[m][0]=i*1./n;
			fr(j,1,i) a[m][j]=1;
		}
		fr(i,1,n)
		{
			m++; a[m][n+1]=-1;
			fr(j,1,i) a[m][j]=v[j-1];
			fr(j,i+1,n) a[m][j]=v[i-1];
		}
		a[0][n+1]=-1; n++; assert(init()); assert(simplex());
		return a[0][0];
	}
};
/*
int main()
{
	TheKFactor query;
	printf("%.10lf\n",query.expectedScore({0}));
	return 0;
}
*/
