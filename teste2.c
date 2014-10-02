#include <stdio.h>
#include <stdlib.h>
#include <mhash.h>

unsigned char hash[16] md5(char *recurso)
{
int i;
MHASH td;
               unsigned char buffer;
               unsigned char hash[16];

               td = mhash_init(MHASH_MD5);

               if (td == MHASH_FAILED) exit(1);

               /*while (fread(&buffer, 1, 1, stdin) == 1) {
                       mhash(td, &buffer, 1);
               }*/
               mhash(td,recurso,sizeof);

               mhash_deinit(td, hash);

		return hash;
}


int main(void)
        {
               unsigned char chave[16];
int i;
		chave = md5("lixo1");

		printf("Start");
               printf("Hash:");
               for (i = 0; i < mhash_get_block_size(MHASH_MD5); i++) {
                       printf("%.2x", chave[i]);
               }
               printf("\n");

               exit(0);
        }

