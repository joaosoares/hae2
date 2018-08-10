#include <cekeikon.h>

void img2vid(int argc, char** argv)
{ if (argc<5) {
    printf("Img2vid: Converte seq de img em vid\n");
    printf("Img2vid n fps sai.avi ent1.jpg ent2.jpg...\n");
    printf("n: Numero de vezes que repete seq de imagens no vid\n");
    printf("n: Negativo indica vai e volta\n");
    erro("Erro: Numero de argumentos invalido");
  }
  int n; convArg(n,argv[1]);
  int fps; convArg(fps,argv[2]);
  Mat_<COR> a; le(a,argv[4]);
  VideoWriter vo(argv[3],CV_FOURCC('X','V','I','D'),fps,a.size()); 
  for (int j=0; j<abs(n); j++) {
    for (int i=4; i<argc; i++) {
      le(a,argv[i]);
      vo << a;
    }
    if (n<0) {
      for (int i=argc-1; i>=4; i--) {
        le(a,argv[i]);
        vo << a;
      }
    }
  }
}
