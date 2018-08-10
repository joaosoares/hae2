#include <cekeikon.h>

void mostraf(int argc, char** argv)
{ if (argc<2) {
    printf("MostraF - Mostra multiplas imagens MatFLT com ajuste brilho/contraste\n");
    printf("MostraF imagem1.img imagem2.txt ...\n");
    printf("  Nota: Pode-se usar wildcard. Ex: MostraF *.img *.txt\n");
    printf("  A=AjustaTamanho +-0=Zoom ESDX=MoveLento flechas=MoveRapido\n");
    printf("  Home/End=Move ESC=FechaESai Q=SaiSemFechar\n");
    erro("Erro: Numero de argumentos invalido\n");
  }

  vector<string> st=vsWildCard(argc-1,&argv[1]);
  for (unsigned i=0; i<st.size(); i++) {
    Mat_<FLT> image; le(image,st[i]);
    printf("Tamanho imagem %s linhas=%d colunas=%d\n",st[i].c_str(),image.rows,image.cols);
    //image=normaliza(image);
    mostra(image,st[i]);
  }
}

