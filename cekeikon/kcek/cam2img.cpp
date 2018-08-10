#include <cekeikon.h>

void cam2img(int argc, char** argv)
{ if (argc!=2 && argc!=3 && argc!=5) {
    printf("Cam2img: Tira serie de fotos da webcam\n");
    printf("Cam2img sai [camId] [nl nc]\n");
    printf("  Gera sai00.jpg sai01.jpg etc\n");
    printf("  Aperte ESPACO para tirar foto\n");
    printf("  Aperte ESC para sair do programa\n");
    erro("Erro: Numero de argumentos invalido");
  }

  int camid=0; 
  if (argc>=3) 
    convArg(camid,argv[2]);

  int nl=480; 
  int nc=640; 
  if (argc==5) {
    convArg(nl,argv[3]);
    convArg(nc,argv[4]);
  }

  VideoCapture vi(camid); 
  if (!vi.isOpened()) erro("Erro abertura webcam");
  vi.set(CV_CAP_PROP_FRAME_HEIGHT,nl);
  vi.set(CV_CAP_PROP_FRAME_WIDTH,nc);
  nl=vi.get(CV_CAP_PROP_FRAME_HEIGHT);
  nc=vi.get(CV_CAP_PROP_FRAME_WIDTH);
  printf("nl=%-4d nc=%-4d\n",nl,nc);

  Mat_<COR> a;
  vi >> a; // O primeiro quadro e' preto

  char ch;
  namedWindow("janela");
  //int conta=0;
  do {
    vi >> a;
    //flip(a,a,1);
    imshow("janela",a);    
    ch=waitKey(1);
    if (ch==' ') {
      // Ex: v000.jpg, v001.jpg, v002.jpg => maiorArq("v???.jpg",3) = 2
      int conta=maiorArq(string(argv[1])+"??.jpg",2);
      string st=format("%s%02d.jpg",argv[1],conta+1);
      //conta++;
      imp(a,st);
      printf("\a");
    }
  } while (ch!=27);
}

