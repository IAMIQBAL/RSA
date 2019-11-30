#include <stdio.h>
#include <math.h>
#include <string.h>
#include "RSA.h"
#include "rsabig.h"
#include <gmp.h>
#include "fileopr.h"

void readNumber(int arr[], int size);

int main(){

    // Module RSA.h
    int modCo = 0;

    printf("Choose Module for Encryption\n1 For RSA\n2 For RSABig: ");
    scanf("%d", &modCo);

    if (modCo == 1){
        printf("\t\tModule RSA.h\n");

        int keys[4];
        genKeys(65537, 5741, keys);

        int e = keys[0];
        int n = keys[1];
        int phin = keys[2];
        int d = keys[3];
        int dec;

        printKeys(e, n, phin, d);

        // change input size here if encrypting long messages
        char word[100];
        int enc[100];

        printf("Enter Text (For encryption): ");
        scanf("%*[\n]%[^\n]]*", word);

        // Encryption text can be seen in encrypted.txt file
        for (int i = 0; i < strlen(word); i++){
            enc[i] = powMod(word[i], e, n);
            printf("Encrypted: %d\n", enc[i]);
        }
        
        writeFile(enc, strlen(word));
        writeBinFile(enc, strlen(word));

        int data[100];
        readFile(data);

        printf("Decrypted: ");
        for (int i = 0; i < strlen(word); i++){
            dec = powMod(data[i], d, n);
            printf("%c", dec);
        }

        printf("\n");
    } else if (modCo == 2){

        // Module rsabig.h

        printf("-----------------------------------\n\t\tModule rsabig.h\n");
    
        char ch;
        printf("Press P for decoding pre-existing file\nPress N for new Encryption: ");
        scanf(" %c", &ch);

        if (ch == 'N' || ch == 'n'){

            char word[100];
            int enc[100];

            printf("Enter Text (For encryption): ");
            scanf("%s", word);
            // printf("%s\n", word);

            mpz_t p, q, n1, e1, phin1, d1;
            mpz_t qx, lx;
            mpz_t array[100];
            mpz_t array2[100];

            // Initialize variables
            mpz_init_set_str(p, "32317006071311007300714876688669951960444102669715484032130345427524655138867890893197201411522913463688717960921898019494119559150490921095088152386448283120630877367300996091750197750389652106796057638384067568276792218642619756161838094338476170470581645852036305042887575891541065808607552399123930385521914333389668342420684974786564569494856176035326322058077805659331026192708460314150258592864177116725943603718461857357598351152301645904403697613233287231227125684710820209725157101726931323469678542580656697935045997268352998638215525166389647960126939249806625440700685819469589938384356951833568218188663", 10);
            mpz_init_set_str(q, "32317006071311007300714876688669951960444102669715484032130345427524655138867890893197201411522913463688717960921898019494119559150490921095088152386448283120630877367300996091750197750389652106796057638384067568276792218642619756161838094338476170470581645852036305042887575891541065808607552399123930385521914333389668342420684974786564569494856176035326322058077805659331026192708460314150258592864177116725943603718461857357598351152334063994785580370721665417662212881203104945914551140008147396357886767669820042828793708588252247031092071155540224751031064253209884099238184688246467489498721336450133889385773", 10);
            mpz_init(qx);
            mpz_init(lx);
            mpz_init(n1);
            mpz_init(e1);
            mpz_init(phin1);
            mpz_init(d1);
            
            genKeysBig(p,q,e1,n1,phin1,d1);
            printKeys(n1,e1,phin1,d1);

            // Using same string given earlier

            for (int i = 0; i < strlen(word); i++){
                mpz_init(array[i]);
                mpz_set_ui(array[i], word[i]);
            }

            FILE *fl;

            fl = fopen("rsabig.txt", "w");

            for (int i = 0; i < strlen(word); i++){
                gmp_printf("Before Encoding: %Zd\n", array[i]);
                mpz_powm(qx, array[i], e1, n1);
                
                gmp_printf("After Encoding: %Zd\n", qx);
                writeFileBig(fl, qx);
                mpz_init_set(array2[i], qx);
            }
            fclose(fl);

            char choice;
            printf("Do you want to Decode the Input Message?");
            scanf(" %c", &choice);

            if (choice == 'Y' || choice == 'y'){
                FILE *msg;
                msg = fopen("rsabig.txt", "r");
                Decoder(msg, strlen(word), n1, d1);
                fclose(msg);
            } else {
                mpz_clear(lx);
                mpz_clear(qx);
                mpz_clear(d1);
                mpz_clear(n1);
                mpz_clear(e1);
                mpz_clear(phin1);
            }
        } else if (ch == 'P' || ch == 'p'){
            FILE *fl;
            fl = fopen("rsabig.txt", "r");
            int nLines = 0;
            mpz_t n1, d1;
            mpz_init(n1);
            mpz_init(d1);

            printf("Enter Number of Lines in File to be decoded: ");
            scanf("%d", &nLines);

            gmp_printf("Enter value of N: ");
            gmp_scanf("%Zd", n1);

            gmp_printf("Enter value of D: ");
            gmp_scanf("%Zd", d1);

            Decoder(fl, nLines, n1, d1);
        } else {
            printf("Something went wrong\n");
        }
    } else {
        printf("Wrong Input\n");
    }

    return 0;
}