#include <cekeikon.h>

void copybk(int argc, char** argv) {
  if (argc!=7) {
    printf("CopyBk: Copia blocos aleatoriamente para gerar fantom para oclusao parcial\n");
    printf("CopyBk ent.pgm sai.pgm nl nc nb seed\n");
    printf("  nl nc: Tamanho dos blocos. Ex: 19 19\n");
    printf("  nb: Numero de blocos copiados. Ex: 20\n");
    erro("Erro: Numero de argumentos invalido");
  }
  Mat_<GRY> a; le(a,argv[1]);
  Mat_<GRY> b=a.clone();

  int nl; convArg(nl,argv[3]);
  int nc; convArg(nc,argv[4]);
  int nb; convArg(nb,argv[5]);
  int seed; convArg(seed,argv[6]);
  srand(seed);

  for (int i=0; i<nb; i++) {
    int lo=rand()%(a.rows-nl);
    int co=rand()%(a.cols-nc);
    int ld=rand()%(a.rows-nl);
    int cd=rand()%(a.cols-nc);
    for (int l=0; l<nl; l++) 
      for (int c=0; c<nc; c++)
        b(l+ld,c+cd)=a(l+lo,c+co);
  }
  imp(b,argv[2]);
}
