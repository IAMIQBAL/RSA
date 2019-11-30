#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Signatures
int calculatePHIN(int p, int q);
int isPrime(int n);
int getGCD(int x, int y);
void encExponent(int p, int q, int *keys);
int decExponent(int e, int phin, int n);
void genKeys(int p, int q, int keys[]);
int powMod(int a, int b, int n);
int euclidean(int arr[]);
void printKeys(int e, int n, int phin, int d);

int isPrime(int n){
    // Check for prime
    int m = n / 2;
    for (int i = 2; i <= m; i++){
        if (n % i == 0){
            return 0;
        }
    }
    return 1;
}

void encExponent(int p, int q, int *keys){
    int n;
    n = p * q; // Public key here is n, whereas p and q are kept private
    int phin = calculatePHIN(p, q);
    int e = 0; // Encryption key
    
    for (e = 2; e <= phin; e++){
        if (getGCD(phin, e) == 1){
            break;
        }
    }
    // Export e, n, phin
    int count = 2;
    keys[0] = e;
    keys[1] = n;
    keys[2] = phin;
}

int decExponent(int e, int phin, int n){
    
    int d = 0;

    // Equation

    // d = e^-1 mod (phin)
    // d * e = 1 mod (phin)
    // d * e / mod phin = 1 ----> keep iterating on d until other side becomes equal to 1

    d = n;
    while (1){
        if (((d * e) % phin) == 1){
            break;
        }
        d--;
    }

    return d;
}

void genKeys(int p, int q, int keys[]){

    // Call in main to get both Kpub and Kpriv
    encExponent(p, q, keys);
    int e = keys[0];
    int n = keys[1];
    int phin = keys[2];

    int d = decExponent(e, phin, n);
    keys[3] = d;
}

int calculatePHIN(int p, int q){
    // phi-n function
    int phin = (p-1) * (q - 1);
    return phin;
}

int getGCD(int num1, int num){
    // Greatest common divisor
    int gcd = 0;
    for (int i = 1; i <= num1 && i <= num; ++i){
        if (num1 % i == 0 && num % i == 0){
            gcd = i;
        }
    }
    return gcd;
}

int powMod(int data, int key, int n) {

    // Enc = M ^ e mod(n)
    // Dec = Enc ^ d mode(n)

    // Above equations are for general quation after Kpub and Kpriv are generated
	long int enc = 1, temp = data;

	for (;key > 0;key/=2) {
        if (key % 2 == 1){
			enc = (enc * temp) % n;
        }
		temp = (temp * temp) % n;
	}

	return enc % n;
}

int euclidean(int arr[]){

    // for future use
    int gcd = 0;
    int arr2[2];
    int temp = 0;

    while (1){
        if (arr2[0] != 0){
            arr2[0] = arr[0] % arr[1];
            arr[1] = arr[1];
        } else {
            break;
        }
    }
    gcd = arr2[1];
    return gcd;
}

void printKeys(int e, int n, int phin, int d){
    printf("Keys: (%d, %d)\n", e,n);
    printf("PHIN: %d\n", phin);
    printf("d: %d\n", d);
}