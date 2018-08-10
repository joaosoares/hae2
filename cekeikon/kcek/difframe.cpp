#include <cekeikon.h>

void difframe(int argc, char** argv)
{ if (argc!=3) {
    printf("DifFrame: Calcula diferenca de quadros consecutivos\n");
    printf("DifFrame ent.avi sai.avi\n");
    erro("Erro: Numero de argumentos invalido");
  }

  VideoCapture vi(argv[1]); 
  Size tam(vi.get(CV_CAP_PROP_FRAME_WIDTH),vi.get(CV_CAP_PROP_FRAME_HEIGHT));

  VideoWriter vo(argv[2],
                 CV_FOURCC('X','V','I','D'), // MPEG4
                 vi.get(CV_CAP_PROP_FPS),
                 tam); 
  // XVID, -1 (pergunta) ou 0 (nao-compactado)
  Mat_<COR> ant,atu,e;
  double inicio=vi.get(CV_CAP_PROP_POS_AVI_RATIO);
  vi >> atu;
  if (!atu.data) erro("Erro inesperado");
  while (true) {
    printf("%6.2f%%\r",100*(vi.get(CV_CAP_PROP_POS_AVI_RATIO)-inicio));
    atu.copyTo(ant);
    vi >> atu;
    if (!atu.data) break;
    //absdiff(ant,atu,e);
    e = (ant-atu)/2+127; 
    vo << e;
  }
  printf("\n");
} 
