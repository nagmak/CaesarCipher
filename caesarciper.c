/*
Caesar cipher - Implement a Caesar cipher, both encoding and decoding. 
The key is an integer from 1 to 25. This cipher rotates the letters of the alphabet (A to Z). 
The encoding replaces each letter with the 1st to 25th next letter in the alphabet (wrapping Z to A). 
So key 2 encrypts "HI" to "JK", but key 20 encrypts "HI" to "BC". 
This simple "monoalphabetic substitution cipher" provides almost no security, 
because an attacker who has the encoded message can either use frequency analysis to guess the key, or just try all 25 keys.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sodium.h>// cryptographically secure for random num generation
#define ALPHABET_LENGTH 26
const uint32_t MAX = 26;

uint32_t swap_letters(uint32_t letter, uint32_t key);
int main(int argc, char **argv){
	if (argc < 1){ 
    	return 0; 
    }
	/* Initialize Sodium */
	if (sodium_init() == -1) {
        return 1;
    }

    /* Save user-input as strings */
    uint32_t strsize = 0;
    for (int i = 1; i < argc; i++){
    	strsize += strlen(argv[i]);
    	if (argc > i+1){ strsize++; }
    }

    /* Allocate memory for strings */
    char *plaintext;
    plaintext = malloc(strsize);
    plaintext[0] = '\0';

    for (int i = 1; i < argc; i++){
    	strcat(plaintext, argv[i]);
    	if (argc > i+1){ strcat(plaintext, " "); }
    }

    /* Encoding */
	uint32_t key;
	char ciphertext[strlen(plaintext)];
	char decodedtext[strlen(plaintext)];
	key = randombytes_uniform(MAX) + 1; // to run from 1 to max

	for(int i = 0; i < strlen(plaintext); i++){
		ciphertext[i] = swap_letters(plaintext[i], key);
	}
	printf("Key: %i\n", key);
	printf("Encoded Text: %s\n", ciphertext);

	/* Decoding */
	for (int i = 0; i < strlen(ciphertext); i++){
		decodedtext[i] = swap_letters(ciphertext[i], 26 - key);
	}

	printf("Decoded text(plaintext): %s\n", decodedtext);

}

uint32_t swap_letters(uint32_t letter, uint32_t key){
	const char alphabet[ALPHABET_LENGTH*2] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
	const char alphabet_upper[ALPHABET_LENGTH*2] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (islower(letter)){
		return alphabet[letter - 'a' + key];
	}
	else if (isupper(letter)){
		return alphabet[letter - 'A' + key];
	}
	else{
		return letter;
	}
}