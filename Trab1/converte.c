#include <stdlib.h>
#include <stdio.h>
#include "converte.h"



int utf2varint(FILE *arq_entrada, FILE *arq_saida)
{
  unsigned char carac[4];
  unsigned char temp;
  while (fread((carac), 1, 1, arq_entrada))
  {
    unsigned char ident = (carac[0] >> 3);
    if (ident == 30)
    {
      fread((carac+1), 1, 3, arq_entrada);
    }
    else if (ident >= 28)
    {
      fread((carac+1), 1, 2, arq_entrada);
      temp = carac[1] << 6;
      carac[2] = carac[2] | temp;
      carac[2] = carac[2] & 0x7F;
      
      temp = carac[0] << 6;
      carac[1] = carac[1] | temp;
      carac[1] = carac[1] & 0x7F;
      
      carac[1] = carac[1] >> 1;
      carac[1] = carac[1] & 0x1F;
      carac[0] = carac[0] | 0x80;
      fwrite(carac, 1, 3, arq_saida);
    }
    else if (ident >= 24)
    {
      fread((carac+1), 1, 1, arq_entrada);
      temp = carac[0] << 6;
      carac[1] = carac[1] | temp;
      carac[1] = carac[1] & 0x7F;
      
      carac[0] = carac[0] >> 1;
      carac[0] = carac[0] & 0x0F;
      carac[0] = carac[0] | 0x80;
      fwrite(carac, 1, 2, arq_saida);
      return;
      
    }
    else
    {
      fwrite(carac, 1, 1, arq_saida);
    }
    
  }
  return 0;
}

int varint2utf(FILE *arq_entrada, FILE *arq_saida)
{
  return 0;
}
