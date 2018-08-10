#include <cekeikon.h>

void mostrac(int argc, char** argv)
{ if (argc<2) {
    printf("MostraC - Mostra multiplas imagens MatCOR\n");
    printf("MostraC imagem1.ppm imagem2.ppm ...\n");
    printf("  Nota: Pode-se usar wildcard. Ex: MostraC *.jpg *.png\n");
    printf("  M<>=AjustaTamanho +-0=Zoom ESDX=MoveLento flechas=MoveRapido\n");
    printf("  Home/End=Move ESC=FechaESai Q=SaiSemFechar\n");
    erro("Erro: Numero de argumentos invalido\n");
  }

  vector<string> st=vsWildCard(argc-1,&argv[1]);
  for (unsigned i=0; i<st.size(); i++) {
    Mat_<COR> image; le(image,st[i]);
    printf("Tamanho imagem %s linhas=%d colunas=%d\n",st[i].c_str(),image.rows,image.cols);
    mostra(image,st[i]);
  }
}

