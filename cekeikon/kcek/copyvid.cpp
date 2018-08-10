#include <cekeikon.h>

void copyvid(int argc, char** argv)
{ if (argc!=3) {
    printf("CopyVid: Copia video.\n");
    printf("  Permite converter tipos de video para avi-xvid\n");
    printf("CopyVid ent.avi sai.avi\n");
    erro("Erro: Numero de argumentos invalido");
  }

  VideoCapture vi(argv[1]); 
  Size tam(vi.get(CV_CAP_PROP_FRAME_WIDTH),vi.get(CV_CAP_PROP_FRAME_HEIGHT));

  VideoWriter vo(argv[2],
                 CV_FOURCC('X','V','I','D'), // MPEG4
                 vi.get(CV_CAP_PROP_FPS),
                 tam); 
  // XVID, -1 (pergunta) ou 0 (nao-compactado)
  Mat_<COR> atu;
  double inicio=vi.get(CV_CAP_PROP_POS_AVI_RATIO);
  while (true) {
    printf("%6.2f%%\r",100*(vi.get(CV_CAP_PROP_POS_AVI_RATIO)-inicio));
    vi >> atu;
    if (!atu.data) break;
    vo << atu;
  }
  printf("\n");
} 
