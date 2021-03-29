/***************************************************************
	File name: 2566.cpp
	Author: huhao
	Create time: Wed 07 Aug 2019 04:02:20 PM CST
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
const int N=15,M=(1<<12)+10,L=51210;
int n,m,d,x[N],y[N],v[N],vis[N][N][M],s[M],ans,_x[L],_y[L],p[L],w[L],l,r,c[N][N];
int mx[4]={1,-1,0,0};
int my[4]={0,0,1,-1};
char a[N][N];
int main()
{
	n=read();
	m=read();
	d=read();
	fr(i,1,d)
		v[i]=read();
	fr(i,1,n)
	{
		scanf("%s",a[i]+1);
		fr(j,1,m)
			if(a[i][j]!='0')
			{
				if(a[i][j]!='#')
				{
					x[a[i][j]-48]=i;
					y[a[i][j]-48]=j;
				}
				a[i][j]='#';
			}
	}
	fr(i,1,(1<<d)-1)
		fr(j,1,d)
			if(i&(1<<(j-1)))
			{
				s[i]=s[i^(1<<(j-1))]+v[j];
				break;
			}
//	fr(i,1,d)
//		fprintf(stderr,"%d %d %d\n",x[i],y[i],v[i]);
	fr(i,1,n)
		fr(j,1,m)
		{
			c[i][j]=c[i][j-1];
			fr(k,1,d)
				if(x[k]==i&&y[k]==j)
					c[i][j]^=(1<<(k-1));
		}
	fr(i,1,n)
		fr(j,1,m)
		{
//			fprintf(stderr,"%d %d\n",i,j);
			if(a[i][j]=='#')
				continue;
			memset(vis,0,sizeof(vis));
			l=1;
			r=1;
			_x[1]=i;
			_y[1]=j;
			p[1]=0;
			w[1]=0;
			vis[i][j][0]=1;
			while(l<=r)
			{
				int X=_x[l],Y=_y[l],P=p[l],W=w[l];
//				fprintf(stderr,"%d %d %d %d\n",X,Y,P,W);
				l++;
				if(X==i&&Y==j&&s[P]>W)
				{
					ans=max(ans,s[P]-W);
				}
				W++;
				fr(k,0,3)
				{
					int XX=X+mx[k],YY=Y+my[k],PP=P;
					if(k==1)
						PP^=c[XX][YY];
					if(k==0)
						PP^=c[X][Y];
					if(a[XX][YY]!='0'||vis[XX][YY][PP])
						continue;
					r++;
					_x[r]=XX;
					_y[r]=YY;
					p[r]=PP;
					w[r]=W;
					vis[XX][YY][PP]=1;
//					fprintf(stderr,"%d %d %d %d %d %d\n",X,Y,mx[k],my[k],XX,YY);
				}
			}
		}
	printf("%d\n",ans);
	return 0;
}
