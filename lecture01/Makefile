all: helloworld

helloworld: helloworld.o
	gcc $^ -o $@

helloworldv2:
	gcc -E helloworld.c -o helloworld.i
	gcc -S helloworld.i -o helloworld.s
	as helloworld.s -o helloworld.o

clean:
	rm -f helloworld.i helloworld.s helloworld.o helloworld helloworldv2
