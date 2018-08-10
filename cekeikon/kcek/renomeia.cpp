#include <cekeikon.h>

void renomeia(int argc, char** argv)
{ if (argc!=5) {
    printf("Renomeia especificacao.ext inicio nchar cadeia\n");
    printf("  Ex: Renomeia aa*.jpg 0 2 b = renomeia aa000.jpg para b000.jpg\n");
    erro("Erro: Numero de argumentos invalido");
  }

  vector<string> vs;
  vsWildCard(argv[1],vs);

  int inicio; convArg(inicio,argv[2]);
  int nchar;  convArg(nchar,argv[3]);
  string cadeia=argv[4];

  for (unsigned i=0; i<vs.size(); i++) {
    string newname=vs[i];
    newname.replace(inicio,nchar,cadeia);
    int result=rename(vs[i].c_str(),newname.c_str());
    if (result!=0) erro("Erro: Falhou rename: ",vs[i]+" ",newname);
  }
}