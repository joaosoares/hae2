#include <cekeikon.h>

void colafund(int argc, char** argv)
{ if (argc!=10) {
    printf("ColaFund: Cola duas imagens com fundo transparente\n");
    printf("ColaFund ent.ppm fig.ppm sai.ppm li ci f/a r g b\n");
    printf("  f=figura na frente, a=figura atras\n");
    printf("  RGB=valores do background\n");
    erro("Erro: Numero de argumentos invalido");
  }
  Mat_<COR> ent; le(ent,argv[1]);
  Mat_<COR> fig; le(fig,argv[2]);
  Mat_<COR> sai; ent.copyTo(sai);
  int li; convArg(li,argv[4]);
  int ci; convArg(ci,argv[5]);
  char modo=tolower(argv[6][0]);
  assert(modo=='f' || modo=='a');
  int red; convArg(red,argv[7]);
  int gre; convArg(gre,argv[8]);
  int blu; convArg(blu,argv[9]);
  COR backg=COR(blu,gre,red);

  IMG_<COR> ient(ent,0,0); ient.backg=backg;
  IMG_<COR> isai(sai,0,0); isai.backg=backg;
  for (int l=0; l<fig.rows; l++)
    for (int c=0; c<fig.cols; c++)
      if (modo=='f') {
        if (fig(l,c)!=backg) isai(l+li,c+ci)=fig(l,c);
      } else {
        if (fig(l,c)!=backg && ient(l+li,c+ci)==backg) isai(l+li,c+ci)=fig(l,c);
      }

  imp(sai,argv[3]);
}
