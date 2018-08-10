#include <cekeikon.h>
#include <cekarq.h>
//int _CRT_glob = 0;   // Para impedir expansao de wildcar

void binariza(int argc, char** argv)
{ if (argc<7) {
    printf("Binariza: Binariza imagem colorida com pesos em RGB\n");
    printf("Binariza wr wg wb k ksize ent1.jpg ent2.jpg ...\n");
    printf("  wr*r+wg*g+wb*b>k => branco\n");
    printf("  ksize: tamanho da janela do filtro mediana (1,3,5,7...)\n");
    printf("    ksize=1: Nao aplica filtro\n");
    printf("  saida: zent1.png zent2.png ...\n");
    erro("Erro: Numero de argumentos invalido");
  }
  double wr; convArg(wr,argv[1]);
  double wg; convArg(wg,argv[2]);
  double wb; convArg(wb,argv[3]);
  double k;  convArg(k, argv[4]);
  int ksize; convArg(ksize, argv[5]);
  assert(ksize>=1 && ksize%2==1);
  vector<string> vs=vsWildCard(argc-6,&argv[6]);
  
  for (unsigned j=0; j<vs.size(); j++) {
    string nomeent=vs[j];
    string nomesai=diretorio(nomeent)+"\\z"+ semSufixo( semDiret(nomeent) ) + ".png";
    cout << nomeent << " => " << nomesai << endl;

    Mat_<COR> ent; le(ent,nomeent);
    Mat_<GRY> sai(ent.size(),0);
    for (unsigned i=0; i<ent.total(); i++) {
      COR cor=ent(i);
      if (wr*cor[2]+wg*cor[1]+wb*cor[0]>k) sai(i)=255;
    }
    if (ksize>=3) medianBlur(sai,sai,ksize);
    imp(sai,nomesai);
  }
}
