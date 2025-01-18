#include<stdio.h>
#include<cuda.h>
#define i64 long long
#define m 1024
#define n 100000000
#define a(n) n*((i64)n*3-1)/2
/*
运行1/3的时间出97，出题人的恶意：
15431918 357216132022127  97
答案：
27042068 1096910149053902  108
*/
__global__ void search()
{
	int i=threadIdx.x+blockIdx.x*blockDim.x+1;
	int j=1,k=i-1,c=0; i64 I=a(i);
	while(j<i)
	{
		while(k>=j&&a(j)+a(k)>I) k--;
		if(k<j) break;
		if(a(j)+a(k)==I) c++;
		j++;
	}
	if(c>50){ printf("%d %lld  %d\n",i,a(i),c); }
}
int main()
{
	search<<<n/m+1,m>>>();
	cudaDeviceSynchronize();
	printf("finished.\n");
	return 0;
}