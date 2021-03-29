cd ~/Desktop/luogu/1737/
g++ 1737.cpp -o 1737
touch 1737.zip
rm 1737.zip
for i in {1..10};
do
	echo $i>1737.in
	./1737<1737.in>nodes$i.out
done
zip 1737.zip *.out
rm 1737