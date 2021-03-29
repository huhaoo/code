/***************************************************************
	File name: I.cpp
	Author: huhao
	Create time: Wed 25 Nov 2020 07:01:45 PM CST
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
#include<vector>
const int _at[]={4,40,40,36,101},_At[]={1,4,160,6400,230400};
#define at(x,i) (x/_At[i]%_at[i]+(1<=i&&i<=3))
int zip(int x,int y,int X,int Y,int d)
{
	assert(d<=3&&x<=40&&y<=40&&X<=36&&Y<=100);
	return (d*_At[0]+(x-1)*_At[1]+(y-1)*_At[2]+(X-1)*_At[3]+Y*_At[4]);
}
const int N=256,M=23270410;
int a[N][N],l[N];
char s[N][N];
int p[N][N];
int r,c,n,m,t;
int Q[N];
int vis[M],ans[M];
int D[N],_D[N]={'n','e','s','w'};
int dx[N]={-1,0,1,0};
int dy[N]={0,1,0,-1};
void Solve(int q)
{
	if(vis[q]) return ;
	vis[q]=-1;
	int x=at(q,1),y=at(q,2),X=at(q,3),Y=at(q,4),d=at(q,0);
//	printf("%d %d %c %d'%c' %c\n",x,y,X<=26?X-1+'A':X-27+'0',Y,s[X][Y],_D[d]);
	if(Y==l[X]){ vis[q]=1; ans[q]=q; return ; }
	if(s[X][Y]>='A'&&s[X][Y]<='Z')
	{
		int c=s[X][Y]-'A'+1,z=zip(x,y,c,0,d);
		Solve(z);
		if(vis[z]==-1) return ;
		int a=ans[z],_x=at(a,1),_y=at(a,2),_d=at(a,0);
		z=zip(_x,_y,X,Y+1,_d); Solve(z);
		if(vis[z]==-1) return ;
		vis[q]=1; ans[q]=ans[z]; return ;
	}
	int _x=x,_y=y,_X=X,_Y=Y+1,_d=d;
	switch(s[X][Y])
	{
	case 'm':
		if(a[x+dx[d]][y+dy[d]]){ _x+=dx[d]; _y+=dy[d]; }
		break;
	case 'l':
		_d=(_d-1)&3;
		break;
	case '(': case 'i': case 'u':
		break;
	case 'b': case 'n': case 's': case 'e': case 'w':
	{
		int st=0;
		if(s[X][Y]=='b'){ if(!a[x+dx[d]][y+dy[d]]) st=1; }
		else if(d==D[s[X][Y]]) st=1;
//		printf("%d\n",st);
		if((s[X][Y-1]=='u'&&st)||(s[X][Y-1]=='i'&&!st))
		{
			_Y=p[X][Y+1]+1;
		}
		break;
	}
	case ')':
		switch(s[X][p[X][Y]-2])
		{
		case 'u':
			_Y=p[X][Y]-1;
			break;
		case 'i':
			_Y=p[X][Y+1]+1;
			break;
		}
		break;
	}
	int z=zip(_x,_y,_X,_Y,_d); Solve(z);
	if(vis[z]==-1) return ;
	ans[q]=ans[z]; vis[q]=1;
}
int main()
{
	D['n']=0; D['e']=1; D['s']=2; D['w']=3;
	r=read(); c=read(); n=read(); m=read();
	fr(i,1,r)
	{
		static char s[N];
		scanf("%s",s+1);
		fr(j,1,c) if(s[j]=='.') a[i][j]=1;
	}
	fr(i,1,n)
	{
		char c=0;
		while(c<'A'||c>'Z') c=getchar();
		getchar();
		scanf("%s",s[c-'A'+1]);
	}
	n=26;
	fr(i,1,m)
	{
		int x=read(),y=read(); char c=getchar();
		Q[i]=zip(x,y,i+26,0,D[c]);
		scanf("%s",s[++n]);
	}
	fr(i,1,n)
	{
		static int a[N],A; A=0; l[i]=strlen(s[i]);
		fr(j,0,l[i]) p[i][j]=-1;
		fr(j,0,l[i]-1)
		{
			if(s[i][j]=='(') a[++A]=j;
			else if(s[i][j]==')'){ p[i][j]=a[A]; p[i][a[A]]=j; A--; }
		}
	}
	fr(i,1,m)
	{
		Solve(Q[i]);
		if(vis[Q[i]]==1){ int Ans=ans[Q[i]]; printf("%d %d %c\n",at(Ans,1),at(Ans,2),_D[at(Ans,0)]); }
		else printf("inf\n");
	}
	return 0;
}
