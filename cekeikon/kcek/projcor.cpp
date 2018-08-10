#include <cekeikon.h>

COR brancoc(255,255,255);

void projcor(int argc, char** argv)
{ if (argc!=5 && argc!=6) {
    printf("ProjCor: Projeta as cores da Mat_<COR> nos planos rg, rb e gb\n");
    printf("ProjCor ent.tga rg.tga rb.tga gb.tga [n]\n");
    printf("  So mostra cores que aparecem > n vezes. Default n=0\n");
    printf("  Nota: A cor mostrada e' a cor mais inferior direita da imagem\n");
    erro("Erro: Numero de argumentos invalido");
  }
  int n=0;
  if (argc==6) {
    int e=sscanf(argv[5],"%d",&n);
    if (e!=1) erro("Erro leitura n");
  }
  Mat_<COR> a; le(a,argv[1]);

  Mat_<FLT> rgf(256,256,0.0);
  Mat_<FLT> rbf(256,256,0.0);
  Mat_<FLT> gbf(256,256,0.0);
  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++) {
      COR k=a(l,c);
      rgf(k[2],k[1])++;
      rbf(k[2],k[0])++;
      gbf(k[1],k[0])++;
    }

  double nf=n;
  Mat_<COR> rg(256,256,brancoc);
  Mat_<COR> rb(256,256,brancoc);
  Mat_<COR> gb(256,256,brancoc);
  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++) {
      COR k=a(l,c);
      if (rgf(k[2],k[1])>nf) rg(k[2],k[1])=k;
      if (rbf(k[2],k[0])>nf) rb(k[2],k[0])=k;
      if (gbf(k[1],k[0])>nf) gb(k[1],k[0])=k;
    }
  imp(rg,argv[2]);
  imp(rb,argv[3]);
  imp(gb,argv[4]);
}
