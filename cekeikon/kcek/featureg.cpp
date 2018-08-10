#include <cekeikon.h>

void featureg(int argc, char** argv) 
{ if (argc<3 || argc>6) {
    printf("FeatureG: Good features to track grayscale\n");
    printf("FeatureG ent.jpg sai.jpg [maxcorner] [quality] [mindist]\n");
    printf("  Default maxcorner=100 quality=0.005 mindist=5\n");
    erro("Erro: Numero de argumentos invalido");
  }
  int maxcorner=100; if (argc>3) convArg(maxcorner,argv[3]);
  double quality=0.005; if (argc>4) convArg(quality,argv[4]);
  double mindist=5; if (argc>5) convArg(mindist,argv[5]);
  
  Mat_<GRY> ent; le(ent,argv[1]);
  vector<Point2f> pts;
  goodFeaturesToTrack(ent, pts, maxcorner, quality, mindist);
  printf("Detectou %u pontos\n",unsigned(pts.size()));

  Mat_<COR> sai; converte(ent,sai);
  for (int i=0; i<int(pts.size()); i++) {
    sai(arredonda(pts[i].y),arredonda(pts[i].x))=COR(0,255,0);
  }
  imp(sai,argv[2]);
}

