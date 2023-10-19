#include "converte.h"

int main(void)
{
	FILE* arqIn = fopen("arqEntrada.txt", "wb");
	FILE* arqOut = fopen("arqSaida.txt", "rb");
	int status = varint2utf(arqIn, arqOut);
	//utf2varint();
	fclose(arqIn);
	fclose(arqOut);
}