all:
	gcc -O3 -I. -I kremlib/dist/minimal -Wall -Wextra *.c && ./a.out
lib:
	gcc -O3 -fPIC -I. -I kremlib/dist/minimal -c Hacl_Curve25519_51.c
	gcc -O3 -fPIC -I. -I kremlib/dist/minimal -c Hacl_Curve25519_64.c
	gcc -O3 -fPIC -I. -I kremlib/dist/minimal -c Hacl_Curve25519_64_Slow.c
	gcc -O3 -fPIC -I. -I kremlib/dist/minimal -c Hacl_Ed25519.c
	gcc -O3 -fPIC -I. -I kremlib/dist/minimal -c Hacl_Hash.c
	gcc -O3 -fPIC -I. -I kremlib/dist/minimal -c Hacl_Spec.c
	gcc -O3 -fPIC -I. -I kremlib/dist/minimal -c Lib_Memzero0.c
	gcc -shared -Wl,-soname,libhaclx255.so.0 -o libhaclx255.so.0 -lc Hacl_Curve25519_51.o Hacl_Ed25519.o Hacl_Hash.o Hacl_Spec.o Lib_Memzero0.o
	sudo cp -uf libhacled.so.0 /usr/local/lib
	sudo ldconfig	
clean:
	rm -rf *.o *.out
