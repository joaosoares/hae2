#include <cekeikon.h>

void sobrepoe(int argc, char** argv)
{ if (argc<4) {
    printf("Sobrepoe: Sobrepoe varias imagens como transparentes\n");
    printf("Sobrepoe sai.ppm ent1.ppm ent2.ppm ...\n");
    erro("Erro: Numero de argumentos invalido");
  }

  Mat_<COR> sai,ent; Mat_<Vec3i> soma;
  le(ent,argv[2]); ent.copyTo(soma);
  for (int i=3; i<argc; i++) {
    le(ent,argv[i]); 
    soma = soma + ent;
  }
  sai = soma / (argc-2);
  imp(sai,argv[1]);
}
  
