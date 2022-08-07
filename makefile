all: 
	@gcc -c *.c
	@gcc -o compacta.out *.o

clean:
	@rm *.o compacta.out *.comp

test: clean all
