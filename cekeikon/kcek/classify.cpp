#include <cekeikon.h>

float boopred(CvBoost& ind, HOG& hog)
{ int ns=hog.blo.size[0];
  int nl=hog.blo.size[1];
  int nc=hog.blo.size[2];

  Mat_<FLT> query(1,ns*nl*nc); 
  for (int s=0; s<ns; s++)
    for (int l=0; l<nl; l++)
      for (int c=0; c<nc; c++)
        query(l*nc*ns+c*ns+s)=hog.blo(s,l,c);
  CvMat pquery=query;

  return ind.predict(&pquery);
}

void classify(int argc, char** argv)
{ if (argc<3) {
    printf("Classify treino.xml imagens128x64*.jpg\n");
    erro("Erro: Numero de argumentos invalido");
  }

  CvBoost ind; ind.load(argv[1]);

  int ns=8;
  int nl=16;
  int nc=8;
  Mat_<COR> a; 
  for (int i=2; i<argc; i++) {
    le(a,argv[i]); 
    HOG hog(a,8,8); //   HOG(Mat_<COR> a, int _nBins=8, int _cellSize=8);
    if (hog.blo.size[0]!=ns || hog.blo.size[1]!=nl || hog.blo.size[2]!=nc) erro("Erro: Dimensoes diferentes");
    //hog.show();
    float resultado=boopred(ind,hog);
  
    if (resultado==1.0) printf("%s = pedestre\n",argv[i]);
    else if (resultado==-1) printf("%s = carro\n",argv[i]);
    else erro("Erro: Resultado inesperado\n");
  }
}

