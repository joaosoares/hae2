//gradiente.cpp
#include <cekeikon.h>

void gradieng(int argc, char** argv) {
  if (argc!=3 && argc!=4) {
    printf("GradienG ent.pgm sai.img [gaussDev]\n");
    printf("  GradieG ent.pgm sai.img [gaussDev]\n");
    xerro1("Erro: Numero de argumentos invalido");
  }
  Mat_<GRY> a;
  le(a,argv[1]);  
  if (argc==4) {
    double gaussDev;
    convArg(gaussDev,argv[3]);
    GaussianBlur(a,a,Size(0,0),gaussDev,gaussDev);
  }
  Mat_<CPX> b=gradienteScharr(a,true);
  imp(b,argv[2]);
}
