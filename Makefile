all: Voidcat run clean

Voidcat: program.cpp 
	g++ program.cpp -o Voidcat

run: Voidcat
	./Voidcat

clean:
	rm Voidcat

