#include <cekeikon.h>

void lkflow(int argc, char** argv) 
{ if (argc!=4) {
    printf("LKFlow: Calcula fluxo otico entre duas imagens\n");
    printf("LKFlow ent1.jpg ent2.jpg sai.jpg\n");
    erro("Erro: Numero de argumentos invalido");
  }
  
  Mat_<COR> a1; le(a1,argv[1]);
  Mat_<GRY> g1; converte(a1,g1);
  Mat_<COR> a2; le(a2,argv[2]);

  int maxcorner=100; 
  double quality=0.005; 
  double mindist=5; 
  vector<Point2f> pts1;
  goodFeaturesToTrack(g1, pts1, maxcorner, quality, mindist);
  printf("Detectou %u pontos\n",unsigned(pts1.size()));

  vector<Point2f> pts2;
  vector<bool>   status;
  vector<float>   err;
  calcOpticalFlowPyrLK(a1, a2, pts1, pts2, status, err);

  for (int i=0; i<int(pts2.size()); i++) {
    if (status[i]==true) {
      Point2f p1=pts1[i];
      Point2f p2=pts2[i];
      if (norm(p1-p2)>1) {
        int l1=arredonda(p1.y);
        int c1=arredonda(p1.x);
        int l2=arredonda(p2.y);
        int c2=arredonda(p2.x);
        flecha(a2,l1,c1,l2,c2,COR(0,0,255));
      }
    }
  }
  imp(a2,argv[3]);
}
