/***************************************************************
	File name: M.cpp
	Author: huhao
	Create time: Thu 14 Jan 2021 04:48:10 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
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
const int N=300;
int n,m,T;
int x[N],y[N],X[N],Y[N],c;
char op[N];
bool in(int x,int l,int r){ return l<=x&&x<=r; }
int cross(int _x,int _y,int _X,int _Y,int i)
{
	if(_x+_X<=x[i]) return 0;
	if(_y+_Y<=y[i]) return 0;
	if(_x>=x[i]+X[i]) return 0;
	if(_y>=y[i]+Y[i]) return 0;
	return 1;
}
bool check(int _x,int _y,int _X,int _Y,int ig=0)
{
	if(_x<0||_y<0||_x+_X>n||_y+_Y>m) return 0;
	fr(i,1,c) if(i!=ig&&cross(_x,_y,_X,_Y,i)) return 0;
	return 1;
}
int find(int _x,int _y)
{
	fr(i,1,c) if(in(_x,x[i],x[i]+X[i]-1)&&in(_y,y[i],y[i]+Y[i]-1)) return i;
	return 0;
}
int main()
{
	n=read(); m=read();
	while(scanf("%s",op)!=EOF)
	{
		T++;
		if(!strcmp(op,"OPEN"))
		{
			int _x=read(),_y=read(),_X=read(),_Y=read();
			if(check(_x,_y,_X,_Y))
			{
				c++; x[c]=_x; y[c]=_y; X[c]=_X; Y[c]=_Y;
			}
			else printf("Command %d: OPEN - window does not fit\n",T);
		}
		if(!strcmp(op,"CLOSE"))
		{
			int _x=read(),_y=read(); int p=find(_x,_y);
			if(p)
			{
				c--;
				fr(j,p,c){ x[j]=x[j+1]; y[j]=y[j+1]; X[j]=X[j+1]; Y[j]=Y[j+1]; }
			}
			else printf("Command %d: CLOSE - no window at given position\n",T);
		}
		if(!strcmp(op,"RESIZE"))
		{
			int _x=read(),_y=read(),_X=read(),_Y=read(); int p=find(_x,_y);
			if(!p){ printf("Command %d: RESIZE - no window at given position\n",T); continue; }
			if(check(x[p],y[p],_X,_Y,p)){ X[p]=_X; Y[p]=_Y; }
			else printf("Command %d: RESIZE - window does not fit\n",T);
		}
		if(!strcmp(op,"MOVE"))
		{
			int _x=read(),_y=read(),dx=read(),dy=read(); int p=find(_x,_y);
			if(!p){ printf("Command %d: MOVE - no window at given position\n",T); continue; }
			static int d[N],vis[N];
			fr(i,0,c){ d[i]=std::abs(dx+dy); vis[i]=0; }
			d[p]=0;
			fr(i,1,c)
			{
				int u=0;
				fr(j,1,c) if(!vis[j]&&(!u||d[j]<d[u])) u=j;
				vis[u]=1;
				if(dx==0)
				{
					if(dy>0)
					{
						if(d[u]>=dy) continue;
						fr(j,1,c) if(u!=j&&cross(x[u],y[u],X[u],Y[u]+dy,j)) d[j]=std::min(d[j],d[u]+y[j]-(y[u]+Y[u]));
						d[0]=std::min(d[0],d[u]+m-(y[u]+Y[u]));
					}
					else
					{
						if(d[u]>=-dy) continue;
						fr(j,1,c) if(u!=j&&cross(x[u],y[u]-(-dy),X[u],Y[u]+(-dy),j)) d[j]=std::min(d[j],d[u]+y[u]-(y[j]+Y[j]));
						d[0]=std::min(d[0],d[u]+y[u]);
					}
				}
				else
				{
					if(dx>0)
					{
						if(d[u]>=dx) continue;
						fr(j,1,c) if(u!=j&&cross(x[u],y[u],X[u]+dx,Y[u],j)) d[j]=std::min(d[j],d[u]+x[j]-(x[u]+X[u]));
						d[0]=std::min(d[0],d[u]+n-(x[u]+X[u]));
					}
					else
					{
						if(d[u]>=-dx) continue;
						fr(j,1,c) if(u!=j&&cross(x[u]-(-dx),y[u],X[u]+(-dx),Y[u],j)) d[j]=std::min(d[j],d[u]+x[u]-(x[j]+X[j]));
						d[0]=std::min(d[0],d[u]+x[u]);
					}
				}
			}
//			fr(i,0,c) printf("%d%c",d[i],i==c?'\n':' ');
			if(d[0]!=std::abs(dx+dy)) printf("Command %d: MOVE - moved %d instead of %d\n",T,d[0],std::abs(dx+dy));
			fr(i,1,c) if(d[0]>d[i]){ x[i]+=(dx>0?1:dx<0?-1:0)*(d[0]-d[i]); y[i]+=(dy>0?1:dy<0?-1:0)*(d[0]-d[i]); }
		}
	}
	printf("%d window(s):\n",c);
	fr(i,1,c) printf("%d %d %d %d\n",x[i],y[i],X[i],Y[i]);
	return 0;
}
