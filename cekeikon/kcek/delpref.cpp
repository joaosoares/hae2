#include <cekeikon.h>

void delpref(int argc, char** argv)
{
  if (argc<3) {
    printf("DelPref: Apaga n letras iniciais dos nomes dos arquivos\n");
    printf("DelPref n arq1.ext arq2.ext ...\n");
    erro("Erro: numero de parametros");
  }

  int n; convArg(n, argv[1]);
  vector<string> vs;
  for (int i=2; i<argc; i++) vsWildCard(argv[i],vs);

  for (unsigned i=0; i<vs.size(); i++) {
    if (int(vs[i].length())<=n) erro("Erro: n muito grande");
    string novo=vs[i].substr(n);
    cout << "Rename " << vs[i] << " " << novo << endl;
    int r=rename(vs[i].c_str(),novo.c_str());
    if (r!=0) erro("Erro no rename");
  }
}

