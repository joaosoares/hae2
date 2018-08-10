#include <cekeikon.h>

namespace VidLkOut {

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

void vidlkout(int argc, char** argv)
{ using namespace VidLkOut;
  if (argc!=3) {
    printf("VidLkOut: Fluxo otico LK entre quadros consecutivos sem outliers\n");
    printf("VidLkOut ent.avi sai.avi\n");
    erro("Erro: Numero de argumentos invalido");
  }
  int maxcorner=100; 
  double quality=0.005; 
  double mindist=5; 

  VideoCapture vi(argv[1]); 
  Size tam(vi.get(CV_CAP_PROP_FRAME_WIDTH),vi.get(CV_CAP_PROP_FRAME_HEIGHT));

  VideoWriter vo(argv[2],
                 CV_FOURCC('X','V','I','D'), // MPEG4
                 vi.get(CV_CAP_PROP_FPS),
                 tam); 
  // XVID, -1 (pergunta) ou 0 (nao-compactado)

  Mat_<COR> a1,a2; //a2=atual
  double inicio=vi.get(CV_CAP_PROP_POS_AVI_RATIO);
  vi >> a2; if (!a2.data) erro("Erro inesperado");
  while (true) {
    printf("%6.2f%%\r",100*(vi.get(CV_CAP_PROP_POS_AVI_RATIO)-inicio));
    a2.copyTo(a1);
    vi >> a2; if (!a2.data) break;
    Mat_<COR> temp; a2.copyTo(temp);

    Mat_<GRY> g1; converte(a1,g1);
    vector<Point2f> pts1;
    goodFeaturesToTrack(g1, pts1, maxcorner, quality, mindist);

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
        flecha(temp,l1,c1,l2,c2,COR(0,0,255));
      }
    }

    vo << temp;
  }
  printf("\n");
} 
