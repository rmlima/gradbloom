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

#define M 100
#define K 4

float bloom[M+K]; //Filtro Global



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
printf("bloom[]=");
for (i=0 ; i<M; i++)
	{
        printf("%f ",bloom[i]);
	if (!(i % 10)) { printf("\n");}
	}
printf("\n");
}



void inserir(char *elem,float p)
{
int i,j,sum,idx;

for (j=0 ; j<K; j++)
   {
   sum=0;
   for (i=0 ; i<sizeof(elem); i++)
	sum+=elem[i]*elem[i];
   idx=((sum+j) % M);
   printf("%d",idx);
   bloom[idx]=max(p,bloom[idx]);
   }
//printf("\n sum = %d\n",sum);
}


float ler(char *elem)
{
int i,j,sum,idx;
float result;
sum=0;
result=0;

for (i=0 ; i<sizeof(elem); i++)
	sum+=elem[i]*elem[i];

idx=(sum % M);
printf("%d",idx);

result=bloom[idx];
for (j=0; j<K; j++)
    result=min(result,bloom[idx+j]);
return result;
//printf("\n sum = %d\n",sum);
}




int main( void )
{
int i;

for (i=0 ; i<M; i++)
	bloom[i]=0;



//inserir("teste",0.5);


mostra_bloom();

printf("teste \t[p]=%f\n",ler("teste"));


exit(0);
}
