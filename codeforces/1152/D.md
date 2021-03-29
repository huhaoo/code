考虑$s_{i,j}$表示还剩$i$个`<`，$j$个`>`的树

显然

$$
\begin{align}
t_{s_{i,j},<}=\cases{s_{i-1,j}&$i\not =0$\\
\mathrm{null}&$i=0$}\tag{1}\\
t_{s_{i,j},>}=\cases{s_{i,j-1}&$i<j$\\
\mathrm{null}&$i=j$}\tag{2}
\end{align}
$$
$f_{i,j,0/1}$表示$s_{i,j}$的根选/不选的最大匹配

状态易得，另外因为选肯定比不选好，所以不用写`long double`比大小

（但是`case 1`不知道为什么能过）

```cpp
	n=read();
	fr(i,1,n)
	{
		f[0][i][0]=i/2;
		f[0][i][1]=(i+1)/2;
	}
	fr(i,1,n)
	{
		f[i][i][0]=f[i-1][i][1];
		f[i][i][1]=(1+f[i-1][i][0])%mod;
		fr(j,i+1,n)
		{
			//case 0
			f[i][j][0]=(f[i-1][j][1]+f[i][j-1][1])%mod;
			//case 1
			f[i][j][1]=(1+f[i-1][j][0]+f[i][j-1][1])%mod;
		}
	}
	printf("%d\n",f[n][n][1]);
```

