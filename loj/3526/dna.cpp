#include"dna.h"
#ifdef huhao
#include"grader.cpp"
#endif
#include<assert.h>
#define fr(i,a,b) for(int i=a;i<=b;i++)

const int N=100010;
int n,a[N],b[N],s[3][3][N];
void init(std::string A, std::string B)
{
	n=A.size(); static int Map[256]; Map['A']=0; Map['C']=1; Map['T']=2;
	fr(i,0,n-1)
	{
		a[i]=Map[A[i]]; b[i]=Map[B[i]];
		if(a[i]!=b[i]) s[a[i]][b[i]][i]++;
	}
	fr(i,0,2) fr(j,0,2) fr(k,1,n-1) s[i][j][k]+=s[i][j][k-1];
}

int get_distance(int x, int y)
{
	int S[3][3]; int _s[3]={0,0,0};
	fr(i,0,2) fr(j,0,2)
	{
		S[i][j]=s[i][j][y]-(x?s[i][j][x-1]:0);
		_s[i]+=S[i][j]; _s[j]-=S[i][j];
	}
	if(_s[0]||_s[1]||_s[2]) return -1;
	int ans=0;
	fr(i,0,2)
	{
		int j=(i+1)%3,k=std::min(S[i][j],S[j][i]);
		S[i][j]-=k; S[j][i]-=k; ans+=k;
	}
	assert(S[0][1]==S[1][2]&&S[1][2]==S[2][0]);
	assert(S[1][0]==S[2][1]&&S[2][1]==S[0][2]);
	return ans+(S[0][1]+S[1][0])*2;
}
