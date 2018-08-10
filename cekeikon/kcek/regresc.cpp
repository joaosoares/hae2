#include <cekeikon.h>

void regresc(int argc, char** argv)
{ if (argc!=5) {
    printf("RegresC: Segmenta Mat_<COR> pela cor, usando flann e regressao\n");
    printf("RegresC qx.ppm qp.pgm zero*.ppm one*.ppm\n");
    printf("  Os pixels pretos de zero e one nao sao levados em conta\n");
    erro("Erro: Numero de argumentos invalido");
  }

  Mat_<COR> amos;
  Mat_<FLT> temp(1,3);

  Mat_<FLT> zero;
  vector<string> arqZero; vsWildCard(argv[3],arqZero);
  for (unsigned i=0; i<arqZero.size(); i++) {
    le(amos,arqZero[i]);
    for (unsigned j=0; j<amos.total(); j++) {
      COR cor=amos(j); 
      temp(0)=G2F(cor[0]);
      temp(1)=G2F(cor[1]);
      temp(2)=G2F(cor[2]);
      zero.push_back(temp);
    }
  }

  Mat_<FLT> one;
  vector<string> arqOne; vsWildCard(argv[4],arqOne);
  for (unsigned i=0; i<arqOne.size(); i++) {
    le(amos,arqOne[i]);
    for (unsigned j=0; j<amos.total(); j++) {
      COR cor=amos(j); 
      temp(0)=G2F(cor[0]);
      temp(1)=G2F(cor[1]);
      temp(2)=G2F(cor[2]);
      one.push_back(temp);
    }
  }

  printf("Treinando...\n");
  flann::Index indZero(zero,flann::KDTreeIndexParams(4)); 
  flann::Index indOne(one,flann::KDTreeIndexParams(4)); 

  Mat_<COR> qx; le(qx,argv[1]);
  Mat_<GRY> qp(qx.size());

  printf("Fazendo regressao...\n");
  vector<FLT> query(3); 
  vector<int> indices(1);
  vector<FLT> dists(1);
  for (unsigned i=0; i<qx.total(); i++) {
    COR cor=qx(i);
    query[0]=G2F(cor[0]);
    query[1]=G2F(cor[1]);
    query[2]=G2F(cor[2]);

    indZero.knnSearch(query,indices,dists,1,flann::SearchParams(8));
    FLT d0=sqrt(dists[0]);
    indOne.knnSearch(query,indices,dists,1,flann::SearchParams(8));
    FLT d1=sqrt(dists[0]);
    FLT r=d0/(d0+d1);
    qp(i) = F2G(r);
  }
  imp(qp,argv[2]);
}

