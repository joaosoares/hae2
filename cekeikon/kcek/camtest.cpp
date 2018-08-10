#include <cekeikon.h>

void camtest(int argc, char** argv)
{ if (argc!=6) {
    printf("CamTest: Testa webcam. Grava video com segundos.\n");
    printf("CamTest camid sai.avi nl nc fps\n");
    erro("Erro: Numero de argumentos invalido");
  }

  int camid; convArg(camid,argv[1]);
  int nl; convArg(nl,argv[3]);
  int nc; convArg(nc,argv[4]);
  int fps; convArg(fps,argv[5]);

  VideoCapture vi(camid); 
  vi.set(CV_CAP_PROP_FRAME_HEIGHT,nl);
  vi.set(CV_CAP_PROP_FRAME_WIDTH,nc);
  vi.set(CV_CAP_PROP_FPS,fps);

  cout << "nl_set= " << nl  << " nl_get= " << vi.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;
  cout << "nc_set= " << nc  << " nc_get= " << vi.get(CV_CAP_PROP_FRAME_WIDTH) << endl;
  cout << "fps_set=" << fps << " fps_get=" << vi.get(CV_CAP_PROP_FPS) << endl;

  nl=vi.get(CV_CAP_PROP_FRAME_HEIGHT);
  nc=vi.get(CV_CAP_PROP_FRAME_WIDTH);
  Mat_<COR> a;
  vi >> a;
  flip(a,a,1);

  VideoWriter vo(argv[2],-1,fps,Size(nc,nl));
  if (!vo.isOpened()) erro("Erro abertura ",argv[2]);

  printf("ESC para sair. F para gravar frame\n");
  namedWindow("janela",0);
  int nf=0; int tinic=0,t;
  while (true) {
    vi >> a;
    flip(a,a,1);
    if (nf==0) { tinic=centseg(); t=0; }
    else t=centseg()-tinic;
    putTxt(a,0,0,format("%5d %5d.%02d",nf++,t/100,t%100));
    vo << a;
    imshow("janela",a);    
    int ch=waitKey(1);
    if (ch=='f' || ch=='F') imp(a,semSufixo(argv[2])+".jpg");
    if (ch==27) break;
  }
}
