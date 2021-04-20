#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include "monocypher.h"
#include "Hacl_Curve25519_51.h"
#include "Hacl_Curve25519_64.h"

#define ARRAY(name, size) \
    uint8_t name[size]; \
    for(size_t i = 0; i < size; i++) name[i] = i;

//@ ensures \result == 0;
int x25519_51(void) {
    ARRAY(key, 32);
    ARRAY(pub1, 32);
    ARRAY(pub2, 32);
    key[0] = 0;
	pub1[0] = 123;
    int status = 0;
    
    crypto_x25519_public_key(pub1, key);
    Hacl_Curve25519_51_secret_to_public(pub2, key);
    status |= crypto_verify32(pub1, pub2);
    return status;
}

int x25519_64(void) {
    ARRAY(key, 32);
    ARRAY(pub1, 32);
    ARRAY(pub2, 32);
    key[0] = 0;
	pub1[0] = 123;
    int status = 0;
    
    crypto_x25519_public_key(pub1, key);
    Hacl_Curve25519_64_secret_to_public(pub2, key);
    status |= crypto_verify32(pub1, pub2);
    return status;
}


/* from Monocypher library, Loup hi! */
static void iterate_x25519_51(uint8_t k[32], uint8_t u[32])
{
    uint8_t tmp[32];
    Hacl_Curve25519_51_scalarmult(tmp , k, u);
    memcpy(u, k  , 32);
    memcpy(k, tmp, 32);
}

static void iterate_x25519_64(uint8_t k[32], uint8_t u[32])
{
    uint8_t tmp[32];
    Hacl_Curve25519_64_scalarmult(tmp , k, u);
    memcpy(u, k  , 32);
    memcpy(k, tmp, 32);
}


static int test_x25519_51()
{
   	uint8_t _1   [32] = {0x42, 0x2c, 0x8e, 0x7a, 0x62, 0x27, 0xd7, 0xbc,
                    0xa1, 0x35, 0x0b, 0x3e, 0x2b, 0xb7, 0x27, 0x9f,
                    0x78, 0x97, 0xb8, 0x7b, 0xb6, 0x85, 0x4b, 0x78,
                    0x3c, 0x60, 0xe8, 0x03, 0x11, 0xae, 0x30, 0x79};
    uint8_t k[32] = {9};
    uint8_t u[32] = {9};

    Hacl_Curve25519_51_secret_to_public(k, u);
    int status = memcmp(k, _1, 32);

    uint8_t _1k  [32] = {0x68, 0x4c, 0xf5, 0x9b, 0xa8, 0x33, 0x09, 0x55,
                    0x28, 0x00, 0xef, 0x56, 0x6f, 0x2f, 0x4d, 0x3c,
                    0x1c, 0x38, 0x87, 0xc4, 0x93, 0x60, 0xe3, 0x87,
                    0x5f, 0x2e, 0xb9, 0x4d, 0x99, 0x53, 0x2c, 0x51};
    for(size_t i = 1; i < 1000; i++) { iterate_x25519_51(k, u); }
    status |= memcmp(k, _1k, 32);
    return status;
}

static int test_x25519_64()
{
   	uint8_t _1   [32] = {0x42, 0x2c, 0x8e, 0x7a, 0x62, 0x27, 0xd7, 0xbc,
                    0xa1, 0x35, 0x0b, 0x3e, 0x2b, 0xb7, 0x27, 0x9f,
                    0x78, 0x97, 0xb8, 0x7b, 0xb6, 0x85, 0x4b, 0x78,
                    0x3c, 0x60, 0xe8, 0x03, 0x11, 0xae, 0x30, 0x79};
    uint8_t k[32] = {9};
    uint8_t u[32] = {9};

    Hacl_Curve25519_64_secret_to_public(k, u);
    int status = memcmp(k, _1, 32);

    uint8_t _1k  [32] = {0x68, 0x4c, 0xf5, 0x9b, 0xa8, 0x33, 0x09, 0x55,
                    0x28, 0x00, 0xef, 0x56, 0x6f, 0x2f, 0x4d, 0x3c,
                    0x1c, 0x38, 0x87, 0xc4, 0x93, 0x60, 0xe3, 0x87,
                    0x5f, 0x2e, 0xb9, 0x4d, 0x99, 0x53, 0x2c, 0x51};
    for(size_t i = 1; i < 1000; i++) { iterate_x25519_64(k, u); }
    status |= memcmp(k, _1k, 32);
    return status;
}


int main(void) {
	int status = 0;
	
	status |= x25519_51();
	status |= x25519_64();

	// FULLs
	status |= test_x25519_51();	// RFC, slow passed
	status |= test_x25519_64();	// RFC, slow passed

	printf("%s\n", status != 0 ? "FAIL" : "OK");	
	return status;
}
