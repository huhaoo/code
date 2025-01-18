def mex(a:list):
	for i in range(len(a)+1):
		if not i in a:
			return i
F={}
def f(a:list):
	if min(a)<0: return -1
	A=tuple(a)
	if not A in F:
		ans=[]
		for i in range(len(a)):
			for j in range(a[i]):
				if(a==[2,4,5,8,9]):
					print(sorted([j if k==i else a[k]-(j<a[k]) for k in range(len(a))]),f([j if k==i else a[k]-(j<a[k]) for k in range(len(a))]))
				ans.append(f([j if k==i else a[k]-(j<a[k]) for k in range(len(a))]))
			if(a==[2,4,5,8,9]):
				print()
		F[A]=mex(ans)
	return F[A]

a=[2,4,5,8]
for k in range(max(a),20):
	print(f(a+[k]),end=' ')
exit(0)

for k in range(0,8):
	for i in range(0,8):
		for j in range(0,8):
			print("{:3d}".format(f(i,j,k)),end=' ')
		print()
	print()