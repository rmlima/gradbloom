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

#define M 256
#define K 4

float bloom[M]; //Filtro Global



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

int mostra_md5(char *recurso, unsigned char chave[KEYSIZE])
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

void mostra_bloom(void)
{
int i;
printf("##### Conteudo do FILTRO ########\n");
printf("Vector bloom[]:\n");
for (i=0 ; i<M; i++)
	{
        printf("%.2f ",bloom[i]);
	if (!(i % 10)) { printf("\n");}
	}
printf("\n");
}



void inserir(char *elem,float p)
{
int j,idx;
unsigned char chave[KEYSIZE];

md5(elem,chave);
mostra_md5(elem,chave);

for (j=0 ; j<K; j++)
   {
   //idx=chave[2*j]+chave[2*j+1];
   idx=chave[j];
   printf("Pos: %d ", idx);
   bloom[idx]=max(p,bloom[idx]);
   }
   printf("\n");
}

float contem(char *elem)
{
int j,idx;
float result;
unsigned char chave[KEYSIZE];

md5(elem,chave);
result=2;
for (j=0; j<K; j++)
	idx=chave[j];
    result=min(result,bloom[idx]);
return result;
//printf("\n sum = %d\n",sum);
}




int main( void )
{
int i;

for (i=0 ; i<M; i++)
	bloom[i]=0;



inserir("teste",0.5);

inserir("teste1",0.3);

mostra_bloom();


//Verificar se existem estes recursos, ou seja p>0
printf("teste \t[p]=%f\n",contem("teste"));
printf("teste1 \t[p]=%f\n",contem("teste1"));
printf("teste2 \t[p]=%f\n",contem("teste2"));

exit(0);
}
