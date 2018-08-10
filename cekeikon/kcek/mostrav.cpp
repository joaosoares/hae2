#include <cekeikon.h>

void mostrav(int argc, char** argv)
{ if (argc<2) {
    printf("MostraV: mostra multiplos videos\n");
    printf("MostraV vid1.avi vid2.avi ...\n");
    printf("  Aperte ESC para sair.\n");
    erro("Erro: Numero de argumentos invalido");
  }

  for (int i=1; i<argc; i++) {
    VideoCapture vi(argv[i]);
    if (!vi.isOpened()) erro("Erro abertura");
    double fps=vi.get(CV_CAP_PROP_FPS);
    int espera=cvRound(1000.0/fps);
    
    Mat_<COR> a,b;
    namedWindow(argv[i]);
    if (!vi.read(a)) break;
    reta(a,0,0,a.rows-1,a.cols-1,COR(64,64,255));
    imshow(argv[i],a);
    printf("\07");
    if (waitKey(3000)==27) return;

    while (vi.read(a)) {
      imshow(argv[i],a);
      a.copyTo(b);
      if (waitKey(espera)==27) return;
    }

    reta(b,0,0,b.rows-1,b.cols-1,COR(64,64,255));
    imshow(argv[i],b);
    if (waitKey(3000)==27) return;
    destroyWindow(argv[i]);
  }
}
