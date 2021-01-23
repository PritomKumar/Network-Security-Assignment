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
	case 'a':
		dig = 10;
		break;
	case 'b':
		dig = 11;
		break;
	case 'c':
		dig = 12;
		break;
	case 'd':
		dig = 13;
		break;
	case 'e':
		dig = 14;
		break;
	case 'f':
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

void hexToAsciiString(char *hexString, char *array)
{
	char *st = NULL;
	st = hexString;
	int length = strlen(st);
	for (int i = 0, j = 0; i < length; i += 2, j++)
	{
		unsigned char c = (unsigned char)hex_to_ascii(st[i], st[i + 1]);
		int temp = hex_to_ascii(st[i], st[i + 1]);
		//printf("c= %c  num= %hhx i = %d  j= %d\n",c,temp,i,j);
		array[j] = c;
	}
}

unsigned char encryptedMessage[10000];
unsigned char decryptedMessage[10000];

void CBC_Encription(int startPoint, char *iv,FILE *fp2,des_key_schedule key,unsigned char *buff,int fileLenght){
	
	//printf("Inside func %s\n", desKey);
	if(startPoint >= fileLenght){
		return;
	}
	// printf("\nBuff = ");
	// for (int i = 0; i < fileLenght; ++i){
	// 	printf("%c",buff[i]);
	// }
	// printf("\n");
	// printf("Start Point = %d\n", startPoint);
	int LENGTH = 8;

	char xor[8];
	int temp[8];
	//unsigned char input[8] = {'p', 'r', 'i', 't', 'o', 'm', '1', '9'};
	 unsigned  char input[8];

	//unsigned char testKey[8] = "pritom19";
	for (int i = startPoint,j=0; i < startPoint + LENGTH; i++,j++)
	{
		input[j] = buff[i];
		temp[j] = input[j];
	}
	// printf("\nInput = ");
	// for (int i = 0; i < 8; ++i){
	// 	printf("%c",input[i]);
	// }
	// printf("\n\nstartpoint = %d and input = %s\n\n",startPoint,input);
	for (int i = 0; i < LENGTH; ++i)
	{
		xor[i] = (char)(iv[i] ^ input[i]);
	}

	// printf("PlainText One: %s\nPlainText Two: %s\n\none^two: ", iv, input);
	// for (int i = 0; i < LENGTH; i++)
	// {
	// 	printf("%c", xor[i]);
	// }
	// printf("\n");
	// for (int i = 0; i < LENGTH; i++)
	// {
	// 	printf("%hhx", temp[i]);
	// }
	// printf("\n");

	// printf("DES Clear Text: ");
	// printf("%s\n", input);

	des_encrypt1(xor, key, ENC);
	fprintf(fp2,"%s",xor);
	// printf("DES Encryption: ");
	// printf("%s\n", xor);
	// for (int i = 0; i < LENGTH; i++)
	// {
	// 	printf("%hhx", xor[i]);
	// }
	// printf("\n");

	for (int i = startPoint,j=0; i < startPoint + LENGTH; i++,j++)
	{
		encryptedMessage[i] = xor[j];
	}
	CBC_Encription(startPoint+8,xor,fp2,key,buff,fileLenght);

}

void CBC_Decrytion(int startPoint, char *iv,des_key_schedule key,unsigned char *buff,int fileLenght){
	
	//printf("Inside func %s\n", desKey);
	if(startPoint >= fileLenght){
		return;
	}
	// printf("\nBuff = ");
	// for (int i = 0; i < fileLenght; ++i){
	// 	printf("%c",buff[i]);
	// }
	// printf("\n");
	// printf("Start Point = %d\n", startPoint);
	int LENGTH = 8;

	char xor[8];
	char temp[8];
	//unsigned char input[8] = {'p', 'r', 'i', 't', 'o', 'm', '1', '9'};
	unsigned  char input[8];

	//unsigned char testKey[8] = "pritom19";
	for (int i = startPoint,j=0; i < startPoint + LENGTH; i++,j++)
	{
		input[j] = buff[i];
		temp[j] = input[j];
	}

	des_encrypt1(input, key, DEC);
	//fprintf(fp2,"%s",xor);
	// printf("DES Decryption: ");
	// printf("%s\n", input);
	// for (int i = 0; i < LENGTH; i++)
	// {
	// 	printf("%hhx", input[i]);
	// }
	// printf("\n");


	// printf("\nInput = ");
	// for (int i = 0; i < 8; ++i){
	// 	printf("%c",input[i]);
	// }
	// printf("\n\nstartpoint = %d and input = %s\n\n",startPoint,input);
	for (int i = 0; i < LENGTH; ++i)
	{
		xor[i] = (char)(iv[i] ^ input[i]);
	}

	// printf("PlainText One: %s\nPlainText Two: %s\n\none^two: ", iv, input);
	// for (int i = 0; i < LENGTH; i++)
	// {
	// 	printf("%c", xor[i]);
	// }
	// printf("\n");
	// for (int i = 0; i < LENGTH; i++)
	// {
	// 	printf("%hhx", temp[i]);
	// }
	// printf("\n");

	// printf("DES Clear Text: ");
	// printf("%s\n", input);

	for (int i = startPoint,j=0; i < startPoint + LENGTH; i++,j++)
	{
		decryptedMessage[i] = xor[j];
	}

	CBC_Decrytion(startPoint+8,temp,key,buff,fileLenght);

}

int main(int argc, char *argv[])
{
	
	if(argc!=5){
		printf("Please provide the required number of parameter.\n");
		printf("You should use the following format:------.\n");
		printf("\nProgram\t\tIV(Hexadicimal)\t\tKey(Hexadicimal)\t\tInputFile\tOutputFile\n\n");
		printf("Exiting....\n");
		exit(1);
	}
	unsigned char iv[8];
	hexToAsciiString(argv[1], iv);
	//hexToAsciiString("3030303030303030", iv);
	printf("IV = %s\n", iv);
	// printf("After IV\n\n");
	unsigned char desKey[8];
	hexToAsciiString(argv[2], desKey);
	printf("desKey = %s\n", desKey);
	char *readFileName = argv[3];
	char *writeFileName = argv[4];
	FILE *fp, *fp2;

	unsigned char buff[10000];
	for (int i = 0; i < 10000; i++)
	{
		buff[i] = '0';
	}
	

	fp = fopen(readFileName, "r");
	fp2 = fopen(writeFileName, "r+");

	int ch = getc(fp); 
	buff[0] = (char) ch;
	printf("\nMessage = ");
	int fileLenght = 0;
	for (int i=0;ch != EOF;i++)  
	{ 
		buff[i] = (char) ch;
		fileLenght = i;
		putchar(ch);  
		ch = getc(fp); 
	} 
	printf("\n");

	if(fileLenght%8!=0){
		fileLenght = fileLenght + (8-fileLenght%8);
	}

	//fscanf(fp, "%s", buff);
	//printf("\nfile Lenght = %d\n", fileLenght );
	//printf("\n1 : %s\n", buff );
	int k;
	des_key_schedule key;
	
	if ((k = des_set_key_checked(&desKey, key)) != 0)
	{
		printf("\nKey error\n");
	}

	CBC_Encription(0,iv,fp2,key,buff,fileLenght);

	printf("\nEncryted Message = ");
	for (int i = 0; i < fileLenght; ++i){
		printf("%c",encryptedMessage[i]);
	}
	printf("\n");
	unsigned char buffDecrypt[10000];
	for (int i = 0; i < 10000; i++)
	{
		buffDecrypt[i] = '0';
	}
	
	for (int i=0;i<fileLenght;i++)  
	{ 
		buffDecrypt[i] = encryptedMessage[i];
	} 

	CBC_Decrytion(0,iv,key,buffDecrypt,fileLenght);

	printf("\nDecrypted Message = ");
	for (int i = 0; i < fileLenght; ++i){
		printf("%c",decryptedMessage[i]);
	}
	printf("\n\n");
	//  printf("\n1 : %s\n", buff );
	//fprintf(fp2, "This is testing for fprintf...\n");


	// des_encrypt1(xor, key, DEC);
	// for (int i = 0; i < LENGTH; ++i)
	// {
	// 	input[i] = (char)(iv[i] ^ xor[i]);
	// }

	// printf("DES Decryption: ");
	// printf("%s\n", input);

	fclose(fp);
	fclose(fp2);
}
