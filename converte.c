#include "converte.h"
#include <stdio.h>
#include <stdlib.h>

int utf2varint(FILE *arq_entrada, FILE *arq_saida) {
  unsigned char carac[4];
  unsigned char temp;
  while (fread((carac), 1, 1, arq_entrada)) {
    unsigned char ident = (carac[0] >> 3);
    if (ident == 30) {
      fread((carac + 1), 1, 3, arq_entrada);
      temp = carac[2] << 6;
      carac[3] = carac[3] | temp;
      carac[3] = carac[3] & 0x7F;

      carac[2] = carac[2] >> 1;
      temp = carac[1] << 5;
      carac[2] = carac[2] & 0x1F;
      carac[2] = carac[2] | temp;
      carac[2] = carac[2] | 0x80;

      carac[1] = carac[1] >> 2;
      temp = carac[0] << 4;
      carac[1] = carac[1] & 0x0F;
      carac[1] = carac[1] | temp;
      carac[1] = carac[1] | 0x80;
      
      fwrite(carac + 1, 1, 3, arq_saida);
    } else if (ident >= 28) {
      fread((carac + 1), 1, 2, arq_entrada);
      temp = carac[1] << 6;
      carac[2] = carac[2] | temp;
      carac[2] = carac[2] & 0x7F;

      carac[1] = carac[1] >> 1;
      temp = carac[0] << 5;
      carac[1] = carac[1] & 0x1F;
      carac[1] = carac[1] | temp;
      carac[1] = carac[1] | 0x80;

      carac[0] = carac[0] >> 2;
      carac[0] = carac[0] & 0x07;
      carac[0] = carac[0] | 0x80;
      
      fwrite(carac, 1, 3, arq_saida);
    } else if (ident >= 24) {
      fread((carac + 1), 1, 1, arq_entrada);
      temp = carac[0] << 6;

      carac[1] = carac[1] | temp;
      carac[1] = carac[1] & 0x7F;

      carac[0] = carac[0] >> 1;
      carac[0] = carac[0] & 0x0F;
      carac[0] = carac[0] | 0x80;

      fwrite(carac, 1, 2, arq_saida);

    } else {
      fwrite(carac, 1, 1, arq_saida);
    }
  }
  return 0;
}

int varint2utf(FILE *arq_entrada, FILE *arq_saida) {
  unsigned char carac[3];
  unsigned char caracUtf[4];

  while (fread(carac, 1, 1, arq_entrada) > 0) {
    if ((carac[0] >> 7) == 0)
      fwrite(carac, 1, 1, arq_saida);
    else {
      fread(carac + 1, 1, 1, arq_entrada);
      if ((carac[1] >> 7) == 0) {

        caracUtf[1] = (carac[1] & 0x3F) | 0x80;
        
        caracUtf[0] = (carac[0] << 1) | (carac[1] >> 6);
        caracUtf[0] = caracUtf[0] | 0xC0;
        
        fwrite(caracUtf, 1, 2, arq_saida);
      } else {
        fread(carac + 2, 1, 1, arq_entrada);
        if ((carac[0] & 0x7F) < 0x04) {
          caracUtf[2] = (carac[2] & 0x3F) | 0x80;

          caracUtf[1] = (carac[1] << 1) | (carac[2] >> 6);
          caracUtf[1] = (caracUtf[1] & 0x3F) | 0x80;

          caracUtf[0] = (carac[0] << 1) |((carac[1] >> 5) & 0x03);
          caracUtf[0] = caracUtf[0] | 0xE0;
          
  
          fwrite(caracUtf, 1, 3, arq_saida);

        } else {
          caracUtf[3] = (carac[2] & 0x3F) | 0x80;

          caracUtf[2] = (carac[1] << 1) | (carac[2] >> 6);
          caracUtf[2] = (caracUtf[2] & 0x3F)| 0x80;

          caracUtf[1] = (carac[0] << 2) | (carac[1] >> 5);
          caracUtf[1] = (caracUtf[1] & 0x3F) | 0x80;

          caracUtf[0] = (carac[0] & 0x7F) >> 4;
          caracUtf[0] = caracUtf[0] | 0xF0;
          fwrite(caracUtf, 1, 4, arq_saida);
        }
      }
    }
  }

  return 0; // Concluído com sucesso
}