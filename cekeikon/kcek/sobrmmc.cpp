#include <cekeikon.h>

int no2550(Mat_<COR> a)
{ int conta=0;
  for (int l=0; l<a.rows; l++)
    for (int c=0; c<a.cols; c++) {
      COR& cor=a(l,c);
      if (cor[0]==0)   { cor[0]=1;   conta++; }
      if (cor[0]==255) { cor[0]=254; conta++; }
      if (cor[1]==0)   { cor[1]=1;   conta++; }
      if (cor[1]==255) { cor[1]=254; conta++; }
      if (cor[2]==0)   { cor[2]=1;   conta++; }
      if (cor[2]==255) { cor[2]=254; conta++; }
    }
  return conta;
}

void sobrmmc(int argc, char** argv)
{ if (argc<4 || 9<argc) {
    printf("SobrMMc: Sobrepoe multiplas mascaras com cores RGBCMY\n");
    printf("SobrMMc ent.ppm sai.ppm red.pbm [gre.pbm] [blu.pbm] [cya.pbm] [mag.pbm] [yel.pbm]\n");
    printf("  sai.ppm nao pode ter extensao .jpg\n");
    printf("  Este programa assegura que nao haja pixels 255 ou 0\n");
    erro("Erro: Numero de argumentos invalido");
  }
  Mat_<COR> a; le(a,argv[1]);
  no2550(a);

  if (argc>3) { //red
    Mat_<GRY> mas; le(mas,argv[3]);
    if (a.size()!=mas.size()) erro("Erro: dimensoes diferentes");
    for (int l=0; l<a.rows; l++)
      for (int c=0; c<a.cols; c++)
        if (mas(l,c)==0) a(l,c)=COR(0,0,255);
  }
  if (argc>4) { //gre
    Mat_<GRY> mas; le(mas,argv[4]);
    if (a.size()!=mas.size()) erro("Erro: dimensoes diferentes");
    for (int l=0; l<a.rows; l++)
      for (int c=0; c<a.cols; c++)
        if (mas(l,c)==0) a(l,c)=COR(0,255,0);
  }
  if (argc>5) { //blu
    Mat_<GRY> mas; le(mas,argv[5]);
    if (a.size()!=mas.size()) erro("Erro: dimensoes diferentes");
    for (int l=0; l<a.rows; l++)
      for (int c=0; c<a.cols; c++)
        if (mas(l,c)==0) a(l,c)=COR(255,0,0);
  }
  if (argc>6) { //cya
    Mat_<GRY> mas; le(mas,argv[6]);
    if (a.size()!=mas.size()) erro("Erro: dimensoes diferentes");
    for (int l=0; l<a.rows; l++)
      for (int c=0; c<a.cols; c++)
        if (mas(l,c)==0) a(l,c)=COR(255,255,0);
  }
  if (argc>7) { //mag
    Mat_<GRY> mas; le(mas,argv[7]);
    if (a.size()!=mas.size()) erro("Erro: dimensoes diferentes");
    for (int l=0; l<a.rows; l++)
      for (int c=0; c<a.cols; c++)
        if (mas(l,c)==0) a(l,c)=COR(255,0,255);
  }
  if (argc>8) { //yel
    Mat_<GRY> mas; le(mas,argv[8]);
    if (a.size()!=mas.size()) erro("Erro: dimensoes diferentes");
    for (int l=0; l<a.rows; l++)
      for (int c=0; c<a.cols; c++)
        if (mas(l,c)==0) a(l,c)=COR(0,255,255);
  }

  imp(a,argv[2]);
}
