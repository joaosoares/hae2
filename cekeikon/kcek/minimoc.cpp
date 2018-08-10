#include <cekeikon.h>

void minimoc(int argc, char **argv)
{ if (argc<3) {
    printf("Calcula minimo elementwise de n Mat_<COR>\n");
    printf("MinimoC sai.ppm arq1.ppm arq2.ppm ...\n");
    erro("Erro: Numero de argumentos invalido");
  }

  vector<string> args=vsWildCard(argc,argv);
  cout << args << endl;

  Mat_<COR> ent; le(ent,args[2]);
  Mat_<COR> sai=ent.clone();

  for (unsigned i=3; i<args.size(); i++) {
    le(ent,args[i]);
    sai = min(sai,ent);
  }
  imp(sai,args[1]);
}


