#include <iostream>
#include "present.h"
#include "byte2x4.h"

present::present() {}

char* present::encrypt(const void* plaintext, const void* key) {
	const unsigned __int8* key_u8 = (const unsigned __int8*)key;
	// wygenerowanie kluczy rundowych
	unsigned __int64* subKeys = genSubKeys(key_u8);
	// wpisanie tekstu jawnego do stanu wewnêtrznego
	unsigned __int64* state = (unsigned __int64*)plaintext;

	for (int i = 0; i < 31; i++) {
		// xorowanie stanu z kluczem rundy
		*state = *state ^ subKeys[i];
		// konwertowanie stanu na bajty
		byte2x4* stateBytes = (byte2x4*)state;
		// podstawienie przez Sbox
		for (int j = 0; j < 8; j++) {
			stateBytes[j].lower = getSbox(stateBytes[j].lower);
			stateBytes[j].higher = getSbox(stateBytes[j].higher);
		}
		*state = permute(stateBytes);
		free(stateBytes);
	}
	*state = *state ^ subKeys[31];
	free(subKeys);
	char* ret = (char*)state;
	return ret;
}

unsigned __int64* present::genSubKeys(const unsigned __int8* key) {
	// 80-bitowy klucz dzielony jest na 2 zmienne. 64-bitowe keyHigh i 16-bitowe keyLow
	unsigned __int64* keyHigh = (unsigned __int64*)key;
	unsigned __int16* keyLow = (unsigned __int16*)(key + 8);

	// alokowanie pamiêci na 32 kluce rundy
	unsigned __int64* subKeys = (unsigned __int64*)calloc(Nr, sizeof(unsigned __int64));

	// pierwszy klucz rundy to keyHigh
	if (subKeys == NULL) {
		return NULL;
	}
	else {
		subKeys[0] = *keyHigh;
	}
	for (int counter = 0; counter < Nr; counter++) {
		// przesuniêcie klucza lewo o 61 bitów
		unsigned __int64 temp1 = *keyHigh, temp2 = *keyLow;
		*keyHigh = (*keyHigh << 61) | (temp2 << 45) | (temp1 >> 19);
		*keyLow = ((temp1 >> 3) & 0xFFFF);

		// najbardziej znacz¹ce 4 bity s¹ zmieniane przez Sbox
		unsigned __int8 temp = getSbox(*keyHigh >> 60);
		// poprzednia wartoœæ 4 bitów ustawiana na 0
		*keyHigh = *keyHigh & 0x0FFFFFFFFFFFFFFFLL;
		// wprowadzenie nowych 4 bitów
		*keyHigh = *keyHigh | (((unsigned __int64)temp) << 60);
		// xorowanie k19, k18, k17, k16, k15 z licznikiem rundy
		*keyLow = *keyLow ^ ((counter & 0x01) << 15);
		*keyHigh = *keyHigh ^ (counter >> 1);
		// zapisanie 64bitowych kluczy
		subKeys[counter] = *keyHigh;
	}
	return subKeys;
}

unsigned __int8 present::getSbox(unsigned __int8 input) {
	return Sbox[input];
}

unsigned __int8 present::getInvSbox(unsigned __int8 input) {
	return invSbox[input];
}

unsigned __int64 present::permute(const void* source) {
	unsigned __int64* source_u64 = (unsigned __int64*) source;
	unsigned __int64 permutation = 0;
	int i;
	for (i = 0; i < 64; i++) {
		int distance = 63 - i;
		permutation = permutation | ((*source_u64 >> distance & 0x1) << (63 - P[i]));
	}
	return permutation;
}

