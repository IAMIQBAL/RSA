# RSA Implementation in C

This program implements the RSA cryptosystem algorithm. User has to provide two prime numbers. The program uses these prime numbers to produce the public and private keys. Using the keys, it can either encrypt or decrypt the sentence that is inputted by the user using the RSA algorithm. The encrypted text is saved in a text file which is can be then decrypted by providing the decryption exponent.  

Moreover, RSA is reimplemented in rsabig.h, which uses gmp.h library to do calculation on big numbers.
