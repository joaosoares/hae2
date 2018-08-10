#include <cekeikon.h>

void webcam(int argc, char** argv) 
{ if (argc!=2 && argc!=4) {
    printf("Webcam: Mostra captura de webcam na tela.\n");
    printf("Webcam camId [nl nc]\n");
    printf("  Default: nl=480 nc=640\n");
    printf("  Ex: Webcam 0\n");
    erro("Erro: Numero de argumentos invalido");
  }

  int camid; convArg(camid,argv[1]);

  int nl=480; 
  int nc=640; 
  if (argc==4) {
    convArg(nl,argv[2]);
    convArg(nc,argv[3]);
  }

  VideoCapture vi(camid); 
  if (!vi.isOpened()) erro("Erro abertura webcam");
  vi.set(CV_CAP_PROP_FRAME_HEIGHT,nl);
  vi.set(CV_CAP_PROP_FRAME_WIDTH,nc);
  nl=vi.get(CV_CAP_PROP_FRAME_HEIGHT);
  nc=vi.get(CV_CAP_PROP_FRAME_WIDTH);
  printf("nl=%-4d nc=%-4d\n",nl,nc);

  Mat_<COR> a(nl,nc);
  namedWindow("janela");
  while (true)  {
    vi >> a;  //  get  a  new  frame  from  camera
    flip(a,a,1);
    imshow("janela",a);
    if (waitKey(1)>=0)  break;
  }
}
