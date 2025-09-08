def fact(n):
	if n<2:return 1
	r=1
	for i in range(2,n+1):r*=i
	return r
def P(x,y):
	return fact(x+y)//fact(x)//fact(y)/(2**(x+y))

a,b=89,97
# a,b=1,1
n=200
f=[1]
g=[1]
for i in range(1,n):
	res=P(a*i,b*i)
	g.append(res)
	# print(res)
	for j in range(1,i):
		res-=f[j]*g[i-j]
	# print(res)
	f.append(res)

print("{:.9f}".format(1-sum(f[1:])))