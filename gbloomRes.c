/*
##################
### @ Rui Lima ###
### 02-10-2014 ###
##################
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mhash.h>

#define KEYSIZE 16




float max(float i, float j) {
	return (i > j) ? i : j;
}

float min(float i, float j) {
	return (i < j) ? i : j;
}

int md5(char *recurso, unsigned char hash[KEYSIZE])
{
 MHASH td;

 td = mhash_init(MHASH_MD5);
 if (td == MHASH_FAILED) return -1; else
 {
  mhash(td,recurso,sizeof(recurso));
  mhash_deinit(td, hash);
  return 0;
 }
}



int mostra_md5(char *recurso)
{
 int i;
 unsigned char hash[KEYSIZE];
 
 md5(recurso,hash);
 
 printf("Dados: %s",recurso);
 printf("\t");
 printf("Hash:");
 for (i = 0; i < KEYSIZE; i++) {
        printf("%.2x", hash[i]);
        }
 printf("\n");
 
 return 0;
 }


char convByte(char *byte)
{
	unsigned char temp;
	int x, shift = strlen(byte)-1;

	for (x=0; x<strlen(byte); x++, shift--)
	{
		switch (byte[x])
		{
			case '0':
				temp = temp & ~(1 << shift); break;
			case '1':
				temp = temp | (1 << shift ); break;
		}
	}
	//printChar(temp);
	return (temp);
}


char *decimal_to_binary(int n)
{
   int c, d, count;
   char *pointer;
 
   count = 0;
   pointer = (char*)malloc(8+1);
 
   if ( pointer == NULL )
      exit(EXIT_FAILURE);
 
   for ( c = 7 ; c >= 0 ; c-- )
   {
      d = n >> c;
 
      if ( d & 1 )
         *(pointer+count) = 1 + '0';
      else
         *(pointer+count) = 0 + '0';
 
      count++;
   }
   *(pointer+count) = '\0';
 
   return  pointer;
}


int main( void )
{
int i;
unsigned char buffer;
char word1[256];
char word2[256];

mostra_md5("1");

strcpy (word1,"1");

mostra_md5(word1);

printf("Introduza um numero\n");
scanf("%s" ,word2);

mostra_md5(word2);
printf("\n");

char a='1';
mostra_md5(&a);

char c;
printf("Outro	\n");
scanf(" %c", &c);
mostra_md5(&c);

   char *pointer;
   printf("Introduzir inteiro\n");
   scanf("%d",&i);
   pointer = decimal_to_binary(i);
   mostra_md5(pointer);
   i=1;
   mostra_md5(decimal_to_binary(i));
   i=2;
   mostra_md5(decimal_to_binary(i));
exit(0);
}
