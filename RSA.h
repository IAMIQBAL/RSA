#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculatePHIN(int p, int q);
int isPrime(int n);
int getGCD(int x, int y);
void readFile(int data[]);
void writeFile(int data[], int size);
void encExponent(int p, int q, int *keys);
int decExponent(int e, int phin);
void genKeys(int p, int q, int keys[]);
int equationPowMod(int a, int b, int n);
void writeBinFile(int data[], int size);
void readBinFile(int data[], int size);

int isPrime(int n){
    int m = n / 2;
    for (int i = 2; i <= m; i++){
        if (n % i == 0){
            return 0;
        }
    }
    return 1;
}

void encExponent(int p, int q, int *keys){
    int range = 2147483647;
    int n;
    n = p * q; // Public key here is n, whereas p and q are kept private
    int phin = calculatePHIN(p, q);
    int e = 0; // Encryption key
    
    // TODO Choose a random e that must be gcd
    for (e = 2; e<= phin; e++){
        if (getGCD(phin, e) == 1){
            break;
        }
    }
    int count = 2;
    keys[0] = e;
    keys[1] = n;
    keys[2] = phin;
}

void genKeys(int p, int q, int keys[]){

    encExponent(p, q, keys);
    int e = keys[0];
    int n = keys[1];
    int phin = keys[2];

    int d = decExponent(e, phin);
    keys[3] = d;
}

int decExponent(int e, int phin){
    
    int d = 0;
    int range = 2147483647;
    
    for (d = e + 1; d <= range; d++) {
		if ( ((d * e) % phin) == 1)
			break;
	}

    return d;
}

int calculatePHIN(int p, int q){
    int phin = (p-1) * (q - 1);
    return phin;
}


int getGCD(int x, int y){
    int gcd = 0;
    for (int i = 1; i <= x && i <= y; ++i){
        if (x % i == 0 && y % i == 0){
            gcd = i;
        }
    }
    return gcd;
}

int equationPowMod(int a, int b, int n) {
	long long x = 1, y = a;

	while (b > 0) {
		if (b % 2 == 1)
			x = (x * y) % n;
		y = (y * y) % n; // Squaring the base
		b /= 2;
	}

	return x % n;
}

void readFile(int data[]){
    FILE * fpointer;

    fpointer = fopen("encrypted.txt", "r");
    int i=0;
    int num;
    while(fscanf(fpointer, "%d", &num) > 0) {
        data[i] = num;
        i++;
    }
    fclose(fpointer);
}

//TODO Make one function and add mode for filing

void writeFile(int data[], int size){

    FILE * fpointer;
    fpointer = fopen("encrypted.txt", "w");
    
    for (int i = 0; i < size;i++){
        fprintf(fpointer, "%d\n",data[i]);
    }

    fclose(fpointer);
}

void writeBinFile(int data[], int size){

    FILE * fpointer;
    fpointer = fopen("encrypted.bin", "wb");

    for (int i = 0; i < size; i++){
        fwrite(&data[i], size, 1, fpointer);
    }
    fclose(fpointer);
}

void readBinFile(int data[], int size){
    
    FILE * fpointer;
    fpointer = fopen("encrypted.bin", "wr");

    int i = 0;
    int num;
    while (fread(&num, size, 1, fpointer)>0){
        data[i] = num;
        i++;
    }
    fclose(fpointer);
}