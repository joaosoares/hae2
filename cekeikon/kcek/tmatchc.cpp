#include <cekeikon.h>

void tmatchc(int argc, char** argv)
{ if (argc!=5) {
    printf("TMatchC: Faz template matching\n");
    printf("TMatchC a.ppm q.ppm p.img metodo\n");
    printf("  metodo=s/sn/x/xn/c/cn\n");
    printf("  s=SQDIFF sn=SQDIFF_NORMED (diferenca quadratica)\n");
    printf("  x=CCORR  xn=CCORR_NORMED  (correlacao cruzada)\n");
    printf("  c=CCOEFF cn=CCOEFF_NORMED (coeficiente subtrai_media)\n");
    printf("  cn e' NCC\n");
    erro("Erro: Numero de argumentos invalido");
  }
  Mat_<GRY> a; le(a,argv[1]);
  Mat_<GRY> q; le(q,argv[2]);
  string metodo=argv[4]; metodo=minuscula(metodo);

  Mat_<FLT> f;
  if        (metodo=="s") {
    matchTemplate( a, q, f, CV_TM_SQDIFF);
  } else if (metodo=="sn") {
    matchTemplate( a, q, f, CV_TM_SQDIFF_NORMED);
  } else if (metodo=="x") {
    matchTemplate( a, q, f, CV_TM_CCORR);
  } else if (metodo=="xn") {
    matchTemplate( a, q, f, CV_TM_CCORR_NORMED);
  } else if (metodo=="c") {
    matchTemplate( a, q, f, CV_TM_CCOEFF);
  } else if (metodo=="cn") {
    matchTemplate( a, q, f, CV_TM_CCOEFF_NORMED);
  } else {
    erro("Erro: Metodo desconhecido");
  }
  imp(f,argv[3]);
}
