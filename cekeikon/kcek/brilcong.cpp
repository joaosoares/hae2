//brilcong.cpp
#include <cekeikon.h>

void brilcong(int argc, char** argv) {
  if (argc!=5) {
    printf("BrilConG: Ajusta brilho/contraste de Mat_<GRY>\n");
    printf("BrilConG ent.pgm sai.pgm brilho contraste\n");
    printf("  brilho e contraste no intervalo -1.0 a +1.0\n");
    erro("Erro: Numero de argumentos invalido");
  }

  Mat_<FLT> a; le(a,argv[1]);

  double brilho;
  if (sscanf(argv[3],"%lf",&brilho)!=1) xerro1("Erro: Leitura brilho");
  if (brilho<-1.0 || 1.0<brilho) xerro1("Erro: Brilho fora do intervalo");

  double contraste;
  if (sscanf(argv[4],"%lf",&contraste)!=1) xerro1("Erro: Leitura contraste");
  if (contraste<-1.0 || 1.0<contraste) xerro1("Erro: contraste fora do intervalo");

  for (unsigned i=0; i<a.total(); i++)
    if (contraste<0.0) // contraste negativo
      a(i)=(a(i)+brilho-0.5)*(1.0+contraste)+0.5;
    else if (contraste<1.0) // contraste positivo ou zero
      a(i)=(a(i)+brilho-0.5)*(1.0/(1.0-contraste))+0.5;
    else // contraste = 1
      a(i)=(a(i)+brilho-0.5)/epsilon+0.5;

  imp(a,argv[2]);
}

