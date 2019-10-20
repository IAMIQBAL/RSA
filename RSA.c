#include <stdio.h>
#include <math.h>
#include <string.h>
#include "RSA.h"

int main(){
    //TODO add binary padding and random numbers and hexdec and save to file and read
    int keys[4];
    genKeys(65537, 19, keys);
    
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

    for (int i = 0; i < strlen(word); i++){
        dec = equationPowMod(enc[i], d, n);
        printf("Decrypted: %c\n", dec);
    }
    // printf("Encrypted: %d\n", text);

    // int dec;

    // dec = equationPowMod(text, d, n);
    // printf("Decrypted: %c\n", dec);


    return 0;
}

