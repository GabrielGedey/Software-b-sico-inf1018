#include <stdlib.h>
#include <stdio.h>
#include "converte.h"



int utf2varint(FILE *arq_entrada, FILE *arq_saida)
{
  char carac[4];
  int caracLen;
  while (fread((carac), 1, 1, arq_entrada))
  {
    unsigned char ident = (carac[0] >> 3);
    if (ident == 254)
    {
      caracLen = 4;
    }
    else if (ident >= 252)
    {
      caracLen = 3;
    }
    else if (ident >= 248)
    {
      caracLen = 2;
    }
    else
    {
      caracLen = 1;
    }
    for (int i = 0; i < caracLen - 1; i++)
    {
      
      fread((carac+i), 1, 1, arq_entrada);
    }
    if (caracLen == 1)
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
