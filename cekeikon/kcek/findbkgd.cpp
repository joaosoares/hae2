#include <cekeikon.h>

namespace FindBkgd {

const double thErr=0.7; // diferenca entre quadros consecutivos<thErr => considera que background. Niveis de cinza vao ate 255.
const double weight=0.1; // Peso do quadro atual no background

/*
double diferenca(Mat_<COR> a, Mat_<COR> b, Mat_<COR>& dif)
{ if (a.size()!=b.size()) erro("Erro: Tamanhos diferentes");
  dif.create(a.size());
  double soma=0;
  for (int l=0; l<dif.rows; l++)
    for (int c=0; c<dif.cols; c++) {
      COR ca=a(l,c);
      COR cb=b(l,c);
      int red=abs(ca[2]-cb[2]);
      int gre=abs(ca[1]-cb[1]);
      int blu=abs(ca[0]-cb[0]);
      dif(l,c)=COR(blu,gre,red);
      soma = soma+red+gre+blu;
    }
  return soma / (3*a.total());
}
*/

void atualizaBkgd(Mat_<COR> atu, Mat_<COR>& bkg)
{ if (bkg.data==0) {
    atu.copyTo(bkg);
  } else {
    bkg = atu*weight + bkg*(1-weight);
  }
}

}

void findbkgd(int argc, char** argv)
{ using namespace FindBkgd;
  if (argc!=3) {
    printf("FindBkgd: Imprime video de background\n");
    printf("FindBkgd ent.avi sai.avi\n");
    erro("Erro: Numero de argumentos invalido");
  }

  VideoCapture vi(argv[1]); 
  Size tam(vi.get(CV_CAP_PROP_FRAME_WIDTH),vi.get(CV_CAP_PROP_FRAME_HEIGHT));

  VideoWriter vo(argv[2],
                 CV_FOURCC('X','V','I','D'), // MPEG4
                 vi.get(CV_CAP_PROP_FPS),
                 tam); 

  Mat_<COR> ant,atu,dif,bkg;
  //double inicio=vi.get(CV_CAP_PROP_POS_AVI_RATIO);
  vi >> atu; atu.copyTo(bkg);
  if (!atu.data) erro("Erro inesperado");
  while (true) {
    //printf("%6.2f%%\r",100*(vi.get(CV_CAP_PROP_POS_AVI_RATIO)-inicio));
    atu.copyTo(ant);
    vi >> atu;
    if (!atu.data) break;
    absdiff(ant,atu,dif);
    Scalar s=mean(dif);
    double e=(s[0]+s[1]+s[2])/3;
    if (e<thErr) atualizaBkgd(atu,bkg);
    //printf("e=%7.1f ",e);
    vo << bkg;
  }
  //printf("\n");
} 
