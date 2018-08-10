#include <cekeikon.h>

void shp2imb(int argc, char** argv)
{ if (argc!=3 && argc!=5 && argc!=6 && argc!=7) {
    printf("shp2ImB: Converte SHAPE em IMGBIN\n");
    printf("shp2ImB ent.mat sai.bmp [nl nc] [f/a] [c/s]\n");
    printf("  Ex. ent.mat: 4 2  1 0  0 1  -1 0  0 -1\n");
    printf("  Default: nl=480 nc=640\n");
    printf("  f=shape fechado (default)  a=shape aberto\n");
    printf("  c=com marca de vertice (default)  s=sem vertice\n");
    erro("Erro: Numero de argumentos invalido");
  }
  SHAPEF u; le(u,argv[1]); 
  assert(u.cols==2);

  int nl=480; int nc=640;
  if (argc>=5) {
    if (sscanf(argv[3],"%d",&nl)!=1) erro("Erro leitura nl");
    if (sscanf(argv[4],"%d",&nc)!=1) erro("Erro leitura nc");
  }

  bool fechado=true;
  if (argc>=6)
    if (tolower(argv[5][0])=='a') fechado=false;

  bool vertice=true;
  if (argc>=7)
    if (tolower(argv[6][0])=='s') vertice=false;

  Mat_<GRY> b(nl,nc,255);
  shape2img(u,b,0,fechado,vertice); // cor, fechado, vertice
  imp(b,argv[2]);
}
