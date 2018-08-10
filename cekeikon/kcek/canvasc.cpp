#include <cekeikon.h>

void canvasc(int argc, char** argv)
{ if (argc!=5 && argc!=6 && argc!=8) {
    printf("CanvasC: Insere bordas em imagens coloridas\n");
    printf("CanvasC ent*.ppm prefixo modo borda\n");
    printf("CanvasC ent*.ppm prefixo modo bordaLateral bordaSupInf\n");
    printf("CanvasC ent*.ppm prefixo modo bordaEsq bordaDir bordaSup bordaInf\n");
    printf("  Modo: N=borda_branca X=estendido R=repetido\n");
    erro("Erro: Numero de argumentos invalido");
  }
  int esq, dir, sup, inf;
  if (argc==5) {
    convArg(esq,argv[4]);
    dir=esq; sup=esq; inf=esq;
  } else if (argc==6) {
    convArg(esq,argv[4]);
    dir=esq; 
    convArg(sup,argv[5]);
    inf=sup;
  } else if (argc==8) {
    convArg(esq,argv[4]);
    convArg(dir,argv[5]);
    convArg(sup,argv[6]);
    convArg(inf,argv[7]);
  }
  char modo=toupper(argv[3][0]);
  if (modo!='N' && modo!='X' && modo!='R') 
    erro("Erro: Modo invalido"); 
  vector<string> vs; vsWildCard(argv[1],vs);
  for (unsigned i=0; i<vs.size(); i++) {
    cout << "Lendo " << vs[i] << ". ";
    Mat_<COR> a; le(a,vs[i]);
    Mat_<COR> b(a.rows+sup+inf,a.cols+esq+dir);
    IMG_<COR> ae(a,0,0); ae.backg=COR(255,255,255);
    IMG_<COR> be(b,sup,esq);
    for (int l=be.minl; l<=be.maxl; l++)
      for (int c=be.minc; c<=be.maxc; c++)
        if      (modo=='N') be.atc(l,c)=ae.atc(l,c);
        else if (modo=='X') be.atx(l,c)=ae.atx(l,c);
        else if (modo=='R') be.atr(l,c)=ae.atr(l,c);
    string st=addPrefix(argv[2],vs[i]);
    cout << "Gravando " << st << "." << endl;
    imp(b,st);
  }
}
