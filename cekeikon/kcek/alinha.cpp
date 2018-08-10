#include <cekeikon.h>

void alinha(int argc, char** argv)
{ if (argc!=4 && argc!=5) { 
    printf("Alinha: Translada A para ficar alinhada com REF\n");
    printf("Alinha REF.ppm A.ppm SAI.ppm [borda]\n");
    printf("  borda=maximo deslocamento. default=1/16 max(nl,nc)\n");
    erro("Erro: Numero de argumentos invalido");
  }

  Mat_<COR> ref; le(ref,argv[1]);
  Mat_<COR> a;   le(a,argv[2]);
  if (ref.size()!=a.size()) erro("Erro: Tamanhos de REF e A diferentes");

  int borda=max(a.rows,a.cols)/16;
  if (argc==5) convArg(borda,argv[4]);
  if (borda<1) erro("Erro: borda<1");

  Point desloca; double corr;
  calcAlinha(ref,a,borda,desloca,corr);
  printf("deslocax=%d deslocay=%d correlacao=%f\n",desloca.x,desloca.y,corr);

  Mat_<COR> sai=alinha(a,desloca);
  imp(sai,argv[3]);
}


  