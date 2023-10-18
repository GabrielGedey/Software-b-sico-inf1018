#include <stdio.h>
#include <stdlib.h>


int main(void)
{
  FILE* arq_in;
  arq_in = fopen("utf8_peq", "rb");
  if (arq_in == NULL)
  {
    printf("ERRO! O arquivo não foi aberto!\n");
    return 1;
  }
  FILE* arq_out;
  arq_out = fopen("utf82var_peq", "wb");
  if (arq_out == NULL)
  {
    printf("ERRO! O arquivo não foi aberto!\n");
    return 1;
  }
  int result = utf2varint(arq_in, arq_out);
  fclose (arq_in);
  fclose (arq_out);
  return 0;
}
