#include <cekeikon.h>

Mat_<FLT> filtraKMeans(Mat_<FLT> m, int k)
{ Mat_<int> bestLabels(m.rows,1);
  Mat_<FLT> centers(k,3);
  TermCriteria criteria(TermCriteria::COUNT | TermCriteria::EPS, 50, 0.03);
  kmeans(m,k,bestLabels,criteria,1,KMEANS_PP_CENTERS,centers);
  //double compactness=kmeans(m,k,bestLabels,criteria,4,KMEANS_PP_CENTERS,centers);
  return centers;
}

void pixelmap(int argc, char** argv)
{ if (argc!=5 && argc!=7) {
    printf("PixelMap: Segmenta Mat_<COR> pela cor, usando flann e regressao\n");
    printf("PixelMap qx.ppm qp.pgm zero*.ppm one*.ppm [kzero kone]\n");
    printf("  Os pixels pretos de zero e one nao sao levados em conta\n");
    printf("  kzero e kone sao numero de nucleos de k-means\n");
    printf("  default: kzero=0 kone=0: nao calcula k-means e usa kd-tree em k-NN\n");
    printf("  kzero>0 ou kone>0: calcula k-means e usa forca-bruta em k-NN\n");
    erro("Erro: Numero de argumentos invalido");
  }

  int kzero=0;
  int kone=0; 
  if (argc==7) {
    convArg(kzero,argv[5]);
    convArg(kone,argv[6]);
  }

  Mat_<COR> amos;
  Mat_<FLT> temp(1,3);

  Mat_<FLT> zero;
  vector<string> arqZero; vsWildCard(argv[3],arqZero);
  for (unsigned i=0; i<arqZero.size(); i++) {
    le(amos,arqZero[i]);
    for (unsigned j=0; j<amos.total(); j++) {
      COR cor=amos(j); 
      temp(0)=G2F(cor[0]); temp(1)=G2F(cor[1]); temp(2)=G2F(cor[2]);
      zero.push_back(temp);
    }
  }

  Mat_<FLT> one;
  vector<string> arqOne; vsWildCard(argv[4],arqOne);
  for (unsigned i=0; i<arqOne.size(); i++) {
    le(amos,arqOne[i]);
    for (unsigned j=0; j<amos.total(); j++) {
      COR cor=amos(j); 
      temp(0)=G2F(cor[0]); temp(1)=G2F(cor[1]); temp(2)=G2F(cor[2]);
      one.push_back(temp);
    }
  }

  if (kzero==0 && kone==0) { 
    // Nao roda k-means. Roda k-NN usando kd-tree. 
    printf("Construindo kd-tree para k-NN...\n");
    flann::Index indZero(zero,flann::KDTreeIndexParams(4)); 
    flann::Index indOne(one,flann::KDTreeIndexParams(4)); 
  
    Mat_<COR> qx; le(qx,argv[1]);
    Mat_<GRY> qp(qx.size());
  
    printf("Buscando k-NN e fazendo regressao...\n");
    vector<FLT> query(3); 
    vector<int> indices(1);
    vector<FLT> dists(1);
    for (unsigned i=0; i<qx.total(); i++) {
      COR cor=qx(i);
      query[0]=G2F(cor[0]);
      query[1]=G2F(cor[1]);
      query[2]=G2F(cor[2]);
  
      indZero.knnSearch(query,indices,dists,1,flann::SearchParams(4));
      FLT d0=sqrt(dists[0]);
      indOne.knnSearch(query,indices,dists,1,flann::SearchParams(4));
      FLT d1=sqrt(dists[0]);
      FLT r=d0/(d0+d1);
      qp(i) = F2G(r);
    }
    imp(qp,argv[2]);
  } else {
    // Nao k-means. Roda k-NN usando forca bruta. 
    printf("Rodando k-means...\n");
    if (kzero>0) zero=filtraKMeans(zero,kzero);
    if (kone>0) one=filtraKMeans(one,kone);

    printf("Preparando para k-NN com forca bruta...\n");
    flann::Index indZero(zero,flann::LinearIndexParams()); 
    flann::Index indOne(one,flann::LinearIndexParams()); 
  
    Mat_<COR> qx; le(qx,argv[1]);
    Mat_<GRY> qp(qx.size());
  
    printf("Buscando k-NN pela forca bruta e fazendo regressao...\n");
    vector<FLT> query(3); 
    vector<int> indices(1);
    vector<FLT> dists(1);
    for (unsigned i=0; i<qx.total(); i++) {
      COR cor=qx(i);
      query[0]=G2F(cor[0]);
      query[1]=G2F(cor[1]);
      query[2]=G2F(cor[2]);
  
      indZero.knnSearch(query,indices,dists,1);
      FLT d0=sqrt(dists[0]);
      indOne.knnSearch(query,indices,dists,1);
      FLT d1=sqrt(dists[0]);
      FLT r=d0/(d0+d1);
      qp(i) = F2G(r);
    }
    imp(qp,argv[2]);
  }
}