#include <cekeikon.h>

void vid2imc(int argc, char** argv)
{ if (argc!=4) {
    printf("VID2IMC: Grava frame #frame como imagem colorida\n");
    printf("VID2JPG video.ext imagem.ppm #frame\n");
    erro("Erro: Numero de argumentos invalido");
  }

  int frame;
  if (sscanf(argv[3],"%d",&frame)!=1) erro("Erro: Leitura frame");
  if (frame<0) erro("Erro: frame<0");

  VideoCapture v; v.open(argv[1]);
  if (!v.isOpened()) erro("Erro abertura video entrada");

  Mat_<COR> a;
  int i=0;
  while (true) {
    v >> a;
    if (i==frame) {
      imp(a,argv[2]); break;
    }
    i++;
  }
}
