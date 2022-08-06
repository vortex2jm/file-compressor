all: 
	@gcc -c *.c
	@gcc -o prog *.o

clean:
	@rm *.o prog *.comp

test: clean all
