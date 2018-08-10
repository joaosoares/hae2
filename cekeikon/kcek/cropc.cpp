#include <cekeikon.h>

void cropc(int argc, char** argv)
{ if (argc!=4 && argc!=5 && argc!=7) {
    printf("CropC: Corta as bordas de imagens coloridas\n");
    printf("CropC ent*.ppm prefixo borda\n");
    printf("CropC ent*.ppm prefixo bordaLateral bordaSupInf\n");
    printf("CropC ent*.ppm prefixo bordaEsq bordaDir bordaSup bordaInf\n");
    erro("Erro: Numero de argumentos invalido");
  }
  int esq, dir, sup, inf;
  if (argc==4) {
    convArg(esq,argv[3]);
    dir=esq; sup=esq; inf=esq;
  } else if (argc==5) {
    convArg(esq,argv[3]);
    dir=esq; 
    convArg(sup,argv[4]);
    inf=sup;
  } else if (argc==7) {
    convArg(esq,argv[3]);
    convArg(dir,argv[4]);
    convArg(sup,argv[5]);
    convArg(inf,argv[6]);
  }
  vector<string> vs; vsWildCard(argv[1],vs);
  for (unsigned i=0; i<vs.size(); i++) {
    cout << "Lendo " << vs[i] << ". ";
    Mat_<COR> a; le(a,vs[i]);
    Mat_<COR> b(a.rows-sup-inf,a.cols-esq-dir);
    IMG_<COR> ae(a,sup,esq);
    for (int l=0; l<b.rows; l++)
      for (int c=0; c<b.cols; c++)
        b(l,c)=ae.atc(l,c);
    string st=addPrefix(argv[2],vs[i]);
    cout << "Gravando " << st << "." << endl;
    imp(b,st);
  }
}
