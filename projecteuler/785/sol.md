令
$$
f(x,y,z)=15(x^2+y^2+z^2)-34(xy+yz+zx)\\
F(x,y)=f(x,y,1)=15(x^2+y^2)-34(xy+x+y)+15
$$
则：
$$
f(x,y,z)=0\Leftrightarrow F(\dfrac xz,\dfrac yz)=0
$$
不难发现：
$$
f(7,16,1)=F(7,16)=0
$$
令
$$
y=k(x-7)+16
$$
则
$$
F(x,y)=(-7 + x) (-473 + k (446 + 15 k (-7 + x) - 34 x) + 15 x)
$$
令上式为$0$，则有：
$$
-473 + k (446 + 15 k (-7 + x) - 34 x) + 15 x=0\\
\begin{cases}
x=\dfrac{473 - 446 k + 105 k^2}{15 - 34 k + 15 k^2}\\
y=\dfrac{240-176k+32k^2}{15 - 34 k + 15 k^2}\\
\end{cases}
$$
引入变量$z$，有：
$$
\begin{cases}
x=d(473 - 446 k + 105 k^2)\\
y=d(240-176k+32k^2)\\
z=d(15 - 34 k + 15 k^2)
\end{cases}
$$
将$k$视为两个数的商：
$$
\begin{cases}
x=(5p-11q)(21p-43q)\\
y=16(p-3q)(2p-5q)\\
z=(5p-3q)(3p-5q)
\end{cases}
$$
打表发现$\gcd(x,y,z)\in\{1,4,16,64\}$，$q\ge 29000$就无解了。
