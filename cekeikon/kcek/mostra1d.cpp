#include <cekeikon.h>

Mat_<FLT> normaliza2(Mat_<FLT> a, double inf, double sup)
{ FLT maior_pt,menor_br;
  maior_pt=percentil(a, inf );
  menor_br=percentil(a, sup);
  printf("maior_pt=%f menor_br=%f\n",maior_pt,menor_br);

  double delta=menor_br-maior_pt;
  if (delta<epsilon) return a;

  Mat_<FLT> d(a.rows,a.cols);
  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++)
      d(l,c)=(a(l,c)-maior_pt)/delta;
  return d;
}

void mostra1d(int argc, char** argv)
{ if (argc<2) {
    printf("Mostra1D - Mostra 1 MatDBL com ajustes\n");
    printf("Mostra1D imagem.img [r | n | p inf sup]\n");
    printf("  A=AjustaTamanho +-0=Zoom ESDX=MoveLento flechas=MoveRapido\n");
    printf("  Home/End=Move ESC=FechaESai Q=SaiSemFechar\n");
    printf("Modo r = raw => nao faz ajustes previos\n");
    printf("Modo n = normaliza => mapeia para [0,1]\n");
    printf("Modo p = percentil => descarta inf e sup percentil e mapeia para [0,1]\n");
    printf("  mostra1d imagem.img p 2 99 => abaixo de 2%% vira pt e acima de 99%% vira br\n");
    erro("Erro: Numero de argumentos invalido\n");
  }

  Mat_<DBL> image; le(image,argv[1]);
  Mat_<FLT> a; converte(image,a);

  if (argc>2) {
    char modo=tolower(argv[2][0]);
    if        (modo=='r') { // nao faz nada
    } else if (modo=='n') { //
      a=normaliza(a);
    } else if (modo=='p') {
      if (argc!=5) erro("Erro: p inf sup");
      double inf,sup;
      convArg(inf,argv[3]);
      convArg(sup,argv[4]);
      a=normaliza2(a,inf,sup);
    } else erro("Modo invalido ",string(1,modo));
  }
  mostra(a,argv[1]);
}

