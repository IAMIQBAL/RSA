#include <stdio.h>
#include <string.h>
#include <math.h>
#include <gmp.h>

void calculatePHINBig(mpz_t p, mpz_t q, mpz_t phin);
int isPrimeBig(mpz_t n);
void encExponentBig(mpz_t p, mpz_t q, mpz_t e, mpz_t n, mpz_t phin);
void decExponentBig(mpz_t e, mpz_t phin, mpz_t d);
void eqnPowModBig(mpz_t a, mpz_t b, mpz_t n, mpz_t x);

int isPrimeBig(mpz_t n){
    int isPrime = -1;
    isPrime = mpz_probab_prime_p(n, 10);
    return isPrime;
}

void encExponentBig(mpz_t p, mpz_t q, mpz_t e, mpz_t n, mpz_t phin){

    mpz_mul(n, p, q);
    calculatePHINBig(p, q, phin);
    mpz_t range;
    mpz_init_set_str(range, "999999999", 10);

    mpz_t gcd;
    mpz_init(gcd);

    mpz_t one;
    mpz_init_set_str(one, "1", 10);

    for (mpz_set(e, n); mpz_cmp(e, range) != 0; mpz_add_ui(e,e,1)){
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

    mpz_set_ui(d, 0);
    mpz_t range, eTemp;

    // Make range big to loop for big d when p and q are big
    mpz_init_set_str(range, "999999999", 10);

    mpz_t r, s, one;
    mpz_init(r);
    mpz_init(s);
    mpz_init_set(eTemp, e);

    mpz_init_set_str(one, "1", 10);

    mpz_add(d, eTemp, one);
    for (mpz_set(d, d); mpz_cmp(d,range)!=0; mpz_add_ui(d,d,1)){
        mpz_mul(r, d, eTemp);
        mpz_mod(s, r, phin);
        if (mpz_cmp_ui(s, 1) == 0){
            break;
        }
    }

}

void eqnPowModBig(mpz_t a, mpz_t b, mpz_t n, mpz_t x){

    mpz_t y, r, m, mm;

    mpz_set_str(x, "1", 10);
    mpz_set(y, a);
    mpz_init(r);
    mpz_init(m);

    while (mpz_cmp_ui(b, 0) == 1){
        if (mpz_mod_ui(r, b, 2) == 1){
            mpz_mul(m, x, y);
            mpz_mod(x, m, n);
        }
        mpz_mul(y, y, y);
        mpz_mod(y, y, n);
        mpz_div_ui(b,b,2);
    }
    mpz_mod(x, x,n);
}