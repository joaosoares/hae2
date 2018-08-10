#include <cekeikon.h>

int media(vector<GRY> r)
{ int soma=0;
  for (unsigned i=0; i<r.size(); i++)
    soma += r[i];
  return arredonda(soma,r.size());
}

void segmenc(int argc, char** argv)
{ if (!(5<=argc && argc<=9)) {
    printf("SegmenC: Segmenta Mat_<COR> pela cor, usando flann\n");
    printf("SegmenC ax.ppm ay.pgm qx.ppm qp.pgm [ntrees] [checks] [knn] [m|a]\n");
    printf("  ntrees=numero de arvores. Def=4\n");
    printf("  checks=numero de buscas recursivas. Def=4\n");
    printf("  knn=numero de vizinhos mais proximos. Def=3\n");
    printf("  decisao=criterio de desempate entre vizinhos. Median|Average. Def=m.\n");
    erro("Erro: Numero de argumentos invalido");
  }

  printf("Lendo arquivos...\n");
  Mat_<COR> ax; le(ax,argv[1]);
  Mat_<GRY> ay; le(ay,argv[2]);
  Mat_<COR> qx; le(qx,argv[3]);
  Mat_<GRY> qp(qx.rows,qx.cols); 

  int ntrees=4;
  if (6<=argc) convArg(ntrees,argv[5]);
 
  int checks=16;
  if (7<=argc) convArg(checks,argv[6]);
  
  int knn=3;
  if (8<=argc) convArg(knn,argv[7]);
      
  char decisao='m';
  if (9<=argc) decisao=tolower(argv[8][0]);
  if (!(decisao=='m' || decisao=='a')) 
    erro("Erro: Decisao invalido"); 

  printf("Criando arvores...\n");
  Mat_<FLT> features(ax.rows*ax.cols,3);
  Mat_<FLT> saidas(ax.rows*ax.cols,1);
  int i=0;
  for (int l=0; l<ax.rows; l++)
    for (int c=0; c<ax.cols; c++) {
      features(i,0)=ax(l,c)[0];
      features(i,1)=ax(l,c)[1];
      features(i,2)=ax(l,c)[2];
      saidas(i,0)=ay(l,c);
      i=i+1;
    }
  flann::Index ind(features,flann::KDTreeIndexParams(ntrees)); // usa 4 arvores

  printf("Fazendo busca...\n");
  vector<FLT> query(3); 
  vector<int> indices(knn);
  vector<FLT> dists(knn);
  vector<GRY> r(knn);
  for (int l=0; l<qp.rows; l++) {
    int p=arredonda(1000*l,qp.rows);
    printf("Completou %3d.%d%%\r",p/10,p%10);
    for (int c=0; c<qp.cols; c++) {
      query[0]=qx(l,c)[0];
      query[1]=qx(l,c)[1];
      query[2]=qx(l,c)[2];
      ind.knnSearch(query,indices,dists,knn,flann::SearchParams(checks));
      for (int i=0; i<knn; i++)
        r[i]=GRY(saidas(indices[i],0));
      if (decisao=='m') {
        nth_element(r.begin(), r.begin()+r.size()/2, r.end());
        qp(l,c) = r[r.size()/2];
      } else {
        qp(l,c) = media(r);
      }
    }
  }
  printf("\n");
  imp(qp,argv[4]);
}
