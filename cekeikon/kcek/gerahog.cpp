#include <cekeikon.h>

void gerahog(int argc, char** argv)
{ if (argc<5) {
    printf("GeraHOG: Extrai HOG de imagens (ex: 128x128) e grava como .IMG\n");
    printf("GeraHOG \"default | nBins=8 | cellSize=16\" hog.img -1|+1 imagens*.jpg\n");
    printf("  Se nao existe hog.img, cria novo\n");
    printf("  Caso contrario, acrescenta novas linhas em pedestre.img\n");
    printf("  -1: exemplo negativo. +1: exemplo positivo.\n");
    erro("Erro: Numero de argumentos invalido");
  }

  int nBins=8;
  int cellSize=16;
  ISTR arq(argv[1]);
  string st=leStr(arq);
  while (st!="eof") {
    if (st=="default") {
    } else if (st=="nbins") {
      leNum(arq,nBins); 
    } else if (st=="cellsize") {
      leNum(arq,cellSize); 
    } else {
      erro("Erro: Palavra desconhecida ",st);
    }
    st=leStr(arq);
  }
  Mat_<COR> a; le(a,argv[4]);
  int rows=a.rows; int cols=a.cols;
  int ns=nBins;
  int nl=rows/cellSize;
  int nc=cols/cellSize;
  int features=ns*nl*nc;

  int n=argc-4;
  Mat_<FLT> pedant; 
  if (existeArq(argv[2])) {
    le(pedant,argv[2]);
    if (pedant.cols!=features+1) erro("Erro: pedestre.img deve ter features+1 colunas. ",format("Features=%d",features));
  }
  Mat_<FLT> ped(pedant.rows+n,features+1,0.0);
  for (int l=0; l<pedant.rows; l++)
    for (int c=0; c<pedant.cols; c++)
      ped(l,c)=pedant(l,c);
  int inicio=pedant.rows;

  FLT rotulo; convArg(rotulo,argv[3]);

  for (int i=0; i<n; i++) {
    le(a,argv[i+4]); 
    printf("Processando %s\r",argv[i+4]);
    HOG hog(a,nBins,cellSize); 
    if (hog.blo.size[0]!=ns || hog.blo.size[1]!=nl || hog.blo.size[2]!=nc) 
      erro("Erro: Dimensoes diferentes",format("ns=%d nl=%d nc=%d",hog.blo.size[0],hog.blo.size[1],hog.blo.size[2]));
    for (int l=0; l<nl; l++)
      for (int c=0; c<nc; c++) {
        for (int s=0; s<ns; s++) 
          ped(i+inicio,l*nc*ns+c*ns+s)=hog.blo(s,l,c);
        ped(i+inicio,features)=rotulo;
      }
  }
  printf("\n");
  imp(ped,argv[2]);
}
