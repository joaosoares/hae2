#include <cekeikon.h>

void mconvert(int argc, char** argv)
{ if (argc<4) {
    printf("MConvert: Converte formatos de multiplas imagens\n");
    printf("MConvert G/C saiext ent*.ext\n");
    printf("  G - imagem grayscale, formatos TGA, PGM, JPGnn, PNG, JP2, TIF, BMP, etc\n");
    printf("  C - imagem colorida, formatos TGA, PPM, JPGnn, PNG, JP2, TIF, BMP, etc\n");
    printf("  saiext: extensao de saida. JPGnn=qualidade (100=melhor qualidade).\n");
    printf("  Ex: MConvert G JPG90 *.tga\n");
    erro("Erro: numero incorreto de parametros");
  }

  char ch=toupper(argv[1][0]);
  string saiext=string(argv[2]);
  vector<string> vs=vsWildCard(argc-3,&argv[3]);
  if (ch=='G') {
    for (unsigned i=0; i<vs.size(); i++) {
      string ent=vs[i];
      Mat_<GRY> a; le(a,ent);
      imp(a,semSufixo(ent)+"."+saiext);
    }
  } else if (ch=='C') {
    for (unsigned i=0; i<vs.size(); i++) {
      string ent=vs[i];
      Mat_<COR> a; le(a,ent);
      imp(a,semSufixo(ent)+"."+saiext);
    }
  } else erro("Erro main - G (gray) ou C (cor)");
}
