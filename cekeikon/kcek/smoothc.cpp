#include <cekeikon.h>

void smoothc(int argc, char** argv)
{ if (argc<3 || 5<argc) {
    printf("Smoothc ent.ppm sai.ppm [tipo] [njanela]\n");
    printf("  tipo=m(mediana-default), g(gaussiana)\n");
    printf("  njanela default=3. Deve ser impar e maior que um\n");
    erro("Erro: Numero de argumentos invalido");
  }

  Mat_<COR> ent; le(ent,argv[1]);
  Mat_<COR> sai;

  char tipo='m'; 
  if (argc>3) tipo=tolower(argv[3][0]);
  if (tipo!='a' && tipo!='m' && tipo!='g') erro("Erro: tipo de filtro invalido");

  int njanela=3;
  if (argc>4) 
    if (sscanf(argv[4],"%d",&njanela)!=1) erro("Erro: Leitura njanela");
  if (njanela%2==0 || njanela<=1) erro("Erro: njanela deve ser impar e maior que 1");

  if      (tipo=='m') medianBlur( ent, sai, njanela );
  else if (tipo=='g') GaussianBlur( ent, sai, Size(njanela,njanela), 0 );
  else erro("Erro: Tipo de operacao desconhecido");

  imp(sai,argv[2]);
}
