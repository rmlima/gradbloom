/*
##################
### @ Rui Lima ###
### 09-10-2014 ###
##################
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mhash.h>

#define KEYSIZE 16 //Também é o tamanho máximo para o K

#define M 256 //Tamanho do bloom filter
#define K 4



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

void mostra_bloom(float *bloom)
{
int i;
printf("##### Conteudo do FILTRO ########\n");
printf("bloom:\n");
for (i=0 ; i<M; i++)
	{
        printf("%.2f ",bloom[i]);
	if (!(i % 10)) { printf("\n");}
	}
printf("\n");
}



void inserir(char *elem,float p,float *bloom)
{
int j,idx;
unsigned char chave[KEYSIZE];

md5(elem,chave);
mostra_md5(elem,chave);

for (j=0 ; j<K; j++)
   {
   idx=chave[j];
   printf("Pos: %d ", idx);
   bloom[idx]=max(p,bloom[idx]);
   }
printf("\n");
}

float contem(char *elem,float *bloom)
{
int j,idx;
float result;
unsigned char chave[KEYSIZE];

md5(elem,chave);
result=1;

for (j=0; j<K; j++)
	idx=chave[j];

result=min(result,bloom[idx]);
return result;
}

void combinar(float *bloom1, float *bloom2, float *forward)
{
int j;
float att = 0.5;

for (j=0 ; j<M; j++)
   {
   forward[j]=max(bloom1[j],bloom2[j]*att);
   }
}

float pesquisa(char *elem,float *bloom)
{
int j,idx;
float result;
unsigned char chave[KEYSIZE];

md5(elem,chave);
result=1;

for (j=0; j<K; j++)
	{
	idx=chave[j];
	result=min(result,bloom[idx]);
	}

return (1-result);
}


int main( void )
{
int i;
float delay;
float bloom1[M];  //Filtro Recursos Próprios
float bloom2[M];  //Gradiente recebido
float forward[M]; //Adicao da informação própria ao gradiente existente

for (i=0 ; i<M; i++)
{
	bloom1[i]=0;
    bloom2[i]=0;
}


//Carregar recursos no filtro
inserir("recurso1",1,bloom1);
inserir("recurso2",1,bloom1);
mostra_bloom(bloom1);
//Verificar se existem estes recursos, ou seja se p>0
printf("recurso1 \t[p]=%f\n",contem("recurso1",bloom1));
printf("recurso2 \t[p]=%f\n",contem("recurso2",bloom1));
printf("recurso3 \t[p]=%f\n",contem("recurso3",bloom1));


printf("#############################\n");
printf("### Usar os dois vectores ###\n");
printf("#############################\n");
//Simular informação de um vizinho com histórico
inserir("recurso3",1,bloom2);
inserir("recurso4",1,bloom2);
inserir("recurso5",0.5,bloom2);
inserir("recurso6",0.4,bloom2);
inserir("recurso7",0.3,bloom2);
//O vector bloom2 já tem informação de gradiente
mostra_bloom(bloom2);

//Adicionar informação própria ao gradiente existente
combinar(bloom1,bloom2,forward);
//O vector a ser renviado será
mostra_bloom(forward);

printf("#############################\n");
printf("####### Decisão no nó #######\n");
printf("#############################\n");
//Se um nó receber este gradiente deve aumentar o delay ?
delay=pesquisa("recurso3",forward);
if (delay)
	printf("Atraso adicionado para o recurso3 = 2*HOP+%f*DELAY\n",delay);
else
	printf("O nó detem o recursos\n");
//Mas um delay=0,5 significa que há um vizinho que tem o recurso... que se faz com isto ?



exit(0);
}
