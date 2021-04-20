all:
	gcc -O3 -I. -I kremlib/dist/minimal -Wall -Wextra *.c && ./a.out
lib:
	gcc -O3 -fPIC -I. -I kremlib/dist/minimal -c Hacl_Curve25519_51.c
	gcc -O3 -fPIC -I. -I kremlib/dist/minimal -c Hacl_Curve25519_64.c
	gcc -O3 -fPIC -I. -I kremlib/dist/minimal -c Hacl_Curve25519_64_Slow.c
	gcc -shared -Wl,-soname,libhaclx255.so.0 -o libhaclx255.so.0 -lc Hacl_Curve25519_51.o Hacl_Curve25519_64.o Hacl_Curve25519_64_Slow.o
	sudo cp -uf libhaclx255.so.0 /usr/local/lib
	sudo ldconfig	
clean:
	rm -rf *.o *.out
