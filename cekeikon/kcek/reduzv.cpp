#include <cekeikon.h>

void reduzv(int argc, char** argv)
{ if (argc!=4) {
    printf("ReduzV: Pega somente quadros dividiveis por n\n");
    printf("ReduzV ent.avi sai.avi n\n");
    erro("Erro: Numero de argumentos invalido");
  }

  VideoCapture vi(argv[1]); 
  if (!vi.isOpened()) erro("Erro abertura video ",argv[1]);
  int nc=vi.get(CV_CAP_PROP_FRAME_WIDTH);
  int nl=vi.get(CV_CAP_PROP_FRAME_HEIGHT);
  int fps=vi.get(CV_CAP_PROP_FPS);

  VideoWriter vo(argv[2],
                 CV_FOURCC('X','V','I','D'),
                 fps,Size(nc,nl)); 
  if (!vo.isOpened()) erro("Erro abertura video ",argv[2]);

  int n;
  convArg(n,argv[3]);

  Mat_<COR> a; 
  for (int i=0; true; i++) {
    vi >> a;
    if (!a.data) break;
    if (i%n==0)
      vo << a;
  }
}

