#include <cekeikon.h>

void cam2vid(int argc, char** argv)
{ if (argc!=2 && argc!=3) {
    printf("Cam2vid: Captura webcam e grava video 240x320 com inf. segundos\n");
    printf("Cam2vid sai.avi [FOURCC]\n");
    printf("FOURCC: PIM1 MJPG MP42 DIV3 DIVX U263 I263\n");
    printf("        FLV1 HFYU DRAC XVID X264 MP1V\n");
    printf("        -1:pergunta 0:uncompressed_avi\n");
    printf("        default=XVID\n");
    erro("Erro: Numero de argumentos invalido");
  }

  VideoCapture vi;
  vi.open(0);
  if (!vi.isOpened()) erro("Erro abertura webcam");
  vi.set(CV_CAP_PROP_FRAME_WIDTH,320);
  vi.set(CV_CAP_PROP_FRAME_HEIGHT,240);

  int fourcc=CV_FOURCC('X','V','I','D');
  if (argc==3) {
    string st=maiuscula(argv[2]);
    if (st.length()==4) fourcc=CV_FOURCC(st[0],st[1],st[2],st[3]);
    else if (st=="0") fourcc=0;
    else if (st=="-1") fourcc=-1;
    else erro("Erro: FOURCC desconhecido");
  }

  VideoWriter vo(argv[1],fourcc,
               30,Size(320,240)); // XVID==MPEG4
  if (!vo.isOpened()) erro("Erro abertura ",argv[1]);

//   printf("FPS=%f\n",vi.get(CV_CAP_PROP_FPS));

  Mat_<COR> a;
  vi >> a; // O primeiro quadro e' preto

  int ch;
  namedWindow("janela");
  int inicio=centseg();
  int conta=0;
  do {
    vi >> a;
    flip(a,a,1);
    int t=centseg()-inicio;
    putTxt(a,0,0,format("%06d %3d.%02d",conta,t/100,t%100));
    imshow("janela",a);    
    vo << a;
    ch=waitKey(33);
    conta++;
  } while (ch!=27);
}

