from decimal import *
getcontext().prec=128
l=Decimal(0)
r=Decimal(1)
m=15
M=120
for i in range(M):
	x=(l+r)/2
	ans=pow(x,m)
	for j in range(M):
		Ans=x
		for k in range(j):
			Ans=Ans*Ans
		for k in range(j+1):
			Ans=Ans/2
		ans-=Ans
	if ans<0: l=x
	else: r=x
print(x)
ans=Decimal(1)-pow(x,10**9)
print(ans)