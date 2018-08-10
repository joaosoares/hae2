//otsug.cpp
#include <cekeikon.h>

void ConstroiHist(const Mat_<GRY>& ent, vector<double>& hist) {
  for (unsigned i=0; i<256; i++) hist[i]=0.0;
  for (unsigned i=0; i<ent.total(); i++) hist[ent(i)]++;
  for (unsigned i=0; i<256; i++) hist[i]=hist[i]/ent.total();
}

void otsug(int argc, char** argv) {
  if (argc!=3) {
    printf("OtsuG: Binariza imagem usando limiar de Otsu global\n");
    printf("OtsuG ent.pgm sai.pgm\n");
    erro("Erro: Numero de argumentos invalido");
  }

  Mat_<GRY> ent; le(ent,argv[1]);
  Mat_<GRY> sai(ent.size());

  vector<double> hist(256);
  ConstroiHist(ent,hist);

  double media=0.0;
  for (int i=0; i<256; i++) media=media+i*hist[i];

  double w=0.0; double m=0.0;
  double maximo=0.0; int maxind=0;
  for (int i=0; i<255; i++) {
  // Nota Se final for 256, nao funciona - Note que ha somente 255 possiveis cortes
    w=w+hist[i]; m=m+i*hist[i];
    double varian=elev2(media*w-m)/(w*(1-w));
    //printf("i=%d w=%g m=%g varian=%g\n",i,w,m,varian);
    if (varian>maximo) { maximo=varian; maxind=i; }
  }

  printf("Ind_max=%d (p<=ind_max -> preto), var_max=%lg\n",maxind,maximo);

  for (unsigned i=0; i<ent.total(); i++)
    if (ent(i)<=maxind) sai(i)=0; else sai(i)=255;
  imp(sai,argv[2]);
}





