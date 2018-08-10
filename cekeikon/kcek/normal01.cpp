#include <cekeikon.h>

void normal01(int argc, char** argv)
{ if (argc!=2 && argc!=3 && argc!=4) {
    printf("Normal01: Faz sai conformar a normal(newMedia,newDesvo)\n");
    printf("Normal01 ent.pgm sai.pgm [newMedia] [newDesvio]\n");
    printf("  newMedia  default = 0.5\n");
    printf("  newDesvio default = 1.0/5.0\n");
    printf("  newDesvio negativo indica desvio -1/2*newDesvio\n");
    printf("    Ex: newDesvio=-2.5: -2.5sigma a 2.5sigma mapeado a [0,1]\n");
    erro("Erro: Numero de argumentos invalido");
  }

  Mat_<FLT> a; le(a,argv[1]);

  double newMedia=0.5; 
  if (argc>3) convArg(newMedia,argv[3]);

  double newDesvio=1.0/5.0; 
  if (argc>4) convArg(newDesvio,argv[4]);
  if (newDesvio<0.0) newDesvio=-1.0/(2*newDesvio);
  printf("newDesvio=%f\n",newDesvio);

  double media, desvio;
  mediaDesvio(a,media,desvio);
  printf("Ent: media=%f desvio=%f\n",media,desvio);

  normal01(a,newMedia,newDesvio);
  imp(a,argv[2]);

  mediaDesvio(a,media,desvio);
  printf("Sai: media=%f desvio=%f\n",media,desvio);
}
