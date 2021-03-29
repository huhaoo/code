/***************************************************************
	File name: 5469.cpp
	Author: huhao
	Create time: Tue 30 Jul 2019 09:06:18 AM CST
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
#define i64 long long
const int N=1210,L=4100,M=4200,mod=1000000007,SL=28800010;
i64 _a[L],_b[L],_f[N],f_[N];
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	a%=p;
	while(b)
	{
		if(b&1)
			r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r;
}
void mul(i64 *c,i64 *a,i64 *b,i64 n,i64 m)
{
	fr(i,0,n)
		_a[i]=a[i];
	fr(i,0,m)
		_b[i]=b[i];
	fr(i,0,n+m)
		c[i]=0;
	fr(i,0,n)
		fr(j,0,m)
			c[i+j]=(c[i+j]+_a[i]*_b[j])%mod;
}
i64 _c[L],_d[L];
void _mul(i64 *c,i64 *a,i64 *b,i64 n,i64 m)
{
	mul(_c,f_,a,n+m,n);
	mul(_d,f_,b,n+m,m);
	fr(i,0,n+m)
		_c[i]=_c[i]*_d[i]%mod*_f[i]%mod;
	fr(i,0,n+m)
		_d[i]=(i%2?mod-f_[i]:f_[i]);
	mul(c,_c,_d,n+m,n+m);
	fr(i,n+m+1,(n+m)*2)
		c[i]=0;
}
i64 n,u[N],d[N],id[N][N],a[N],c,m,s[M][N];
i64 *f[M][N],*g;
i64 _e[L];
void del1(i64 *b,i64 *a,i64 n)
{
	fr(i,0,n)
		b[i]=0;
	_e[n]=a[n];
	fd(i,n,1)
	{
		b[i]=_e[i];
		_e[i-1]=(a[i-1]-i*_e[i]%mod+mod)%mod;
	}
	b[0]=_e[0];
}
void plus1(i64 *b,i64 *a,i64 n)
{
	fr(i,0,n)
		b[i]=0;
	fr(i,1,n)
	{
		b[i]=(b[i]+a[i])%mod;
		b[i-1]=(b[i-1]+a[i]*i)%mod;
	}
	b[0]=(b[0]+a[0])%mod;
}
i64 inv(i64 k)
{
	return _f[k-1]*f_[k]%mod;
}
i64 _g[L];
void presum(i64 *b,i64 *a,i64 n)
{
	fr(i,0,n)
		_g[i+1]=inv(i+1)*a[i]%mod;
	_g[0]=0;
	plus1(b,_g,n+1);
	b[0]=(b[0]-a[0]+mod)%mod;
}
i64 _h[L];
i64 calc(i64 *a,i64 n,i64 v)
{
	presum(_h,a,n);
	i64 s=0,k=1;
	fr(i,0,n+1)
	{
		s=(s+_h[i]*k)%mod;
		k=k*(v-i)%mod;
	}
	return s;
}
i64 _fl[L],_fr[L],pl[L],pr[N];
void dfs(i64 l,i64 r)
{
	if(l>r||id[l][r])
		return;
	id[l][r]=++c;
	fr(i,1,m)
	{
		f[c][i]=g;
		g=g+r-l+10;
	}
	if(l==r)
	{
		fr(i,d[l],u[l])
			f[c][i][0]=1;
		fr(i,d[l],m)
			s[c][i]=s[c][i-1]+(i<=u[l])*(a[i+1]-a[i]);
		return;
	}
	i64 _l,_r;
	if((r-l)%2==0)
	{
		_l=(l+r)/2-1;
		_r=_l+2;
	}
	else
	{
		_l=(l+r)/2;
		_r=_l+1;
	}
	_l=max(_l,l);
	_r=min(_r,r);
	i64 t=c;
	fr(i,_l,_r)
	{
		dfs(l,i-1);
		dfs(i+1,r);
		fr(j,d[i],u[i])
		{
			if(i==l)
			{
				i64 ir=id[i+1][r];
				fr(k,0,r-i-1)
					_fr[k]=f[ir][j][k];
				presum(pr,_fr,r-i-1);
				del1(_fr,pr,r-i);
				_fr[0]=(_fr[0]+s[ir][j-1])%mod;
				fr(k,0,r-l)
					f[t][j][k]=(f[t][j][k]+_fr[k])%mod;
				continue;
			}
			if(i==r)
			{
				i64 il=id[l][i-1];
				fr(k,0,i-1-l)
					_fl[k]=f[il][j][k];
				presum(pl,_fl,i-1-l);
				pl[0]=(pl[0]+s[il][j-1])%mod;
				fr(k,0,r-l)
					f[t][j][k]=(f[t][j][k]+pl[k])%mod;
				continue;
			}
			i64 il=id[l][i-1],ir=id[i+1][r];
			fr(k,0,r-i-1)
				_fr[k]=f[ir][j][k];
			fr(k,0,i-l-1)
				_fl[k]=f[il][j][k];
			presum(pr,_fr,r-i-1);
			del1(_fr,pr,r-i);
			_fr[0]=(_fr[0]+s[ir][j-1])%mod;
			presum(pl,_fl,i-1-l);
			pl[0]=(pl[0]+s[il][j-1])%mod;
			_mul(pr,_fr,pl,r-i,i-l);
			fr(k,0,r-l)
				f[t][j][k]=(f[t][j][k]+pr[k])%mod;
		}
	}
	fr(j,1,m)
		s[t][j]=(s[t][j-1]+calc(f[t][j],r-l,a[j+1]-a[j]))%mod;
}
int main()
{
/*	freopen("robot.in","r",stdin);
	freopen("robot.out","w",stdout);*/
	g=new i64[SL];
	memset(g,0,sizeof(i64[SL]));
	n=read();
	_f[0]=1;
	fr(i,1,n*2)
		_f[i]=_f[i-1]*i%mod;
	f_[n*2]=power(_f[n*2],mod-2,mod);
	fd(i,n*2,1)
		f_[i-1]=f_[i]*i%mod;
	fr(i,1,n)
	{
		d[i]=read();
		u[i]=read()+1;
		a[++m]=d[i];
		a[++m]=u[i];
	}
	sort(a+1,a+m+1);
	m=unique(a+1,a+m+1)-a-1;
	fr(i,1,n)
	{
		d[i]=lower_bound(a+1,a+m+1,d[i])-a;
		u[i]=lower_bound(a+1,a+m+1,u[i])-a;
	}
	fr(i,1,n)
		u[i]--;
	m--;
	dfs(1,n);
	printf("%lld\n",s[id[1][n]][m]);
	return 0;
}
