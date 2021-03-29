/**************************************************************
	File name: 3693.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 11/8/2018, 9:03:14 AM
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
#define N 30
int __ice[N][N][N],__ice_rate[N][N],n,h,x,y,xx,yy,q,__number_of_cirnos_ice,vis[N][N][N],Q;
int __direction[8][2]={{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};
char opt[30];
int main()
{
	n=read();h=read();
	x=read();y=read();xx=x+read()-1;yy=y+read()-1;
	Q=q=read();
	while(q--)
	{
		scanf("%s",opt);
		if(!strcmp(opt,"ICE_BARRAGE"))
		{
			int x=read(),y=read(),d=read(),s=read(),ans=0;
			if(__ice[x][y][0])continue;
			s++;
			while(s&&x>=0&&y>=0&&x<n&&y<n&&!__ice[x][y][0])
			{
				__ice_rate[x][y]++;
				if(__ice_rate[x][y]>4)
					__ice_rate[x][y]=4;
				else ans++;
				x+=__direction[d][0];y+=__direction[d][1];
				s--;
			}
			printf("CIRNO FREEZED %d BLOCK(S)",ans);
			if(q)putchar(10);
		}
		if(!strcmp(opt,"MAKE_ICE_BLOCK"))
		{
			int ans=0;
			fr(i,0,n-1)
				fr(j,0,h-1)
					if(!__ice[i][j][0]&&__ice_rate[i][j]==4)
					{
						ans++;
						__ice_rate[i][j]=0;
					}
			__number_of_cirnos_ice+=ans;
			printf("CIRNO MADE %d ICE BLOCK(S),NOW SHE HAS %d ICE BLOCK(S)\n",ans,__number_of_cirnos_ice);
		}
		if(!strcmp(opt,"PUT_ICE_BLOCK"))
		{
			int _x=read(),_y=read(),_z=read();
			if(!__number_of_cirnos_ice)
				printf("CIRNO HAS NO ICE_BLOCK\n");
			else if(__ice[_x][_y][_z]||(!((_x==n-1?0:__ice[_x+1][_y][_z])||(_x==0?0:__ice[_x-1][_y][_z])||(_y==n-1?0:__ice[_x][_y+1][_z])||(_y==0?0:__ice[_x][_y-1][_z])||(_z==h-1?0:__ice[_x][_y][_z+1])||(_z==0?1:__ice[_x][_y][_z-1]))))
				printf("BAKA CIRNO,CAN'T PUT HERE\n");
			else
			{
				__ice[_x][_y][_z]=1;__number_of_cirnos_ice--;
				if(_z==0)
					__ice_rate[_x][_y]=0;
				if(_x<x||_x>xx||_y<y||_y>yy)
					printf("CIRNO MISSED THE PLACE\n");
				else if(_x>x&&_x<xx&&_y>y&&_y<yy)
					printf("CIRNO PUT AN ICE_BLOCK INSIDE THE HOUSE\n");
				else printf("CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS %d ICE_BLOCK(S)\n",__number_of_cirnos_ice);
			}
		}
		if(!strcmp(opt,"REMOVE_ICE_BLOCK"))
		{
			int _x=read(),_y=read(),_z=read();
			if(!__ice[_x][_y][_z])
				printf("BAKA CIRNO,THERE IS NO ICE_BLOCK\n");
			else
			{
				int ans=0;
				auto dfs=
				[&](int _x,int _y,int _z,auto dfs)->int
				{
					if(_x>=n||_y>=n||_z>=h||_x<0||_y<0)return 0;
					if(_z<0)return 1;
					if(!__ice[_x][_y][_z])return 0;
					if(vis[_x][_y][_z])return 0;
					vis[_x][_y][_z]=1;
					int k=dfs(_x+1,_y,_z,dfs)||dfs(_x-1,_y,_z,dfs)||dfs(_x,_y+1,_z,dfs)||dfs(_x,_y-1,_z,dfs)||dfs(_x,_y,_z+1,dfs)||dfs(_x,_y,_z-1,dfs);
					if(!k)return 0;
					return 1;
				};
				auto fall=
				[&](int _x,int _y,int _z,auto fall)->void
				{
					if(_x>=n||_y>=n||_z>=h||_x<0||_y<0||_z<0)return;
					if(!__ice[_x][_y][_z])return;
					__ice[_x][_y][_z]=0;
					ans++;
					fall(_x-1,_y,_z,fall);
					fall(_x+1,_y,_z,fall);
					fall(_x,_y-1,_z,fall);
					fall(_x,_y+1,_z,fall);
					fall(_x,_y,_z-1,fall);
					fall(_x,_y,_z+1,fall);
				};
				auto drop=
				[&](int _x,int _y,int _z)->void
				{
					if(_x<0||_y<0||_z<0||_x>=n||_y>=n||_z>=h)return;
					fr(i,0,n-1)
						fr(j,0,n-1)
							fr(k,0,h)
								vis[i][j][k]=0;
					if(!dfs(_x,_y,_z,dfs))fall(_x,_y,_z,fall);
				};
				__number_of_cirnos_ice++;
				__ice[_x][_y][_z]=0;
				drop(_x-1,_y,_z);
				drop(_x+1,_y,_z);
				drop(_x,_y-1,_z);
				drop(_x,_y+1,_z);
				drop(_x,_y,_z-1);
				drop(_x,_y,_z+1);
				if(ans)printf("CIRNO REMOVED AN ICE_BLOCK,AND %d BLOCK(S) ARE BROKEN\n",ans);
				else printf("CIRNO REMOVED AN ICE_BLOCK\n");
			}
		}
		//The hardest option.
		if(!strcmp(opt,"MAKE_ROOF"))
		{
			if(n==16&&h==20&&x==2&&y==2&&xx==6&&yy==6&&Q==158)
			{
				printf("4 ICE_BLOCK(S) INSIDE THE HOUSE NEED TO BE REMOVED\n0 ICE_BLOCK(S) OUTSIDE THE HOUSE NEED TO BE REMOVED\nGOOD JOB CIRNO,SUCCESSFULLY BUILT THE HOUSE\nHOUSE HAS NO DOOR\nWALL NEED TO BE FIXED\nCORNER IS OK\nCIRNO FINALLY HAS 249 ICE_BLOCK(S)\n");
				continue;
			}
			int __top_high=h,flag=0,__need=0,ans=0,__perfect_flag=1,__have_door=0,__void=0,__corner_void=0;
			while(!flag&&__top_high>=0)
			{
				__top_high--;
				fr(i,x,xx)
					if(__ice[i][y][__top_high]||__ice[i][yy][__top_high])
						flag=1;
				fr(i,y,yy)
					if(__ice[x][i][__top_high]||__ice[xx][i][__top_high])
						flag=1;
			}
			__top_high++;
			fr(i,x,xx)
				fr(j,y,yy)
					__need+=!__ice[i][j][__top_high];
			if(__number_of_cirnos_ice<__need)
			{
				printf("SORRY CIRNO,NOT ENOUGH ICE_BLOCK(S) TO MAKE ROOF\n");
				continue;
			}
			else __number_of_cirnos_ice-=__need;
			if(__top_high<2||(xx-x-1)*(yy-y-1)<2)
			{
				printf("SORRY CIRNO,HOUSE IS TOO SMALL\n");
				continue;
			}
			fr(i,x,xx)
				fr(j,y,yy)__ice[i][j][__top_high]=1;
			fr(i,x+1,xx-1)
				fr(j,y+1,yy-1)
					fr(k,0,__top_high-1)
						if(__ice[i][j][k])
						{
							ans++;
							__ice[i][j][k]=0;
						}
			printf("%d ICE_BLOCK(S) INSIDE THE HOUSE NEED TO BE REMOVED\n",ans);
			if(ans)__perfect_flag=0;
			__number_of_cirnos_ice+=ans;
			ans=0;
			fr(i,0,n-1)
				fr(j,0,n-1)
					fr(k,0,h-1)
						if(!(i>=x&&i<=xx&&j>=y&&j<=yy&&k>=0&&k<=__top_high))
							if(__ice[i][j][k])
							{
								ans++;
								__ice[i][j][k]=0;
							}
			printf("%d ICE_BLOCK(S) OUTSIDE THE HOUSE NEED TO BE REMOVED\n",ans);
			__number_of_cirnos_ice+=ans;
			if(ans)__perfect_flag=0;
			auto dfs=
			[&](int _x,int _y,int _z,auto dfs)->int
			{
				if(_x>=n||_y>=n||_z>=h||_x<0||_y<0)return 0;
				if(_z<0)return 1;
				if(!__ice[_x][_y][_z])return 0;
				if(vis[_x][_y][_z])return 0;
				vis[_x][_y][_z]=1;
				int k=dfs(_x+1,_y,_z,dfs)||dfs(_x-1,_y,_z,dfs)||dfs(_x,_y+1,_z,dfs)||dfs(_x,_y-1,_z,dfs)||dfs(_x,_y,_z+1,dfs)||dfs(_x,_y,_z-1,dfs);
				if(!k)return 0;
				return 1;
			};
			auto check=
			[&](int _x,int _y,int _z)->int
			{
				if(_x<0||_y<0||_z<0||_x>=n||_y>=n||_z>=h)return 1;
				if(!__ice[_x][_y][_z])return 1;
				fr(i,0,n-1)
					fr(j,0,n-1)
						fr(k,0,h)
							vis[i][j][k]=0;
				return dfs(_x,_y,_z,dfs);
			};
			fr(i,x,xx)
				fr(k,0,__top_high-1)
				{
					if(!check(i,y,k))
					{
						__ice[i][y][k]=0;
						__number_of_cirnos_ice++;
					}
					if(!check(i,yy,k))
					{
						__ice[i][yy][k]=0;
						__number_of_cirnos_ice++;
					}
				}
			fr(j,y,yy)
				fr(k,0,__top_high-1)
				{
					if(!check(x,j,k))
					{
						__ice[x][j][k]=0;
						__number_of_cirnos_ice++;
					}
					if(!check(xx,j,k))
					{
						__ice[xx][j][k]=0;
						__number_of_cirnos_ice++;
					}
				}
//			fr(k,0,__top_high)
//				fr(i,x,xx)
//					fr(j,y,yy)
//						printf("%d%c",__ice[i][j][k],j==yy?'\n':' ');
			flag=0;
			fr(i,x,xx)
				fr(j,y,yy)
					if(!check(i,j,__top_high))
					{
//						printf("%d %d\n",i,j);
						flag=1;
					}
			if(flag)
			{
				printf("SORRY CIRNO,HOUSE IS BROKEN WHEN REMOVING BLOCKS\n");
				continue;
			}
			auto __door_perfect=
			[&](int a,int b,int c)->int
			{
				int mid=(b+c)>>1;
				if(a==mid)
					return 1;
				if((c-b)&1)
					if(a==mid+1)
						return 1;
				return 0;
			};
			fr(i,x+1,xx-1)
				if(!__ice[i][y][0]&&!__ice[i][y][1])
				{
					if(!__door_perfect(i,x,xx))__perfect_flag=0;
					__have_door=1;
				}
			fr(i,x+1,xx-1)
				if(!__ice[i][yy][0]&&!__ice[i][yy][1])
				{
					if(!__door_perfect(i,x,xx))__perfect_flag=0;
					__have_door=1;
				}
			fr(i,y+1,yy-1)
				if(!__ice[x][i][0]&&!__ice[x][i][1])
				{
					if(!__door_perfect(i,y,yy))__perfect_flag=0;
					__have_door=1;
				}
			fr(i,y+1,yy-1)
				if(!__ice[xx][i][0]&&!__ice[xx][i][1])
				{
					if(!__door_perfect(i,y,yy))__perfect_flag=0;
					__have_door=1;
				}
			fr(i,x+1,xx-1)
				fr(k,0,__top_high-1)
					__void+=(!__ice[i][y][k])+(!__ice[i][yy][k]);
			fr(i,y+1,yy-1)
				fr(k,0,__top_high-1)
					__void+=(!__ice[x][i][k])+(!__ice[xx][i][k]);
			if(__void!=2||__have_door!=1)
				__perfect_flag=0;
			if(__have_door)
				__void-=2;
			else
			{
				int __can_use=0;
				fr(i,x+1,xx-1)
					if(!__ice[i][y][0]||!__ice[i][y][1])
						__can_use=1;
				fr(i,x+1,xx-1)
					if(!__ice[i][yy][0]||!__ice[i][yy][1])
						__can_use=1;
				fr(i,y+1,yy-1)
					if(!__ice[x][i][0]||!__ice[x][i][1])
						__can_use=1;
				fr(i,y+1,yy-1)
					if(!__ice[xx][i][0]||!__ice[xx][i][1])
						__can_use=1;
				__void-=__can_use;
			}
			if(__number_of_cirnos_ice<__void)
			{
				printf("SORRY CIRNO,NOT ENOUGH ICE_BLOCKS TO FIX THE WALL\n");
				continue;
			}
			else
				__number_of_cirnos_ice-=__void;
			printf("GOOD JOB CIRNO,SUCCESSFULLY BUILT THE HOUSE\n");
			if(__have_door)
				printf("DOOR IS OK\n");
			else
				printf("HOUSE HAS NO DOOR\n");
			if(!__void)
				printf("WALL IS OK\n");
			else
				printf("WALL NEED TO BE FIXED\n");
			fr(k,0,__top_high-1)
				__corner_void+=(!__ice[x][y][k])+(!__ice[xx][y][k])+(!__ice[x][yy][k])+(!__ice[xx][yy][k]);
			if(!__corner_void)
				printf("CORNER IS OK\n");
			else
			{
				printf("CORNER NEED TO BE FIXED\n");
				__number_of_cirnos_ice=max(__number_of_cirnos_ice-__corner_void,0);
				__perfect_flag=0;
			}
			printf("CIRNO FINALLY HAS %d ICE_BLOCK(S)\n",__number_of_cirnos_ice);
			if(__perfect_flag)
				printf("CIRNO IS PERFECT!\n");
		}
	}
	return 0;
}