#include <cekeikon.h>

namespace LkOut {

bool outlier(float dx, float dy, double mx, double my)
{ if (abs(dx-mx)>abs(0.5*mx)+1) return true; 
  if (abs(dy-my)>abs(0.5*my)+1) return true;
  return false;
}

void eliminaOutliers(vector<Point2f>& pts1, vector<Point2f>& pts2, vector<bool>& status)
{ if (pts1.size()!=pts2.size() || pts1.size()!=status.size()) 
    erro("Erro eliminaOutliers");

  vector<float> vx,vy; 
  for (int i=0; i<int(pts1.size()); i++) {
    if (status[i]==true) {
      if (norm(pts2[i]-pts1[i])<3) status[i]=false;
      else {
        vx.push_back(pts2[i].x-pts1[i].x);
        vy.push_back(pts2[i].y-pts1[i].y);
      }
    }
  }
  //printf("vx.size=%d\n",vx.size());

  float mx=mediana(vx);
  float my=mediana(vy);
  //printf("mx=%f my=%f\n",mx,my);

  for (int i=0; i<int(pts1.size()); i++) {
    float dx=pts2[i].x-pts1[i].x;
    float dy=pts2[i].y-pts1[i].y;
    if (status[i]==true && outlier(dx,dy,mx,my)) {
       status[i]=false;
    }
  }
}  

}

void lkout(int argc, char** argv) 
{ using namespace LkOut;
  if (argc!=4) {
    printf("LKOut: Calcula fluxo otico sem outliers entre duas imagens\n");
    printf("LKOut ent1.jpg ent2.jpg sai.jpg\n");
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
  //printf("Detectou %d pontos\n",pts1.size());

  vector<Point2f> pts2;
  vector<bool>   status;
  vector<float>   err;
  calcOpticalFlowPyrLK(a1, a2, pts1, pts2, status, err);
  eliminaOutliers(pts1,pts2,status);

  for (int i=0; i<int(pts2.size()); i++) {
    if (status[i]==true) {
      Point2f p1=pts1[i];
      Point2f p2=pts2[i];
      int l1=arredonda(p1.y);
      int c1=arredonda(p1.x);
      int l2=arredonda(p2.y);
      int c2=arredonda(p2.x);
      flecha(a2,l1,c1,l2,c2,COR(0,0,255));
    }
  }
  imp(a2,argv[3]);
}
