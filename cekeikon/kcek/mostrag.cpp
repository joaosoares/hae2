#include <cekeikon.h>

void mostrag(int argc, char** argv)
{ if (argc<2) {
    printf("MostraG - Mostra multiplas imagens MatGRY com ajuste brilho/contraste\n");
    printf("MostraG imagem1.pgm imagem2.pgm ...\n");
    printf("  Nota: Pode-se usar wildcard. Ex: MostraG *.jpg *.png\n");
    printf("  M<>=AjustaTamanho +-0=Zoom ESDX=MoveLento flechas=MoveRapido\n");
    printf("  Home/End=Move ESC=FechaESai Q=SaiSemFechar\n");
    erro("Erro: Numero de argumentos invalido\n");
  }

  vector<string> st=vsWildCard(argc-1,&argv[1]);
  for (unsigned i=0; i<st.size(); i++) {
    Mat_<GRY> image; le(image,st[i]);
    printf("Tamanho imagem %s linhas=%d colunas=%d\n",st[i].c_str(),image.rows,image.cols);
    mostra(image,st[i]);
  }
}

