//threshg.cpp
#include <cekeikon.h>

void threshg(int argc, char** argv)
{ if (argc!=4) {
    printf("ThreshG ent.tga sai.bmp limiar\n");
    printf("  if (ent(l,c)<=limiar) sai(l,c)=0;\n");
    erro("Erro: Numero invalido de argumentos");
  }

  int limiar=0;
  if (sscanf(argv[3],"%d",&limiar)!=1) erro("Erro: limiar deve ser inteiro");
  if (limiar<0 || 255<limiar) erro("Erro: limiar deve pertencer a [0,255]");

  Mat_<GRY> ent; le(ent,argv[1]);
  Mat_<GRY> sai(ent.size());

  for (int l=0; l<ent.rows; l++)
    for (int c=0; c<ent.cols; c++) {
      if (ent(l,c)<=limiar) sai(l,c)=0;
      else sai(l,c)=255;
    }
  imp(sai,argv[2]);
}
