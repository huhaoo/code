#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9'){ t=c=='-'?-1:1; c=getchar(); }
	while(c>='0'&&c<='9'){ r=(r<<3)+(r<<1)+(c^48); c=getchar(); }
	return r*t;
}
long double f[541][14][5][2][2],F[541][14][5][2][2],ans[541];
long double C[541][541];
int main()
{
	f[0][0][0][0][0]=1; int i=0,j=-2,k=0;
	while(true)
	{
		printf("%d %d %d\n",i,j,k);
		if(i==10)
		{
			fr(I,0,540) ans[I]=f[I][13][4][0][0];
			break;
		}
		memcpy(F,f,sizeof(f)); memset(f,0,sizeof(f));
		if(j==13)
		{
			fr(I,0,540) fr(J,0,13) fr(K,0,4)
				f[I][J][K][0][0]+=F[I][J][K][1][0];
			i++; j=-2; k=0;
			continue;
		}
		if(k==4)
		{
			fr(I,0,540) fr(J,0,13) fr(K,0,4) fr(L,0,1) fr(O,0,1)
				f[I][J][K][L][0]+=F[I][J][K][L][O];
			j++; k=0;
			continue;
		}
		if(j<0)
		{
			fr(I,0,539) fr(J,0,13) fr(K,0,4) fr(L,0,1)
			{
				f[I][J][K][L][0]+=F[I][J][K][L][0];
				f[I+1][J][K][1][0]+=F[I][J][K][L][0];
			}
			j++;
		}
		else
		{
			fr(I,0,539) fr(J,0,13) fr(K,0,4) fr(L,0,1) fr(O,0,1)
			{
				f[I][J][K][L][O]+=F[I][J][K][L][O];
				f[I+1][J+(not O and j>=J)][K+(k>=K)][1][O or j>=J]+=F[I][J][K][L][O];
			}
			k++;
		}
	}
//	fr(i,0,540) printf("%E ",(double)ans[i]);
	fr(i,0,540)
	{
		C[i][0]=C[i][i]=1;
		fr(j,1,i-1) C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	long double Ans=0;
//	fr(i,0,540) printf("%.10lf ",double(ans[i]/C[540][i]));
	fr(i,0,540) Ans+=1-ans[i]/C[540][i];
	printf("%.8lf\n",(double)Ans);
	return 0;
}