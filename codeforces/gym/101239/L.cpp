/***************************************************************
	File name: L.cpp
	Author: huhao
	Create time: Tue 17 Nov 2020 03:16:43 PM CST
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
#define i64 long long
#include<queue>
#include<vector>
const int N=1010;
i64 C[N][N];
int n;
double p1,p2,p3,p4;
double ans;
#define P std::pair<double,i64>
std::priority_queue<P,std::vector<P>,std::greater<P> > q;
int main()
{
	n=read(); scanf("%lf%lf%lf%lf",&p1,&p2,&p3,&p4);
	fr(i,0,n)
	{
		C[i][0]=C[i][i]=1;
		fr(j,1,i-1) C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	fr(i,0,n) fr(j,0,n-i) fr(k,0,n-i-j)
	{
		int l=n-i-j-k;
		q.push(P(pow(p1,i)*pow(p2,j)*pow(p3,k)*pow(p4,l),C[n][i]*C[n-i][j]*C[n-i-j][k]));
	}
	while(1)
		if(q.top().second==1)
		{
			if(q.size()==1) break;
			P u=q.top(); q.pop(); P v=q.top(); q.pop();
			ans+=u.first+v.first; v.second--;
			q.push({u.first+v.first,1}); if(v.second) q.push(v);
		}
		else
		{
			P u=q.top(); q.pop();
			ans+=2*u.first*(u.second/2); q.push({u.first*2,u.second/2}); u.second%=2;
			if(u.second) q.push(u);
		}
	printf("%.10lf\n",ans);
	return 0;
}
