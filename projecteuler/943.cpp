#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
const i64 mod=2233222333;
const i64 N=(1<<25)+10;

i64 solve(int a,int b,i64 n)
{
	int mx;
	// offset, cnt, sum
	static i64 f[N][3];
	static int val[int(1e8)+10],l,lst;
	i64 ans=0;
	mx=(a+b)<8?1e8:(a+b)<16?1e7:1e6;
	l=a; lst=1; fr(i,1,l) val[i]=a;
	while((i64)l*(a+b)<=mx)
	{
		int k=l;
		fr(i,lst+1,k)
		{
			l++; val[l]=(val[l-1]==a?b:a);
			fr(j,1,val[i]-1){ l++; val[l]=val[l-1]; }
		}
		lst=k;
		// printf("%d ",l);
	}
	// l=a;
	// printf("%d %lld\n",l,n); fflush(stdout);
	if(l>n) l=n;
	fr(i,1,l) ans=(ans+val[i])%mod;
	n-=l;
	if(!n) return ans;

	f[2][0]=0; f[2][1]=1; f[2][2]=a;
	f[3][0]=1; f[3][1]=1; f[3][2]=b;

	int o=(val[l]==a?2:0); int m=2;
	while(true)
	{
		fr(i,0,(1<<m)-1)
		{
			i64 &off=f[i+(1<<m)][0], &cnt=f[i+(1<<m)][1], &sum=f[i+(1<<m)][2];
			off=i>>1; cnt=sum=0;
			fr(j,1,i&1?b:a)
			{
				cnt+=f[(1<<(m-1))+off][1];
				sum=(sum+f[(1<<(m-1))+off][2])%mod;
				off=f[(1<<(m-1))+off][0];
			}
			off=((off<<1)^2)|(i&1);
		}
		// static int _o=0,scnt=2; printf("%d %d  %d %d %d  %d\n",m,_o,f[(1<<m)+_o][0],f[(1<<m)+_o][1],f[(1<<m)+_o][2],scnt+=f[(1<<m)+_o][1]); _o=(f[(1<<m)+_o][0]<<1);
		// if(m<=3){ fr(i,(1<<m),(1<<(m+1))-1) printf("%d  %d %d %d\n",i-(1<<m),f[i][0],f[i][1],f[i][2]); putchar('\n'); }
		// else exit(0);
		fr(i,lst+1,l)
		{
			o|=(val[i]==b);
			i64 off=f[(1<<m)+o][0], cnt=f[(1<<m)+o][1], sum=f[(1<<m)+o][2];
			if(n>cnt) { n-=cnt; ans=(ans+sum)%mod; o=off-(off&1); }
			else goto break1;
		}
		m++; o=(o<<1)^(val[l]==a?2:0);
		assert(m<=23);
		// printf("%d %d  %lld\n",m,o,n);
	}
break1:;
	// exit(0);
	// printf("%d %d %lld(%d)  %lld\n",m,o,n,f[(1<<m)+o][1],ans);
	while(true)
	{
		// printf("%d %d  %lld  %d\n",m,o,n,f[(1<<m)+o][1]);
		int off=o>>1;
		fr(i,1,o&1?b:a)
		{
			i64 cnt=f[(1<<(m-1))+off][1], sum=f[(1<<(m-1))+off][2];
			// printf(" %d %d  %d %d\n",i,off,cnt,sum);
			if(n>=cnt) { n-=cnt; ans=(ans+sum)%mod; if(!n) goto break2;  }
			else{ o=off; break; }
			off=f[(1<<(m-1))+off][0];
			assert(i!=(o&1?b:a));
		}
		m--;
		assert(m>1);
	}
break2:;
	// exit(0);
	printf("%d %d  %lld\n",a,b,ans); fflush(stdout);
	return ans;
}

int main()
{
	// printf("%d\n",solve(2,3,63));
	// printf("%d\n",solve(2,3,10));
	// printf("%d\n",solve(4,2,1e4));
	// printf("%d\n",solve(5,8,1e6));
	// return 0;
	i64 n=22332223332233;
	i64 ans=0;
	// printf("%d\n",sizeof(f)/1024/1024);
	// printf("%lf\n",log(n)/log(10));
	fr(a,2,223) fr(b,2,223) if(a!=b) ans=(ans+solve(a,b,n))%mod;
	printf("%lld\n",ans);
	return 0;
}

/*
 * 2 2 3 3
 * 2 2 2 3 3 3
 */