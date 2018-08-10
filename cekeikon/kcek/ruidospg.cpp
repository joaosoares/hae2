#include <cekeikon.h>

void ruidospg(int argc, char** argv) {
  if (argc!=5) {
    printf("RuidoSPG: Coloca ruido aleatorio\n");
    printf("RuidoSPG ENT.PGM SAI.PGM CadaQto SRAND\n");
    erro("Erro: Numero de argumentos invalido");
  }
  Mat_<GRY> a; le(a,argv[1]);
  int cadaQto; convArg(cadaQto,argv[3]);
  int semente; convArg(semente,argv[4]);

  srand(semente);
  for (int l=0; l<a.rows; l++) {
    for (int c=0; c<a.cols; c++) {
      if (rand()%cadaQto==0) {
        a(l,c)=rand()%256;        
      }
    }
  }
  imp(a,argv[2]);
}

