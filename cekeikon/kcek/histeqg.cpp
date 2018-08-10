//histeqg.cpp
#include <cekeikon.h>
void histeqg(int argc, char** argv) {
  if (argc!=3) {
    printf("HistEqG ent.pgm sai.pgm\n");
    erro("Erro: Numero de argumentos invalido");
  }
  Mat_<GRY> img; le(img,argv[1]);
  Mat_<GRY> histeq;
  equalizeHist(img, histeq); 
  imp(histeq,argv[2]);
}
