#include <stdio.h>
#include <string.h>
#include <math.h>
#include <gmp.h>

void calculatePHINBig(mpz_t p, mpz_t q, mpz_t phin);
int isPrimeBig(mpz_t n);
void encExponentBig(mpz_t p, mpz_t q, mpz_t e, mpz_t n, mpz_t phin);

int isPrimeBig(mpz_t n){
    int isPrime = -1;
    isPrime = mpz_probab_prime_p(n, 10);
    return isPrime;
}

void encExponentBig(mpz_t p, mpz_t q, mpz_t e, mpz_t n, mpz_t phin){

    mpz_mul(n, p, q);
    calculatePHINBig(p, q, phin);

    mp_size_t ph, eSize;

    mpz_t randomE;
    mpz_init(randomE);

    mpz_random(randomE, ph);

    mpz_t gcd;
    mpz_init(gcd);

    mpz_t one;
    mpz_init_set_str(one, "1", 10);

    for (mpz_set(e, randomE); mpz_cmp(e, phin) != 0; mpz_add_ui(e,e,1)){
        mpz_gcd(gcd, phin, e);
        if(mpz_cmp_ui(gcd, 1) == 0){
            break;
        }
    }
}

void calculatePHINBig(mpz_t p, mpz_t q, mpz_t phin){

    mpz_init(phin);
    mpz_set_ui(phin, 0);
    
    mpz_sub_ui(p,p,1);
    mpz_sub_ui(q,q,1);

    mpz_mul(phin,p,q);
}

void genKeysBig(mpz_t p, mpz_t q, mpz_t e, mpz_t n, mpz_t phin){

    //TODO
}

void decExponentBig(mpz_t e, mpz_t phin, mpz_t d){

    //TODO
}

void eqnPowModBig(mpz_t a, mpz_t b, mpz_t n, mpz_t res){

    //TODO
}