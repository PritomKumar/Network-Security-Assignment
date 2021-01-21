#include <openssl/des.h>

#include <openssl/des.h>
#include <stdio.h>
#include <string.h>

#define ENC 1
#define DEC 0

int hex_to_int(char c)
{
	int dig = 0;
	switch (c)
	{
	case 'A':
		dig = 10;
		break;
	case 'B':
		dig = 11;
		break;
	case 'C':
		dig = 12;
		break;
	case 'D':
		dig = 13;
		break;
	case 'E':
		dig = 14;
		break;
	case 'F':
		dig = 15;
		break;
	default:
		dig = c - 0x30;
	}
	return dig;
}

int hex_to_ascii(char c, char d)
{
	int high = hex_to_int(c) * 16;
	int low = hex_to_int(d);
	// printf("\nhigh = %d low = %d  \n", high, low);
	return high + low;
}
unsigned char *hexToAsciiString(char *hexString, char *array)
{

	char *st = NULL;
	// printf("Before st\n\n");
	st = hexString;
	unsigned char ascii[8];
	unsigned char ascii2[8];
	int length = strlen(st);
	// printf("Before for loop\n\n");

	for (int i = 0, j = 0; i < length; i += 2, j++)
	{
		unsigned char c = (unsigned char)hex_to_ascii(st[i], st[i + 1]);
		array[j] = c;
	}
	// printf("After for loop\n\n");
	// printf("ascii = %s\n", ascii);
	return ascii;
}

int main(int argc, char *argv[])
{
	int k;
	unsigned in[2];
	static unsigned char cbc_key[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
	unsigned char input[8] = {'p', 'r', 'i', 't', 'o', 'm', '1', '9'};
	unsigned char iv[8];
	hexToAsciiString(argv[1], iv);
	printf("IV = %s\n", iv);
	// printf("After IV\n\n");
	unsigned char desKey[8];
	hexToAsciiString(argv[2], desKey);
	printf("desKey = %s\n", desKey);
	char *readFileName = argv[3];
	char *writeFileName = argv[4];
	FILE *fp, *fp2;

	unsigned char buff[10000];
	fp = fopen(readFileName, "r");
	fp2 = fopen(writeFileName, "w+");

	fscanf(fp, "%s", buff);
	//  printf("\n1 : %s\n", buff );
	//fprintf(fp2, "This is testing for fprintf...\n");

	int LENGTH = 8;
	const char plainone[16] = "PlainOne";
	const char plaintwo[16] = "PlainTwo";
	char xor[8];
	int temp[8];
	int i;

	for (i = 0; i < LENGTH; ++i)
	{
		xor[i] = (char)(desKey[i] ^ input[i]);
		temp[i] = (int)xor[i];
	}

	printf("PlainText One: %s\nPlainText Two: %s\n\none^two: ", desKey, input);
	for (i = 0; i < LENGTH; i++){
		printf("%c", xor[i]);
	}
	printf("\n");
	for (i = 0; i < LENGTH; i++){
		printf("%d", temp[i]);
	}
		
	printf("\n");

	des_key_schedule key;

	if ((k = des_set_key_checked(&cbc_key, key)) != 0)
	{
		printf("\nkey error\n");
	}

	printf("DES Clear Text: ");
	printf("%s\n", input);

	des_encrypt1(input, key, ENC);

	printf("DES Encryption: ");
	printf("%s\n", input);

	des_encrypt1(input, key, DEC);
	printf("DES Decription: ");
	printf("%s\n", input);

	printf("%s\n", iv);

	fclose(fp);
	fclose(fp2);
}
