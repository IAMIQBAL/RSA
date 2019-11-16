#include <stdio.h>
#include <math.h>
#include <string.h>
#include "RSA.h"
#include "rsabig.h"

int main(){

    int keys[4];
    genKeys(65537, 19, keys); // 5741,17,1
    
    int e = keys[0];
    int n = keys[1];
    int phin = keys[2];
    int d = keys[3];
    int dec;
    printf("Keys: (%d, %d)\n", e,n);
    printf("PHIN: %d\n", phin);
    printf("d: %d\n", d);

    char word[100];
    int s[100];
    int enc[100];
    printf("Enter a Character: ");
    fgets(word, 100, stdin);
    printf("%s\n", word);

    for (int i = 0; i < strlen(word); i++){
        s[i] = word[i];
    }

    for (int i = 0; i < strlen(word); i++){
        enc[i] = equationPowMod(s[i], e, n);
        printf("Encrypted: %d\n", enc[i]);
    }
    writeFile(enc, strlen(word));
    writeBinFile(enc, strlen(word));

    int data[100];
    readFile(data);

    printf("Decrypted: ");
    for (int i = 0; i < strlen(word); i++){
        dec = equationPowMod(data[i], d, n);
        printf("%c", dec);
    }

    // Dummy Primes
    // 48552962525444623306758594028804316966546241000198426809413353988758613146319
    // 40242743371890990858447090570121699416382150234809337003026322521020751020083
    
    mpz_t p, q, n1, e1, phin1;
    mpz_t res, res2;

    mpz_init_set_str(p, "48552962525444623306758594028804316966546241000198426809413353988758613146319", 10);
    mpz_init_set_str(q, "40242743371890990858447090570121699416382150234809337003026322521020751020083", 10);
    mpz_init(res);

    mpz_init(n1);
    mpz_init(e1);
    mpz_init(phin1);
    
    encExponentBig(p, q, e1, n1, phin1);

    gmp_printf("p: %Zd\n", p);
    gmp_printf("q: %Zd\n", q);
    gmp_printf("n: %Zd\n", n1);
    gmp_printf("e: %Zd\n", e1);
    gmp_printf("phin: %Zd\n", phin1);
    
    return 0;
}

