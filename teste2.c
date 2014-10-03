#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mhash.h>

#define KEYSIZE  16

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

int mostra(char *recurso, unsigned char chave[KEYSIZE])
{
 int i;
 
 printf("Dados: %s",recurso);
 printf("\t");
 printf("Hash:");
 for (i = 0; i < KEYSIZE; i++) {
        printf("%.2x", chave[i]);
        }
 printf("\n");
 
 return 0;
 }


int main(void)
{
  unsigned char chave[KEYSIZE];
  char dados[100];
		
		strcpy(dados,"lixo1");
  md5(dados,chave);
  mostra(dados,chave);
        
  strcpy(dados,"lixo1");
  md5(dados,chave);
  mostra(dados,chave);
  
  strcpy(dados,"lixo2");
  md5(dados,chave);
  mostra(dados,chave);
  
exit(0);
}

