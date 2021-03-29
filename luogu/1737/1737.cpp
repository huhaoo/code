/**************************************************************
	File name: 1737.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/11/2018, 12:44:27 PM
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
int s[1010],l=0,p[20];
int main()
{
	int T=read();
	if(T==1)
	{
		printf("I\n");
		printf("I\n");
		printf("+ 1 2\n");
		printf("- 3\n");
		printf("< 4 1\n");
		printf("O 5\n");
	}
	if(T==2)
	{
		printf("I\n");
		printf("< 1 4\n");
		printf("+ 1 2\n");
		printf("- 3\n");
		printf("S 4\n");
		printf("O 5\n");
	}
	if(T==3)
	{
		printf("I\n");
		printf("< 1 500\n");
		printf("S 2\n");
		printf("< 3 1\n");
		printf("C 4 -1\n");
		printf("O 5\n");
	}
	if(T==4)
	{
		printf("I\n");
		printf("C 1 %.30lf\n",1e-30);
		printf("< 2 500\n");
		printf("S 3\n");
		printf("< 4 152\n");
		printf("> 1 150\n");
		printf("+ 5 6\n");
		printf("S 7\n");
		printf("- 8\n");
		printf("C 9 0.5\n");
		printf("< 10 153\n");
		printf("+ 1 11\n");
		printf("+ 12 5\n");
		printf("O 13\n");
	}
	if(T==5)
	{
		printf("I\n");
		fr(i,1,31)
		{
			printf("< %d 1\n",i*3-2);
			printf("I\n");
			printf("+ %d %d\n",i*3-1,i*3);
		}
		printf("O 94\n");
		//0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0
	}
	if(T==6)
	{
		s[0]=1;
		fr(i,1,500)
		{
			fr(j,0,l)s[j]<<=1;
			fr(j,0,l)
				s[j+1]+=s[j]/10,s[j]%=10;
			if(s[l+1])l++;
		}
		fr(i,1,31)
		{
			fr(j,0,l)s[j]<<=1;
			fr(j,0,l)
				s[j+1]+=s[j]/10,s[j]%=10;
			if(s[l+1])l++;
		}
		printf("I\n");
		printf("< 1 500\n");
		fd(i,31,1)
		{
			int k=(32-i)*6-4;
			printf("C %d -",k);
			fd(j,l,0)putchar(j!=60?s[j]+48:48);
			putchar(10);
			fd(j,l,1)s[j-1]+=s[j]%2*10,s[j]/=2;s[0]/=2;
			if(!s[l])l--;
			printf("S %d\n",k+1);
			printf("O %d\n",k+2);
			printf("- %d\n",k+2);
			printf("< %d %d\n",k+4,500+i);
			printf("+ %d %d\n",k+5,k);
		}
		printf("> 188 500\n");
		printf("O 189\n");
	}
	if(T==7)
	{
		s[0]=1;l=0;
		fr(i,1,1000)s[i]=0;
		fr(i,1,500)
		{
			fr(j,0,l)s[j]<<=1;
			fr(j,0,l)
				s[j+1]+=s[j]/10,s[j]%=10;
			if(s[l+1])l++;
		}
		fr(i,1,31)
		{
			fr(j,0,l)s[j]<<=1;
			fr(j,0,l)
				s[j+1]+=s[j]/10,s[j]%=10;
			if(s[l+1])l++;
		}
		printf("I\n");
		printf("< 1 500\n");
		fd(i,31,1)
		{
			int k=(32-i)*5-3;
			printf("C %d -",k);
			fd(j,l,0)putchar(j!=60?s[j]+48:48);
			putchar(10);
			fd(j,l,1)s[j-1]+=s[j]%2*10,s[j]/=2;s[0]/=2;
			if(!s[l])l--;
			printf("S %d\n",k+1);
			printf("- %d\n",k+2);
			printf("< %d %d\n",k+3,500+i);
			printf("+ %d %d\n",k+4,k);
		}
		printf("> 157 500\n");
		s[0]=1;l=0;
		fr(i,1,1000)s[i]=0;
		fr(i,1,500)
		{
			fr(j,0,l)s[j]<<=1;
			fr(j,0,l)
				s[j+1]+=s[j]/10,s[j]%=10;
			if(s[l+1])l++;
		}
		fr(i,1,31)
		{
			fr(j,0,l)s[j]<<=1;
			fr(j,0,l)
				s[j+1]+=s[j]/10,s[j]%=10;
			if(s[l+1])l++;
		}
		printf("I\n");
		printf("< 159 500\n");
		fd(i,31,1)
		{
			int k=(32-i)*5-3+158;
			printf("C %d -",k);
			fd(j,l,0)putchar(j!=60?s[j]+48:48);
			putchar(10);
			fd(j,l,1)s[j-1]+=s[j]%2*10,s[j]/=2;s[0]/=2;
			if(!s[l])l--;
			printf("S %d\n",k+1);
			printf("- %d\n",k+2);
			printf("< %d %d\n",k+3,500+i);
			printf("+ %d %d\n",k+4,k);
		}
		printf("> 315 500\n");
		fd(i,31,0)
		{
			int k1=(i==0?158:(32-i)*5-3+2),k2=(i==0?316:(32-i)*5-3+158+2),k=(31-i)*9+317-(i!=31);
			printf("+ %d %d\n",k1,k2);
			printf("C %d -0.5\n",k);
			printf("< %d 500\n",k+1);
			printf("S %d\n",k+2);
			printf("< %d 1\n",k+3);
			printf("- %d\n",k);
			printf("+ %d %d\n",k+4,k+5);
			printf("< %d %d\n",k+6,i);
			if(i!=31)printf("+ %d %d\n",k-1,k+7);
		}
		printf("O 603\n");
	}
	if(T==8)
	{
		printf("I\n");
		printf("> 1 96\n");
		printf("C 2 -0.962423650119206894995517826848736846270368668771321039322036337680327735216443548824018858\n");
		printf("S 3\n");
		printf("C 4 -0.276393202250021030359082633126872376455938164038847427572910275458947907436219510058558559\n");
		printf("< 5 95\n");
		printf("O 6");
	}
	if(T==9)
	{
		int n=16;
		fr(i,1,n)
		{
			printf("I\n");
			p[i]=i;
		}
		int k=n+1;
		fr(i,1,n-1)
			fr(j,i+1,n)
			{
				int k1=p[i],k2=p[j];
				printf("- %d\n",k1);
				printf("+ %d %d\n",k,k2);
				printf("C %d %.30lf\n",k+1,1e-30);
				printf("< %d 500\n",k+2);
				printf("S %d\n",k+3);
				printf("< %d 152\n",k+4);
				printf("> %d 150\n",k+1);
				printf("+ %d %d\n",k+5,k+6);
				printf("S %d\n",k+7);
				printf("- %d\n",k+8);
				printf("C %d 0.5\n",k+9);
				printf("< %d 153\n",k+10);
				printf("+ %d %d\n",k+1,k+11);
				printf("+ %d %d\n",k+12,k+5);//k+13:|b-a|
				printf("+ %d %d\n",k1,k2);
				printf("+ %d %d\n",k+14,k+13);
				printf("> %d 1\n",k+15);//k+16:max
				printf("- %d\n",k+16);
				printf("+ %d %d\n",k+17,k+14);//k+18:min
				p[i]=k+18;
				p[j]=k+16;
				k+=19;
			}
		fr(i,1,n)
			printf("O %d\n",p[i]);
		//1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
		//1 2 3 4 10 6 7 8 9 5 11 12 13 14 15 16
		//16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
	}
	if(T==10)
	{
		int cnt=0,sa=4,m;
		printf("I\n");//1;a
		printf("I\n");//2;b
		printf("I\n");//3;m
		printf("> 1 1000\n");//4;sa
		printf("C 4 1\n");//5;1
		printf("> 1 150\n");//6;2^(-150)a
		printf("C 2 0.5\n");//7;b+=0.5
		cnt=7;
		fd(i,31,0)
		{
			int k=cnt;
			printf("< 5 %d\n",i);cnt++;//k+1
			printf("- %d\n",k+1);cnt++;//k+2
			printf("+ %d %d\n",k+2,k);cnt++;//k+3
			printf("< %d 1000\n",k+3);cnt++;//k+4
			printf("S %d\n",k+4);cnt++;//bi,k+5
			printf("C %d -1\n",k+5);cnt++;//k+6
			printf("< %d 500\n",k+6);cnt++;//k+7
			printf("+ 6 %d\n",k+7);cnt++;//k=8
			printf("S %d\n",k+8);cnt++;//k+9
			printf("< %d 1\n",k+9);cnt++;//k+10
			printf("- %d\n",k+5);cnt++;//k+11
			printf("+ %d %d\n",k+11,k+10);cnt++;//k+12
			printf("< %d %d\n",k+12,151+i);cnt++;//k+13
			printf("+ %d %d\n",sa,k+13);cnt++;//k+14
			sa=cnt;
			printf("< %d %d\n",k+5,i);cnt++;//k+15
			printf("- %d\n",k+15);cnt++;//k+16
			printf("+ %d %d\n",k+16,k);cnt++;//k+17
		}
		printf("C %d 0\n",sa);cnt++;sa=cnt;
		printf("- 3\n");cnt++;m=cnt;
		fd(i,64,0)
		{
			int d,k;
			printf("< %d %d\n",m,i);cnt++;d=cnt;
			printf("+ %d %d\n",sa,cnt);cnt++;
			printf("C %d 0.5\n",cnt);cnt++;
			printf("< %d 100\n",cnt);cnt++;
			printf("S %d\n",cnt);cnt++;k=cnt;
			printf("C %d -1\n",cnt);cnt++;
			printf("< %d 1000\n",cnt);cnt++;
			printf("> %d 150\n",d);cnt++;
			printf("+ %d %d\n",cnt-1,cnt);cnt++;
			printf("S %d\n",cnt);cnt++;
			printf("< %d 1\n",cnt);cnt++;
			printf("- %d\n",k);cnt++;
			printf("+ %d %d\n",cnt-1,cnt);cnt++;
			printf("< %d 151\n",cnt);cnt++;
			printf("+ %d %d\n",cnt,sa);cnt++;sa=cnt;
		}
//		printf("C %d -0.5\n",sa);cnt++;sa=cnt;
		printf("O %d\n",sa);
//		printf("O %d\n",m);
	}//2000
	return 0;
}