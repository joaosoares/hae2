#include <cekeikon.h>

void pixmappo(int argc, char** argv)
{ if (argc!=5) {
    printf("PixMapPo: Segmenta Mat_<COR> pela cor, usando so amostras positivas\n");
    printf("PixMapPo 'qx*.ppm' prefixo distmax 'pos*.ppm'\n");
    printf("  Exemplo_neg=preto, exemplo_pos=branco\n; utiliza FlaNN\n");
    printf("  distmax e' a maior distancia euclidiana no espaco RGB\n");
    printf("    de uma amostra pos para que seja considerada positiva\n");
    printf("  qx*.ppm sao imagens para processar\n");
    printf("  pos*.ppm sao amostras de cores positivas\n");
    printf("  Extensao das imagens de saida sao .png\n");
    printf("Ex: pixmappo 'qx*.ppm' p 20 'pos*.ppm'\n");
    xerro1("Erro: Numero de argumentos invalido");
  }

  int distmaxg; convArg(distmaxg,argv[3]);
  float distmax; distmax=G2F(distmaxg);

  Mat_<FLT> pos;
  vector<string> vs; vsWildCard(argv[4],vs);
  for (unsigned i=0; i<vs.size(); i++) {
    Mat_<COR> amos;
    le(amos,vs[i]);
    for (unsigned j=0; j<amos.total(); j++) {
      COR cor=amos(j); 
      Mat_<FLT> temp(1,3);
      temp(0)=G2F(cor[0]); temp(1)=G2F(cor[1]); temp(2)=G2F(cor[2]);
      pos.push_back(temp);
    }
  }

  // Roda 1-NN usando kd-tree. 
  printf("Construindo kd-tree para 1-NN...\n");
  flann::Index indPos(pos,flann::KDTreeIndexParams(1)); 
  
  vs.clear(); vsWildCard(argv[1],vs);
  for (unsigned i=0; i<vs.size(); i++) {
    Mat_<COR> qx; le(qx,vs[i]);
    Mat_<GRY> qp(qx.size(),GRY(0));
    cout << "Processando " << vs[i] << endl;

    for (unsigned i=0; i<qx.total(); i++) {
      COR cor=qx(i);
      vector<FLT> query(3); query[0]=G2F(cor[0]); query[1]=G2F(cor[1]); query[2]=G2F(cor[2]);
      vector<int> indices(1); vector<FLT> dists(1);
      indPos.knnSearch(query,indices,dists,1,flann::SearchParams(4));
      float dist=sqrt(dists[0]);
      if (dist<distmax) qp(i)=255;
    }
    string st = diretorio(vs[i])+"/"+argv[2]+semDiret(semSufixo(vs[i]))+".png";
    cout << "  Imprimindo " << st << endl;
    imp(qp,st);
  }
}
