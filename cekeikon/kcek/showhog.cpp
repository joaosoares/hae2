#include <cekeikon.h>

void showhog(int argc, char** argv)
{ if (argc<3) {
    printf("ShowHOG: Mostra HOG features de imagens (ex: 128x64)\n");
    printf("ShowHOG \"default | nBins=8 | cellSize=8 | zoom=4 | mult=1.0\" imagem1.jpg imagem2.jpg ...\n");
    printf("  Default nBins=8 cellSize=8\n");
    erro("Erro: Numero de argumentos invalido");
  }

  int nBins=8; 
  int cellSize=8; 
  int zoom=4; 
  double mult=1.0; 

  ISTR arq(argv[1]);
  string st;
  seekArg(arq,"default",st);
  seekArg(arq,"nbins",nBins);
  seekArg(arq,"cellsize",cellSize);
  seekArg(arq,"zoom",zoom);
  seekArg(arq,"mult",mult);
  if (seekFim(arq)==false) erro("Erro: Argumento invalido ",arq.st);

  Mat_<COR> a; 
  for (int i=2; i<argc; i++) {
    le(a,argv[i]); 
    HOG hog(a,nBins,cellSize); 
    hog.show(zoom,mult,argv[i]);
  }
}

