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
unsigned char *hexToAsciiString(char *hexString)
{
	char *st = hexString;
	static unsigned char ascii[8];
	int length = strlen(st);
	int i;
	char buf = st[0];
	for (int i = 0, j = 0; i < length - 1; i += 2, j++)
	{
		// printf( "buf =  %c\n ",buf);
		// printf("%c", (unsigned char)hex_to_ascii(st[i], st[i + 1]));
		// printf(" %d ", hex_to_ascii(buf, st[i]));
		unsigned char c = (unsigned char)hex_to_ascii(st[i], st[i + 1]);
		ascii[j] = c;
	}
	// printf("\n");
	// for (int i = 0; i < 8; i++)
	// {
	// 	printf("%c", ascii[i]);
	// }
	// printf("FUctions = %s\n",ascii);

	return &ascii;
}

int main(int argc, char *argv[])
{
	int k;
	unsigned in[2];
	static unsigned char cbc_key[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
	unsigned char input[8] = {'p', 'r', 'i', 't', 'o', 'm', '1', '9'};
	unsigned char * iv = hexToAsciiString(argv[1]);
	unsigned char * desKey = hexToAsciiString(argv[2]);

	des_key_schedule key;

	if ((k = des_set_key_checked(&cbc_key, key)) != 0)
	{
		printf("\nkey error\n");
	}

	in[0] = 3212314;
	in[1] = 1231233;

	printf("DES Clear Text: ");
	printf("%s\n",input);

	des_encrypt1(input, key, ENC);

	printf("DES Encryption: ");
	printf("%s\n",input);

	des_encrypt1(input, key, DEC);
	printf("DES Decription: ");
	printf("%s\n",input);

	
	printf("%s\n",iv);
}
