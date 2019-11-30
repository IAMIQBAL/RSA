#include <stdio.h>
#include <gmp.h>

void calculatePHINBig(mpz_t p, mpz_t q, mpz_t phin);
int isPrimeBig(mpz_t n);
void encExponentBig(mpz_t p, mpz_t q, mpz_t e, mpz_t n, mpz_t phin);
void decExponentBig(mpz_t e, mpz_t phin, mpz_t d, mpz_t n);
void eqnPowModBig(mpz_t a, mpz_t b, mpz_t n, mpz_t x);
void genKeysBig(mpz_t p, mpz_t q, mpz_t e, mpz_t n, mpz_t phin, mpz_t d);
void printKeys(mpz_t n, mpz_t e,mpz_t phin ,mpz_t d);
void initKeys(mpz_t p, mpz_t q, mpz_t n, mpz_t e, mpz_t phin, mpz_t d);
void Decoder(FILE *file, int size, mpz_t n, mpz_t d);

int isPrimeBig(mpz_t n){
    int isPrime = -1;
    isPrime = mpz_probab_prime_p(n, 10);
    return isPrime;
}

void encExponentBig(mpz_t p, mpz_t q, mpz_t e, mpz_t n, mpz_t phin){

    mpz_mul(n, p, q);
    calculatePHINBig(p, q, phin);

    mpz_t gcd;
    mpz_init(gcd);

    mpz_t initE;
    mpz_init_set_str(initE, "48552962525444623306758594028804316966546241000198426809413353988758613146319", 10);

    for (mpz_set(e, initE); mpz_cmp(e, phin) != 0; mpz_add_ui(e,e,1)){
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

void genKeysBig(mpz_t p, mpz_t q, mpz_t e, mpz_t n, mpz_t phin, mpz_t d){

    encExponentBig(p, q, e, n, phin);
    decExponentBig(e, phin, d, p);
}

void decExponentBig(mpz_t e, mpz_t phin, mpz_t d, mpz_t p){

    mpz_sub_ui(p, p, 1);
    if (mpz_invert(d,e,phin) == 0){
        printf("Invert does not exist\n");
    }
}

void eqnPowModBig(mpz_t message, mpz_t b, mpz_t n, mpz_t x){

    mpz_t y, r, m, mm;

    mpz_set_ui(x,1);
    mpz_set(y, message);
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

void printKeys(mpz_t n, mpz_t e,mpz_t phin ,mpz_t d){
    gmp_printf("n: %Zd\n", n);
    gmp_printf("e: %Zd\n", e);
    gmp_printf("phin: %Zd\n", phin);
    gmp_printf("d: %Zd\n", d);
}
