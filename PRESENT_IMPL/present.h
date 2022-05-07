#ifndef PRESENT
#define PRESENT

//#include "defines.cpp"
class present
{
	// liczba rund
	const __int8 Nr = 32;
	// zdefiniowanie Sboxa
	const unsigned __int8 Sbox[16] = { 0xC, 0x5, 0x6, 0xB, 0x9, 0x0, 0xA, 0xD, 0x3, 0xE, 0xF, 0x8, 0x4, 0x7, 0x1, 0x2 };
	// zdefiniowanie odwróconego Sboxa
	const unsigned __int8 invSbox[16] = { 0x5, 0xe, 0xf, 0x8, 0xC, 0x1, 0x2, 0xD, 0xB, 0x4, 0x6, 0x3, 0x0, 0x7, 0x9, 0xA };
	// zdefiniowanie permutacji
	const unsigned __int8 P[64] = { 0, 16, 32, 48, 1, 17, 33, 49, 2, 18, 34, 50, 3, 19, 35, 51,
						4, 20, 36, 52, 5, 21, 37, 53, 6, 22, 38, 54, 7, 23, 39, 55,
						8, 24, 40, 56, 9, 25, 41, 57, 10, 26, 42, 58, 11, 27, 43, 59,
						12, 28, 44, 60, 13, 29, 45, 61, 14, 30, 46, 62, 15, 31, 47, 63 };
public:
	present();

	// funkcja szyfruj¹ca
	char* encrypt(const void* plaintext, const void* key);

	// funkcja generuj¹ca klucze
	unsigned __int64* genSubKeys(const unsigned __int8* key);

	// pozyskanie odpowiadaj¹cej wartoœci z Sboxa
	unsigned __int8 getSbox(unsigned __int8 input);

	// pozyskanie odpowiadaj¹cej wartoœci z invSboxa
	unsigned __int8 getInvSbox(unsigned __int8 input);

	// funkcja permutuj¹ca wejœcie
	unsigned __int64 permute(const void* source);
};


#endif // !PRESENT

