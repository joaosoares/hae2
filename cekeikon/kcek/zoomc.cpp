#include <cekeikon.h>

void zoomc(int argc, char** argv)
{
  if (argc<5) {
    printf("ZoomC fatorl fatorc metodo ent1.ppm ent2.ppm ...\n");
    printf("  metodo: Nearest Linear Area Cubic Sinc\n");
    printf("  A saida sera zent1.ppm zent2.ppm ...\n");
    erro("Erro: numero de parametros");
  }

  double fatorl; convArg(fatorl, argv[1]);
  double fatorc; convArg(fatorc, argv[2]);

  char metodo=tolower(argv[3][0]);
  assert(metodo=='n' || metodo=='l' || metodo=='a' || metodo=='c' || metodo=='s');
  int interpolation;
  if (metodo=='n') interpolation=INTER_NEAREST;
  if (metodo=='l') interpolation=INTER_LINEAR;
  if (metodo=='a') interpolation=INTER_AREA;
  if (metodo=='c') interpolation=INTER_CUBIC;
  if (metodo=='s') interpolation=INTER_LANCZOS4;

  vector<string> vs;
  for (int i=4; i<argc; i++) vsWildCard(argv[i],vs);

  Mat_<COR> ent,sai;
  for (unsigned i=0; i<vs.size(); i++) {
    le(ent,vs[i]);
    cout << "Lendo " << vs[i] << endl;
    resize(ent,sai,Size(0,0),fatorc,fatorl,interpolation);
    string nomedir=diretorio(vs[i]);
    string nomearq=semDiret(vs[i]);
    if (nomedir!="") nomearq=nomedir+"\\z"+nomearq;
    else nomearq="z"+nomearq;
    imp(sai,nomearq);
    cout << "Imprimindo " << nomearq << endl;
  }
}


